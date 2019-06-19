/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_rewards/browser/monthly_statement.h"

namespace brave_rewards {

  MonthlyStatement::MonthlyStatement() {}

  MonthlyStatement::MonthlyStatement(const std::string& site_id) :
      id(site_id),
      verified(false),
      excluded(false),
      probi(0),
      category(0),
      date(0),
      percentage(0),
      reconcile_stamp(0) {
  }

  MonthlyStatement::~MonthlyStatement() {}

  MonthlyStatement::MonthlyStatement(const MonthlyStatement &properties) {
    id = properties.id;
    verified = properties.verified;
    excluded = properties.excluded;
    name = properties.name;
    favicon_url = properties.favicon_url;
    url = properties.url;
    provider = properties.provider;
    probi = properties.probi;
    date = properties.date;
    category = properties.category;
    percentage = properties.percentage;
    reconcile_stamp = properties.reconcile_stamp;
  }
}  // namespace brave_rewards
