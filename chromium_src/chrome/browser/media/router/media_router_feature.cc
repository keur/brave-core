/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "chrome/browser/media/router/media_router_feature.h"

#include "extensions/common/feature_switch.h"

#define MediaRouterEnabled MediaRouterEnabled_ChromiumImpl
#include "../../../../../../chrome/browser/media/router/media_router_feature.cc"  // NOLINT
#undef MediaRouterEnabled

namespace media_router {

bool IsMediaRouterFeatureEnabled() {
  return extensions::FeatureSwitch::load_media_router_component_extension()
      ->IsEnabled();
}

bool MediaRouterEnabled(content::BrowserContext* context) {
  if (!IsMediaRouterFeatureEnabled())
    return false;
  return MediaRouterEnabled_ChromiumImpl(context);
}

}  // namespace media_router
