#pragma once

#include <optional>
#include <string>
#include "BetfairAPI/jurisdiction.hpp"
#include "BetfairAPI/response.h"
#include "BetfairAPI/account_enum/wallet.hpp"

namespace BetfairAPI {
    Response getAccountFunds(
        const std::string& api_key,
        const std::string& session_key,
        std::optional<AccountEnum::Wallet> wallet = std::nullopt,
        const Jurisdiction jurisdiction = Jurisdiction::GLOBAL,
        bool save_request_info = false
    );
}