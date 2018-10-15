// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_DISPLAY_DISPLAY_SWITCHES_H_
#define UI_DISPLAY_DISPLAY_SWITCHES_H_

#include "base/compiler_specific.h"
#include "build/build_config.h"
#include "ui/display/display_export.h"

namespace switches {

DISPLAY_EXPORT extern const char kForceDeviceScaleFactor[];

#if defined(OS_CHROMEOS)
DISPLAY_EXPORT extern const char kDisableDisplayColorCalibration[];
#endif

}  // namespace switches

#endif  // UI_DISPLAY_DISPLAY_SWITCHES_H_
