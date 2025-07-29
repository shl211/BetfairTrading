#pragma once

#include <optional>
#include <string>
#include <memory>
#include "BetfairAPI/jurisdiction.hpp"
#include "http/response.h"
#include "Logging/ILogger.h"
#include "BetfairAPI/account_enum/wallet.hpp"
#include "BetfairAPI/account_enum/include_item.hpp"
#include "BetfairAPI/account_type/time_range.h"

namespace BetfairAPI {
    HTTP::Response getAccountFunds(
        const std::string& api_key,
        const std::string& session_key,
        std::optional<AccountEnum::Wallet> wallet = std::nullopt,
        const Jurisdiction jurisdiction = Jurisdiction::GLOBAL,
        std::shared_ptr<Logging::ILogger> logger = nullptr
    );

    HTTP::Response getAccountDetails(
        const std::string& api_key,
        const std::string& session_key,
        const Jurisdiction jurisdiction = Jurisdiction::GLOBAL,
        std::shared_ptr<Logging::ILogger> logger = nullptr
    );

    HTTP::Response getAccountStatement(
        const std::string& api_key,
        const std::string& session_key,
        std::optional<std::string> locale,
        std::optional<int> from_record,
        std::optional<int> record_count,
        std::optional<AccountType::TimeRange> item_date_range,
        std::optional<AccountEnum::IncludeItem>,
        const Jurisdiction jurisdiction = Jurisdiction::GLOBAL,
        std::shared_ptr<Logging::ILogger> logger = nullptr
    );
}