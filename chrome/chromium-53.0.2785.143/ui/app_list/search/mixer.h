// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_APP_LIST_SEARCH_MIXER_H_
#define UI_APP_LIST_SEARCH_MIXER_H_

#include <stddef.h>

#include <vector>

#include "base/gtest_prod_util.h"
#include "base/macros.h"
#include "base/memory/scoped_vector.h"
#include "ui/app_list/app_list_export.h"
#include "ui/app_list/app_list_model.h"
#include "ui/app_list/search/history_types.h"

namespace app_list {

namespace test {
FORWARD_DECLARE_TEST(MixerTest, Publish);
}

class SearchProvider;
class SearchResult;

// Mixer collects results from providers, sorts them and publishes them to the
// SearchResults UI model. The targeted results have 6 slots to hold the
// result. The search controller can specify any number of groups, each with a
// different number of results and priority boost. The "omnibox" group is
// expected to contain omnibox results, and will be treated specially.
class APP_LIST_EXPORT Mixer {
 public:
  explicit Mixer(AppListModel::SearchResults* ui_results);
  ~Mixer();

  // Adds a new mixer group. A maximum of |max_results| results will be
  // displayed from this group (if 0, will allow unlimited results from this
  // group). Behaviour depends on the AppListMixer field trial:
  // - If default: Each result in the group will have its score boosted by
  //   |boost|. |multiplier| is ignored.
  // - If "Blended": |max_results| is a "soft" maximum; if there aren't enough
  //   results from all groups, more than |max_results| may be chosen from this
  //   group. Each result in the group will have its score multiplied by
  //   |multiplier|. |boost| is ignored.
  // Returns the group's group_id.
  size_t AddGroup(size_t max_results, double boost, double multiplier);

  // Adds a new mixer group for the special "omnibox" group. This group will be
  // treated specially by the Mixer (it will be truncated such that it fills the
  // remaining slots without overflowing, but with at least one result). A
  // maximum of one group should be added using this method.
  size_t AddOmniboxGroup(size_t max_results, double boost, double multiplier);

  // Associates a provider with a mixer group.
  void AddProviderToGroup(size_t group_id, SearchProvider* provider);

  // Collects the results, sorts and publishes them.
  void MixAndPublish(bool is_voice_query,
                     const KnownResults& known_results,
                     size_t num_max_results);

 private:
  FRIEND_TEST_ALL_PREFIXES(test::MixerTest, Publish);

  // Used for sorting and mixing results.
  struct APP_LIST_EXPORT SortData {
    SortData();
    SortData(SearchResult* result, double score);

    bool operator<(const SortData& other) const;

    SearchResult* result;  // Not owned.
    double score;
  };
  typedef std::vector<Mixer::SortData> SortedResults;

  class Group;
  typedef ScopedVector<Group> Groups;

  // Publishes the given |new_results| to |ui_results|, deleting any existing
  // results that are not in |new_results|. Results that already exist in
  // |ui_results| are reused to avoid flickering caused by icon reload.
  static void Publish(const SortedResults& results,
                      AppListModel::SearchResults* ui_results);

  // Removes entries from |results| with duplicate IDs. When two or more results
  // have the same ID, the earliest one in the |results| list is kept.
  // NOTE: This is not necessarily the one with the highest *score*, as
  // |results| may not have been sorted yet.
  static void RemoveDuplicates(SortedResults* results);

  void FetchResults(bool is_voice_query, const KnownResults& known_results);

  AppListModel::SearchResults* ui_results_;  // Not owned.
  Groups groups_;

  // The ID of the omnibox group. The group with this ID will be treated
  // specially by the Mixer. Ignored if the AppListMixer field trial is
  // "Blended".
  // TODO(mgiuca): Remove this after the field trial is complete.
  size_t omnibox_group_ = 0;
  // Whether |omnibox_group_| has been set.
  bool has_omnibox_group_ = false;

  DISALLOW_COPY_AND_ASSIGN(Mixer);
};

}  // namespace app_list

#endif  // UI_APP_LIST_SEARCH_MIXER_H_
