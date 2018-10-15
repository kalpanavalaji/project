// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "sandbox/mac/seatbelt.h"

extern "C" {
#include <sandbox.h>

int sandbox_init_with_parameters(const char* profile,
                                 uint64_t flags,
                                 const char* const parameters[],
                                 char** errorbuf);
};

namespace sandbox {

// static
int Seatbelt::Init(const char* profile, uint64_t flags, char** errorbuf) {
// OS X deprecated these functions, but did not provide a suitable replacement,
// so ignore the deprecation warning.
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
  return ::sandbox_init(profile, flags, errorbuf);
#pragma clang diagnostic pop
}

// static
int Seatbelt::InitWithParams(const char* profile,
                             uint64_t flags,
                             const char* const parameters[],
                             char** errorbuf) {
  return ::sandbox_init_with_parameters(profile, flags, parameters, errorbuf);
}

// static
void Seatbelt::FreeError(char* errorbuf) {
// OS X deprecated these functions, but did not provide a suitable replacement,
// so ignore the deprecation warning.
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
  return ::sandbox_free_error(errorbuf);
#pragma clang diagnostic pop
}

}  // namespace sandbox
