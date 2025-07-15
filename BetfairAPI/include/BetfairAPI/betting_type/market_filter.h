#pragma once

#include <string>
#include <set>
#include <optional>

#include "BetfairAPI/betting_enum/market_betting_type.hpp"
#include "BetfairAPI/betting_enum/order_status.hpp"
#include "time_range.h"

namespace BetfairAPI::BettingType {
    struct MarketFilter {
        std::string textQuery;
        std::set<std::string> eventTypeIds;
        std::set<std::string> eventIds;
        std::set<std::string> competitionIds;
        std::set<std::string> marketIds;
        std::set<std::string> venues;
        std::optional<bool> bspOnly = std::nullopt;
        std::optional<bool> turnInPlayEnabled = std::nullopt;
        std::optional<bool> inPlayOnly = std::nullopt;
        std::set<BettingEnum::MarketBettingType> marketBettingTypes;
        std::set<std::string> marketCountries;
        std::set<std::string> marketTypeCodes;
        std::optional<TimeRange> marketStartTime;
        std::set<BettingEnum::OrderStatus> withOrders;
        std::set<std::string> raceTypes;
    };
}