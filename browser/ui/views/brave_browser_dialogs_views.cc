/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/browser/ui/brave_browser_dialogs.h"

#include "brave/browser/ui/views/ads_notification_view.h"

namespace brave {

void ShowAdsNotification(Browser* browser) {
  LOG(ERROR) << __FUNCTION__;
  static int show_count = 0;
  show_count++;
  AdsNotificationView::Show(
      browser,
      show_count % 2 == 0 ? GURL("https://simonhong.github.io/")
                          : GURL("brave://rewards/"));
}

}