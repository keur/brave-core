/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVELEDGER_WALLET_WALLET_H_
#define BRAVELEDGER_WALLET_WALLET_H_

#include <stdint.h>

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "bat/ledger/ledger.h"
#include "bat/ledger/internal/bat_helper.h"

namespace bat_ledger {
class LedgerImpl;
}

namespace braveledger_wallet {
class Create;
}

namespace braveledger_wallet {
class Recover;
}

namespace braveledger_wallet {
class Balance;
}

namespace braveledger_uphold {
class Uphold;
}

namespace braveledger_wallet {

class Wallet {
 public:
  explicit Wallet(bat_ledger::LedgerImpl* ledger);

  ~Wallet();

  void CreateWalletIfNecessary();

  void RecoverWallet(const std::string& passPhrase);

  std::string GetWalletPassphrase() const;

  void GetWalletProperties(ledger::OnWalletPropertiesCallback callback);

  ledger::WalletPropertiesPtr WalletPropertiesToWalletInfo(
    const braveledger_bat_helper::WALLET_PROPERTIES_ST& properties);

  void FetchBalance(ledger::FetchBalanceCallback callback);

  void GetExternalWallet(const std::string& type,
                         ledger::ExternalWalletCallback callback);

 private:
  void WalletPropertiesCallback(
      int response_status_code,
      const std::string& response,
      const std::map<std::string, std::string>& headers,
      ledger::OnWalletPropertiesCallback callback);

  void OnGetExternalWallet(
    const std::string& type,
    ledger::ExternalWalletCallback callback,
    std::map<std::string, ledger::ExternalWalletPtr> wallets);

  bat_ledger::LedgerImpl* ledger_;  // NOT OWNED
  std::unique_ptr<Create> create_;
  std::unique_ptr<Recover> recover_;
  std::unique_ptr<Balance> balance_;
  std::unique_ptr<braveledger_uphold::Uphold> uphold_;
};

}  // namespace braveledger_wallet
#endif  // BRAVELEDGER_WALLET_WALLET_H_
