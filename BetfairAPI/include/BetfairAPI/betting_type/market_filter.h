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

    inline bool operator==(const MarketFilter& lhs, const MarketFilter& rhs) {
        return lhs.textQuery == rhs.textQuery &&
                lhs.eventTypeIds == rhs.eventTypeIds &&
                lhs.eventIds == rhs.eventIds &&
                lhs.competitionIds == rhs.competitionIds &&
                lhs.marketIds == rhs.marketIds &&
                lhs.venues == rhs.venues &&
                lhs.bspOnly == rhs.bspOnly &&
                lhs.turnInPlayEnabled == rhs.turnInPlayEnabled &&
                lhs.inPlayOnly == rhs.inPlayOnly &&
                lhs.marketBettingTypes == rhs.marketBettingTypes &&
                lhs.marketCountries == rhs.marketCountries &&
                lhs.marketTypeCodes == rhs.marketTypeCodes &&
                lhs.marketStartTime == rhs.marketStartTime &&
                lhs.withOrders == rhs.withOrders &&
                lhs.raceTypes == rhs.raceTypes;
    }

    inline bool operator!=(const MarketFilter& lhs, const MarketFilter& rhs) {
        return !(lhs == rhs);
    }
}