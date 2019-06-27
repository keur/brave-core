/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <string>

#include "base/strings/strcat.h"
#include "base/strings/string_util.h"
#include "base/task/post_task.h"
#include "brave/common/url_constants.h"
#include "chrome/browser/external_protocol/external_protocol_handler.h"
#include "content/public/browser/browser_task_traits.h"
#include "content/public/browser/browser_thread.h"
#include "content/public/browser/render_process_host.h"
#include "content/public/browser/render_view_host.h"
#include "net/base/escape.h"

namespace brave_rewards {

bool IsRewardsEnabled(content::BrowserContext* browser_context) {
  return true;
}

static GURL TranslateUrl(const GURL& url) {
  if (!url.is_valid()) {
    return GURL();
  }

  std::string path = url.path();
  std::string query;

  if (url.has_query()) {
    query = base::StrCat({
      "?",
      net::EscapeExternalHandlerValue(url.query())
    });
  }

  base::ReplaceFirstSubstringAfterOffset(&path, 0, "/", "");

  return GURL(
      base::StrCat({
        "chrome://rewards",
        path,
        query
      }));
}

static void LoadOrLaunchRewardsURL(
    const GURL& url,
    const content::ResourceRequestInfo::WebContentsGetter& web_contents_getter,
    ui::PageTransition page_transition,
    bool has_user_gesture) {
  content::WebContents* web_contents = web_contents_getter.Run();
  if (!web_contents)
    return;

  if (IsRewardsEnabled(web_contents->GetBrowserContext())) {
    web_contents->GetController().LoadURL(url, content::Referrer(),
        page_transition, std::string());
  } else {
    ExternalProtocolHandler::LaunchUrl(
        url, web_contents->GetRenderViewHost()->GetProcess()->GetID(),
        web_contents->GetRenderViewHost()->GetRoutingID(), page_transition,
        has_user_gesture);
  }
}

static bool HandleRewardsURLRewrite(GURL* url,
    content::BrowserContext* browser_context) {
  if (IsRewardsEnabled(browser_context) && url->SchemeIs(kRewardsScheme)) {
    *url = TranslateUrl(*url);
    return true;
  }

  return false;
}

static bool HandleRewardsProtocol(
    const GURL& url,
    content::ResourceRequestInfo::WebContentsGetter web_contents_getter,
    ui::PageTransition page_transition,
    bool has_user_gesture) {
  if (url.SchemeIs(kRewardsScheme)) {
    base::PostTaskWithTraits(FROM_HERE, {content::BrowserThread::UI},
        base::BindOnce(&LoadOrLaunchRewardsURL, url, web_contents_getter,
        page_transition, has_user_gesture));
    return true;
  }

  return false;
}

}  // namespace brave_rewards