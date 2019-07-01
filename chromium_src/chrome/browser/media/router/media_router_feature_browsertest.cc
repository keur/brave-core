/* Copyright 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "chrome/browser/media/router/media_router_feature.h"
#include "chrome/browser/ui/browser_finder.h"
#include "chrome/test/base/in_process_browser_test.h"
#include "chrome/test/base/testing_profile.h"
#include "chrome/test/base/ui_test_utils.h"
#include "components/policy/core/browser/browser_policy_connector.h"
#include "components/policy/core/common/mock_configuration_policy_provider.h"
#include "components/policy/core/common/policy_map.h"
#include "components/policy/policy_constants.h"
#include "net/dns/mock_host_resolver.h"

namespace policy {
class PolicyTest : public InProcessBrowserTest {
 protected:
  PolicyTest() {}
  ~PolicyTest() override {}

  void SetUp() override { InProcessBrowserTest::SetUp(); }

  void SetUpInProcessBrowserTestFixture() override {
    BrowserPolicyConnector::SetPolicyProviderForTesting(&provider_);
  }

  void SetUpOnMainThread() override {
    host_resolver()->AddRule("*", "127.0.0.1");
  }

  MockConfigurationPolicyProvider provider_;
};

// Sets the proper policy before the browser is started.
template <bool enable>
class MediaRouterPolicyTest : public PolicyTest {
 public:
  void SetUpInProcessBrowserTestFixture() override {
    PolicyTest::SetUpInProcessBrowserTestFixture();
    PolicyMap policies;
    policies.Set(key::kEnableMediaRouter, POLICY_LEVEL_MANDATORY,
                 POLICY_SCOPE_USER, POLICY_SOURCE_CLOUD,
                 std::make_unique<base::Value>(enable), nullptr);
    provider_.UpdateChromePolicy(policies);
  }
};

using MediaRouterEnabledPolicyTest = MediaRouterPolicyTest<true>;
using MediaRouterDisabledPolicyTest = MediaRouterPolicyTest<false>;

IN_PROC_BROWSER_TEST_F(MediaRouterEnabledPolicyTest, MediaRouterEnabled) {
  EXPECT_FALSE(media_router::MediaRouterEnabled(browser()->profile()));
}

IN_PROC_BROWSER_TEST_F(MediaRouterDisabledPolicyTest, MediaRouterDisabled) {
  EXPECT_FALSE(media_router::MediaRouterEnabled(browser()->profile()));
}
}  // namespace policy

