// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_LOGIN_SCREENS_GAIA_SCREEN_H_
#define CHROME_BROWSER_CHROMEOS_LOGIN_SCREENS_GAIA_SCREEN_H_

#include <string>

#include "base/bind.h"
#include "base/compiler_specific.h"
#include "base/macros.h"

namespace chromeos {

class LoginDisplayWebUIHandler;
class GaiaScreenHandler;

// This class represents GAIA screen: login screen that is responsible for
// GAIA-based sign-in.
class GaiaScreen {
 public:
  GaiaScreen();
  virtual ~GaiaScreen();
  void SetLegacyHandler(LoginDisplayWebUIHandler* handler);
  void SetScreenHandler(GaiaScreenHandler* handler);
  void MaybePreloadAuthExtension();

 private:
  LoginDisplayWebUIHandler* legacy_handler_;
  GaiaScreenHandler* screen_handler_;

  DISALLOW_COPY_AND_ASSIGN(GaiaScreen);
};

}  // namespace chromeos

#endif  // CHROME_BROWSER_CHROMEOS_LOGIN_SCREENS_GAIA_SCREEN_H_
