// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_ANDROID_CONTENT_VIEW_RENDER_VIEW_H_
#define CONTENT_BROWSER_ANDROID_CONTENT_VIEW_RENDER_VIEW_H_

#include <memory>

#include "base/android/jni_weak_ref.h"
#include "base/logging.h"
#include "base/macros.h"
#include "base/memory/weak_ptr.h"
#include "content/public/browser/android/compositor_client.h"
#include "ui/gfx/native_widget_types.h"

namespace cc {
class Layer;
}

namespace content {
class Compositor;

class ContentViewRenderView : public CompositorClient {
 public:
  // Registers the JNI methods for ContentViewRender.
  static bool RegisterContentViewRenderView(JNIEnv* env);

  ContentViewRenderView(JNIEnv* env,
                        jobject obj,
                        gfx::NativeWindow root_window);

  // Methods called from Java via JNI -----------------------------------------
  void Destroy(JNIEnv* env, const base::android::JavaParamRef<jobject>& obj);
  void SetCurrentContentViewCore(
      JNIEnv* env,
      const base::android::JavaParamRef<jobject>& obj,
      jlong native_content_view_core);
  void SurfaceCreated(JNIEnv* env,
                      const base::android::JavaParamRef<jobject>& obj);
  void SurfaceDestroyed(JNIEnv* env,
                        const base::android::JavaParamRef<jobject>& obj);
  void SurfaceChanged(JNIEnv* env,
                      const base::android::JavaParamRef<jobject>& obj,
                      jint format,
                      jint width,
                      jint height,
                      const base::android::JavaParamRef<jobject>& surface);
  void SetOverlayVideoMode(JNIEnv* env,
                           const base::android::JavaParamRef<jobject>& obj,
                           bool enabled);

  // CompositorClient implementation
  void UpdateLayerTreeHost() override;
  void OnSwapBuffersCompleted(int pending_swap_buffers) override;

 private:
  ~ContentViewRenderView() override;

  void InitCompositor();

  base::android::ScopedJavaGlobalRef<jobject> java_obj_;

  std::unique_ptr<content::Compositor> compositor_;

  gfx::NativeWindow root_window_;
  int current_surface_format_;

  DISALLOW_COPY_AND_ASSIGN(ContentViewRenderView);
};



}

#endif  // CONTENT_BROWSER_ANDROID_CONTENT_VIEW_RENDER_VIEW_H_
