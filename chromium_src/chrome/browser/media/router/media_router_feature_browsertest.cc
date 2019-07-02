/* Copyright 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "chrome/browser/media/router/media_router_feature.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/browser_finder.h"
#include "chrome/common/pref_names.h"
#include "chrome/test/base/in_process_browser_test.h"
#include "chrome/test/base/ui_test_utils.h"
#include "components/prefs/pref_service.h"
#include "net/dns/mock_host_resolver.h"

class MediaRouterTest : public InProcessBrowserTest {
 protected:
  MediaRouterTest() {}
  ~MediaRouterTest() override {}

  void SetUpOnMainThread() override {
    InProcessBrowserTest::SetUpOnMainThread();
    host_resolver()->AddRule("*", "127.0.0.1");
  }
};

IN_PROC_BROWSER_TEST_F(MediaRouterTest, MediaRouterDisabled) {
  browser()->profile()->GetPrefs()->SetBoolean(prefs::kEnableMediaRouter, false);
  EXPECT_FALSE(media_router::MediaRouterEnabled(browser()->profile()));
}
