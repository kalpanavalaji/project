// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_CHROME_PAGES_H_
#define CHROME_BROWSER_UI_CHROME_PAGES_H_

#include <stdint.h>

#include <string>

#include "build/build_config.h"
#include "components/content_settings/core/common/content_settings_types.h"
#include "url/gurl.h"

#if !defined(OS_ANDROID)
#include "chrome/browser/signin/signin_promo.h"
#endif

class Browser;

namespace content {
class WebContents;
}

namespace chrome {

// Sources of requests to show the help tab.
enum HelpSource {
  // Keyboard accelerators.
  HELP_SOURCE_KEYBOARD,

  // Menus (e.g. app menu or Chrome OS system menu).
  HELP_SOURCE_MENU,

  // WebUI (the "About" page).
  HELP_SOURCE_WEBUI,
};


void ShowBookmarkManager(Browser* browser);
void ShowBookmarkManagerForNode(Browser* browser, int64_t node_id);
void ShowHistory(Browser* browser);
void ShowDownloads(Browser* browser);
void ShowExtensions(Browser* browser,
                    const std::string& extension_to_highlight);
void ShowConflicts(Browser* browser);

// ShowFeedbackPage() uses |browser| to determine the URL of the current tab.
// |browser| should be NULL if there are no currently open browser windows.
void ShowFeedbackPage(Browser* browser,
                      const std::string& description_template,
                      const std::string& category_tag);

void ShowHelp(Browser* browser, HelpSource source);
void ShowHelpForProfile(Profile* profile, HelpSource source);
void ShowPolicy(Browser* browser);
void ShowSlow(Browser* browser);

// Constructs a settings GURL for the specified |sub_page|.
GURL GetSettingsUrl(const std::string& sub_page);

// Returns true if |url| is the URL for the settings subpage |sub_page|.
bool IsSettingsSubPage(const GURL& url, const std::string& sub_page);

// Returns true if |browser| is a trusted popup window containing a page with
// matching |scheme| (or any trusted popup if |scheme| is empty).
bool IsTrustedPopupWindowWithScheme(const Browser* browser,
                                    const std::string& scheme);


// Various things that open in a settings UI.
void ShowSettings(Browser* browser);
void ShowSettingsSubPage(Browser* browser, const std::string& sub_page);
void ShowSettingsSubPageForProfile(Profile* profile,
                                   const std::string& sub_page);
void ShowContentSettingsExceptions(Browser* browser,
                                   ContentSettingsType content_settings_type);
void ShowContentSettingsExceptionsInWindow(
    Profile* profile,
    ContentSettingsType content_settings_type);
void ShowContentSettings(Browser* browser,
                         ContentSettingsType content_settings_type);
void ShowSettingsSubPageInTabbedBrowser(Browser* browser,
                                        const std::string& sub_page);
void ShowClearBrowsingDataDialog(Browser* browser);
void ShowPasswordManager(Browser* browser);
void ShowImportDialog(Browser* browser);
void ShowAboutChrome(Browser* browser);
void ShowSearchEngineSettings(Browser* browser);

#if !defined(OS_ANDROID)
// Initiates signin in a new browser tab.
void ShowBrowserSignin(Browser* browser,
                       signin_metrics::AccessPoint access_point);

// If the user is already signed in, shows the "Signin" portion of Settings,
// otherwise initiates signin in a new browser tab.
void ShowBrowserSigninOrSettings(Browser* browser,
                                 signin_metrics::AccessPoint access_point);
#endif

}  // namespace chrome

#endif  // CHROME_BROWSER_UI_CHROME_PAGES_H_
