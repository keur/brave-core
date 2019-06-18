/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_BRAVE_REWARDS_BROWSER_MONTHLY_STATEMENT_H_
#define BRAVE_COMPONENTS_BRAVE_REWARDS_BROWSER_MONTHLY_STATEMENT_H_

#include <stdint.h>

#include <string>
#include <vector>

#include "base/macros.h"

namespace brave_rewards {

struct MonthlyStatement {
  MonthlyStatement();
  MonthlyStatement(const std::string& site_id);
  MonthlyStatement(const MonthlyStatement& properties);
  ~MonthlyStatement();

  std::string id;
  bool verified;
  bool excluded;
  std::string name;
  std::string favicon_url;
  std::string url;
  std::string provider;
  std::string probi;
  int32_t category;
  uint64_t date;
  uint32_t percentage;
};

typedef std::vector<MonthlyStatement> MonthlyStatementList;

}  // namespace brave_rewards

#endif  // BRAVE_COMPONENTS_BRAVE_REWARDS_BROWSER_MONTHLY_STATEMENT_H_
