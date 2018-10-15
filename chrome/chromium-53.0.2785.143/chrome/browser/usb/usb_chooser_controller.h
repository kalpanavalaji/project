// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_USB_USB_CHOOSER_CONTROLLER_H_
#define CHROME_BROWSER_USB_USB_CHOOSER_CONTROLLER_H_

#include <utility>
#include <vector>

#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "base/scoped_observer.h"
#include "components/chooser_controller/chooser_controller.h"
#include "device/usb/public/interfaces/chooser_service.mojom.h"
#include "device/usb/usb_service.h"
#include "mojo/public/cpp/bindings/array.h"

namespace content {
class RenderFrameHost;
}

namespace device {
class UsbDevice;
class UsbDeviceFilter;
}

// UsbChooserController creates a chooser for WebUSB.
// It is owned by ChooserBubbleDelegate.
class UsbChooserController : public ChooserController,
                             public device::UsbService::Observer {
 public:
  UsbChooserController(
      content::RenderFrameHost* owner,
      mojo::Array<device::usb::DeviceFilterPtr> device_filters,
      content::RenderFrameHost* render_frame_host,
      const device::usb::ChooserService::GetPermissionCallback& callback);
  ~UsbChooserController() override;

  // ChooserController:
  size_t NumOptions() const override;
  const base::string16& GetOption(size_t index) const override;
  void Select(size_t index) override;
  void Cancel() override;
  void Close() override;
  void OpenHelpCenterUrl() const override;

  // device::UsbService::Observer:
  void OnDeviceAdded(scoped_refptr<device::UsbDevice> device) override;
  void OnDeviceRemoved(scoped_refptr<device::UsbDevice> device) override;

 private:
  void GotUsbDeviceList(
      const std::vector<scoped_refptr<device::UsbDevice>>& devices);
  bool DisplayDevice(scoped_refptr<device::UsbDevice> device) const;

  content::RenderFrameHost* const render_frame_host_;
  device::usb::ChooserService::GetPermissionCallback callback_;
  ScopedObserver<device::UsbService, device::UsbService::Observer>
      usb_service_observer_;
  std::vector<device::UsbDeviceFilter> filters_;
  // Each pair is a (device, device name).
  std::vector<std::pair<scoped_refptr<device::UsbDevice>, base::string16>>
      devices_;
  base::WeakPtrFactory<UsbChooserController> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(UsbChooserController);
};

#endif  // CHROME_BROWSER_USB_USB_CHOOSER_CONTROLLER_H_
