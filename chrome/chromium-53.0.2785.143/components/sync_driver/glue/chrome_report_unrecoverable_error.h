// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SYNC_DRIVER_GLUE_CHROME_REPORT_UNRECOVERABLE_ERROR_H_
#define COMPONENTS_SYNC_DRIVER_GLUE_CHROME_REPORT_UNRECOVERABLE_ERROR_H_

#include "components/version_info/version_info.h"

namespace browser_sync {

// Sends a minidump via breakpad for canary/dev channels at a hardcoded
// sampling rate. Does nothing on beta/stable builds.
void ChromeReportUnrecoverableError(version_info::Channel channel);

}  // namespace browser_sync

#endif  // COMPONENTS_SYNC_DRIVER_GLUE_CHROME_REPORT_UNRECOVERABLE_ERROR_H_
