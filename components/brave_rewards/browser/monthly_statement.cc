/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_rewards/browser/monthly_statement.h"

namespace brave_rewards {

  MonthlyStatement::MonthlyStatement() {}

  MonthlyStatement::~MonthlyStatement() {}

  MonthlyStatement::MonthlyStatement(const MonthlyStatement &properties) {
    id = properties.id;
    verified = properties.verified;
    name = properties.name;
    favicon_url = properties.favicon_url;
    url = properties.url;
    provider = properties.provider;
    probi = properties.probi;
    month = properties.month;
    year = properties.year;
    category = properties.category;
  }
}  // namespace brave_rewards
