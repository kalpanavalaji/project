// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "remoting/protocol/video_frame_pump.h"

#include <algorithm>
#include <memory>
#include <utility>

#include "base/bind.h"
#include "base/callback.h"
#include "base/logging.h"
#include "base/memory/ptr_util.h"
#include "base/single_thread_task_runner.h"
#include "base/task_runner_util.h"
#include "base/time/time.h"
#include "remoting/base/constants.h"
#include "remoting/proto/control.pb.h"
#include "remoting/proto/video.pb.h"
#include "remoting/protocol/video_stub.h"
#include "third_party/webrtc/modules/desktop_capture/desktop_frame.h"

namespace remoting {
namespace protocol {

// Interval between empty keep-alive frames. These frames are sent only when the
// stream is paused or inactive for some other reason (e.g. when blocked on
// capturer). To prevent PseudoTCP from resetting congestion window this value
// must be smaller than the minimum RTO used in PseudoTCP, which is 250ms.
static const int kKeepAlivePacketIntervalMs = 200;

static bool g_enable_timestamps = false;

VideoFramePump::FrameTimestamps::FrameTimestamps() {}
VideoFramePump::FrameTimestamps::~FrameTimestamps() {}

VideoFramePump::PacketWithTimestamps::PacketWithTimestamps(
    std::unique_ptr<VideoPacket> packet,
    std::unique_ptr<FrameTimestamps> timestamps)
    : packet(std::move(packet)), timestamps(std::move(timestamps)) {}

VideoFramePump::PacketWithTimestamps::~PacketWithTimestamps() {}

// static
void VideoFramePump::EnableTimestampsForTests() {
  g_enable_timestamps = true;
}

VideoFramePump::VideoFramePump(
    scoped_refptr<base::SingleThreadTaskRunner> encode_task_runner,
    std::unique_ptr<webrtc::DesktopCapturer> capturer,
    std::unique_ptr<VideoEncoder> encoder,
    protocol::VideoStub* video_stub)
    : encode_task_runner_(encode_task_runner),
      capturer_(std::move(capturer)),
      encoder_(std::move(encoder)),
      video_stub_(video_stub),
      keep_alive_timer_(
          FROM_HERE,
          base::TimeDelta::FromMilliseconds(kKeepAlivePacketIntervalMs),
          base::Bind(&VideoFramePump::SendKeepAlivePacket,
                     base::Unretained(this)),
          false),
      capture_scheduler_(base::Bind(&VideoFramePump::CaptureNextFrame,
                                    base::Unretained(this))),
      weak_factory_(this) {
  DCHECK(encoder_);
  DCHECK(video_stub_);

  capturer_->Start(this);
  capture_scheduler_.Start();
}

VideoFramePump::~VideoFramePump() {
  encode_task_runner_->DeleteSoon(FROM_HERE, encoder_.release());
}

void VideoFramePump::Pause(bool pause) {
  DCHECK(thread_checker_.CalledOnValidThread());

  capture_scheduler_.Pause(pause);
}

void VideoFramePump::OnInputEventReceived(int64_t event_timestamp) {
  DCHECK(thread_checker_.CalledOnValidThread());

  if (!next_frame_timestamps_)
    next_frame_timestamps_.reset(new FrameTimestamps());
  next_frame_timestamps_->input_event_client_timestamp = event_timestamp;
  next_frame_timestamps_->input_event_received_time = base::TimeTicks::Now();
}

void VideoFramePump::SetLosslessEncode(bool want_lossless) {
  DCHECK(thread_checker_.CalledOnValidThread());

  encode_task_runner_->PostTask(
      FROM_HERE, base::Bind(&VideoEncoder::SetLosslessEncode,
                            base::Unretained(encoder_.get()), want_lossless));
}

void VideoFramePump::SetLosslessColor(bool want_lossless) {
  DCHECK(thread_checker_.CalledOnValidThread());

  encode_task_runner_->PostTask(
      FROM_HERE, base::Bind(&VideoEncoder::SetLosslessColor,
                            base::Unretained(encoder_.get()), want_lossless));
}

void VideoFramePump::SetObserver(Observer* observer) {
  DCHECK(thread_checker_.CalledOnValidThread());
  observer_ = observer;
}

void VideoFramePump::OnCaptureResult(
    webrtc::DesktopCapturer::Result result,
    std::unique_ptr<webrtc::DesktopFrame> frame) {
  DCHECK(thread_checker_.CalledOnValidThread());

  capture_scheduler_.OnCaptureCompleted();

  captured_frame_timestamps_->capture_ended_time = base::TimeTicks::Now();

  if (frame) {
    webrtc::DesktopVector dpi =
        frame->dpi().is_zero() ? webrtc::DesktopVector(kDefaultDpi, kDefaultDpi)
                               : frame->dpi();
    if (!frame_size_.equals(frame->size()) || !frame_dpi_.equals(dpi)) {
      frame_size_ = frame->size();
      frame_dpi_ = dpi;
      if (observer_)
        observer_->OnVideoSizeChanged(this, frame_size_, frame_dpi_);
    }
  }

  // Even when |frame| is nullptr we still need to post it to the encode thread
  // to make sure frames are freed in the same order they are received and
  // that we don't start capturing frame n+2 before frame n is freed.
  base::PostTaskAndReplyWithResult(
      encode_task_runner_.get(), FROM_HERE,
      base::Bind(&VideoFramePump::EncodeFrame, encoder_.get(),
                 base::Passed(&frame),
                 base::Passed(&captured_frame_timestamps_)),
      base::Bind(&VideoFramePump::OnFrameEncoded, weak_factory_.GetWeakPtr()));
}

void VideoFramePump::CaptureNextFrame() {
  DCHECK(thread_checker_.CalledOnValidThread());

  // |next_frame_timestamps_| is not set if no input events were received since
  // the previous frame. In that case create FrameTimestamps instance without
  // setting |input_event_client_timestamp| and |input_event_received_time|.
  if (!next_frame_timestamps_)
    next_frame_timestamps_.reset(new FrameTimestamps());

  captured_frame_timestamps_ = std::move(next_frame_timestamps_);
  captured_frame_timestamps_->capture_started_time = base::TimeTicks::Now();

  capturer_->Capture(webrtc::DesktopRegion());
}

// static
std::unique_ptr<VideoFramePump::PacketWithTimestamps>
VideoFramePump::EncodeFrame(VideoEncoder* encoder,
                            std::unique_ptr<webrtc::DesktopFrame> frame,
                            std::unique_ptr<FrameTimestamps> timestamps) {
  timestamps->encode_started_time = base::TimeTicks::Now();

  std::unique_ptr<VideoPacket> packet;
  // If |frame| is non-NULL then let the encoder process it.
  if (frame)
    packet = encoder->Encode(*frame, 0);

  // If |frame| is NULL, or the encoder returned nothing, return an empty
  // packet.
  if (!packet)
    packet.reset(new VideoPacket());

  if (frame)
    packet->set_capture_time_ms(frame->capture_time_ms());

  timestamps->encode_ended_time = base::TimeTicks::Now();
  packet->set_encode_time_ms(
      (timestamps->encode_ended_time - timestamps->encode_started_time)
          .InMilliseconds());

  return base::WrapUnique(
      new PacketWithTimestamps(std::move(packet), std::move(timestamps)));
}

void VideoFramePump::OnFrameEncoded(
    std::unique_ptr<PacketWithTimestamps> packet) {
  DCHECK(thread_checker_.CalledOnValidThread());

  capture_scheduler_.OnFrameEncoded(packet->packet.get());

  if (send_pending_) {
    pending_packets_.push_back(std::move(packet));
  } else {
    SendPacket(std::move(packet));
  }
}

void VideoFramePump::SendPacket(std::unique_ptr<PacketWithTimestamps> packet) {
  DCHECK(thread_checker_.CalledOnValidThread());
  DCHECK(!send_pending_);

  packet->timestamps->can_send_time = base::TimeTicks::Now();
  UpdateFrameTimers(packet->packet.get(), packet->timestamps.get());

  if (observer_) {
    observer_->OnVideoFrameSent(
        this, packet->packet->frame_id(),
        packet->timestamps->input_event_client_timestamp);
  }

  send_pending_ = true;
  video_stub_->ProcessVideoPacket(std::move(packet->packet),
                                  base::Bind(&VideoFramePump::OnVideoPacketSent,
                                             weak_factory_.GetWeakPtr()));
}

void VideoFramePump::UpdateFrameTimers(VideoPacket* packet,
                                       FrameTimestamps* timestamps) {
  if (g_enable_timestamps)
    packet->set_timestamp(timestamps->capture_ended_time.ToInternalValue());


  if (!timestamps->input_event_received_time.is_null()) {
    packet->set_capture_pending_time_ms((timestamps->capture_started_time -
                                         timestamps->input_event_received_time)
                                            .InMilliseconds());
    packet->set_latest_event_timestamp(
        timestamps->input_event_client_timestamp);
  }

  packet->set_capture_overhead_time_ms(
      (timestamps->capture_ended_time - timestamps->capture_started_time)
          .InMilliseconds() -
      packet->capture_time_ms());

  packet->set_encode_pending_time_ms(
      (timestamps->encode_started_time - timestamps->capture_ended_time)
          .InMilliseconds());

  packet->set_send_pending_time_ms(
      (timestamps->can_send_time - timestamps->encode_ended_time)
          .InMilliseconds());
}

void VideoFramePump::OnVideoPacketSent() {
  DCHECK(thread_checker_.CalledOnValidThread());

  send_pending_ = false;
  capture_scheduler_.OnFrameSent();
  keep_alive_timer_.Reset();

  // Send next packet if any.
  if (!pending_packets_.empty()) {
    std::unique_ptr<PacketWithTimestamps> next(pending_packets_.front());
    pending_packets_.weak_erase(pending_packets_.begin());
    SendPacket(std::move(next));
  }
}

void VideoFramePump::SendKeepAlivePacket() {
  DCHECK(thread_checker_.CalledOnValidThread());

  video_stub_->ProcessVideoPacket(
      base::WrapUnique(new VideoPacket()),
      base::Bind(&VideoFramePump::OnKeepAlivePacketSent,
                 weak_factory_.GetWeakPtr()));
}

void VideoFramePump::OnKeepAlivePacketSent() {
  DCHECK(thread_checker_.CalledOnValidThread());

  keep_alive_timer_.Reset();
}

}  // namespace protocol
}  // namespace remoting
