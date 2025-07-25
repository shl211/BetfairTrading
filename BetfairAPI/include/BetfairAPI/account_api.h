#pragma once

#include <optional>
#include <string>
#include "BetfairAPI/jurisdiction.hpp"
#include "BetfairAPI/response.h"
#include "BetfairAPI/account_enum/wallet.hpp"
#include "BetfairAPI/account_enum/include_item.hpp"
#include "BetfairAPI/account_type/time_range.h"

namespace BetfairAPI {
    Response getAccountFunds(
        const std::string& api_key,
        const std::string& session_key,
        std::optional<AccountEnum::Wallet> wallet = std::nullopt,
        const Jurisdiction jurisdiction = Jurisdiction::GLOBAL,
        bool save_request_info = false
    );

    Response getAccountDetails(
        const std::string& api_key,
        const std::string& session_key,
        const Jurisdiction jurisdiction = Jurisdiction::GLOBAL,
        bool save_request_info = false
    );

    Response getAccountStatement(
        const std::string& api_key,
        const std::string& session_key,
        std::optional<std::string> locale,
        std::optional<int> from_record,
        std::optional<int> record_count,
        std::optional<AccountType::TimeRange> item_date_range,
        std::optional<AccountEnum::IncludeItem>,
        const Jurisdiction jurisdiction = Jurisdiction::GLOBAL,
        bool save_request_info = false
    );
}