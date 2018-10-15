// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_BANNERS_APP_BANNER_MANAGER_H_
#define CHROME_BROWSER_BANNERS_APP_BANNER_MANAGER_H_

#include <memory>
#include <vector>

#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/banners/app_banner_data_fetcher.h"
#include "chrome/browser/engagement/site_engagement_observer.h"
#include "content/public/browser/web_contents_observer.h"
#include "third_party/WebKit/public/platform/modules/app_banner/WebAppBannerPromptReply.h"

namespace banners {
class AppBannerDataFetcher;

/**
 * Creates an app banner.
 *
 * Hooks the wiring together for getting the data for a particular app.
 * Monitors at most one app at a time, tracking the info for the most recently
 * requested app. Any work in progress for other apps is discarded.
 */
class AppBannerManager : public content::WebContentsObserver,
                         public AppBannerDataFetcher::Delegate,
                         public SiteEngagementObserver {
 public:
  static void DisableSecureSchemeCheckForTesting();

  static void SetEngagementWeights(double direct_engagement,
                                   double indirect_engagement);

  // Returns whether or not the URLs match for everything except for the ref.
  static bool URLsAreForTheSamePage(const GURL& first, const GURL& second);

  // Requests an app banner. Set |is_debug_mode| when it is triggered by the
  // developer's action in DevTools.
  void RequestAppBanner(const GURL& validated_url, bool is_debug_mode);

  ~AppBannerManager() override;

 protected:
  explicit AppBannerManager(content::WebContents* web_contents);

  void ReplaceWebContents(content::WebContents* web_contents);

  // Creates an AppBannerDataFetcher, which constructs an app banner.
  virtual AppBannerDataFetcher* CreateAppBannerDataFetcher(
      base::WeakPtr<AppBannerDataFetcher::Delegate> weak_delegate,
      bool is_debug_mode) = 0;

  // Return whether the AppBannerDataFetcher is active.
  bool IsFetcherActive();

  scoped_refptr<AppBannerDataFetcher> data_fetcher() { return data_fetcher_; }

 private:
  // WebContentsObserver overrides.
  void DidStartNavigation(
      content::NavigationHandle* navigation_handle) override;
  void DidFinishNavigation(
      content::NavigationHandle* navigation_handle) override;
  void DidFinishLoad(content::RenderFrameHost* render_frame_host,
                     const GURL& validated_url) override;
  void MediaStartedPlaying(const MediaPlayerId& id) override;
  void MediaStoppedPlaying(const MediaPlayerId& id) override;

  // AppBannerDataFetcher::Delegate overrides.
  bool HandleNonWebApp(const std::string& platform,
                       const GURL& url,
                       const std::string& id,
                       bool is_debug_mode) override;

  // SiteEngagementObserver overrides.
  void OnEngagementIncreased(content::WebContents* web_contents,
                             const GURL& url,
                             double score) override;

  // Cancels an active DataFetcher, stopping its banners from appearing.
  void CancelActiveFetcher();

  // The type of navigation made to the page
  ui::PageTransition last_transition_type_;

  // Fetches the data required to display a banner for the current page.
  scoped_refptr<AppBannerDataFetcher> data_fetcher_;

  // We do not want to trigger a banner when the manager is attached to
  // a WebContents that is playing video. Banners triggering on a site in the
  // background will appear when the tab is reactivated.
  std::vector<MediaPlayerId> active_media_players_;

  // If a banner is requested before the page has finished loading, defer
  // triggering the pipeline until the load is complete.
  bool banner_request_queued_;
  bool load_finished_;

  // A weak pointer is used as the lifetime of the ServiceWorkerContext is
  // longer than the lifetime of this banner manager. The banner manager
  // might be gone when calls sent to the ServiceWorkerContext are completed.
  base::WeakPtrFactory<AppBannerManager> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(AppBannerManager);
};  // class AppBannerManager

}  // namespace banners

#endif  // CHROME_BROWSER_BANNERS_APP_BANNER_MANAGER_H_
