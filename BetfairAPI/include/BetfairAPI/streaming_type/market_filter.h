#pragma once

#include <string>
#include <ostream>
#include <optional>
#include <set>

#include "BetfairAPI/streaming_enum/betting_type.hpp"
#include "BetfairAPI/utils.h"

namespace BetfairAPI::StreamingType {
    struct MarketFilter {
        std::set<std::string> marketIds;
        std::optional<bool> bspMarket;
        std::set<StreamingEnum::BettingType> bettingTypes;
        std::set<std::string> eventTypeIds;
        std::set<std::string> eventIds;
        std::optional<bool> turnInPlayEnabled;
        std::set<std::string> marketTypes;
        std::set<std::string> venues;
        std::set<std::string> countryCodes;
        std::set<std::string> raceTypes;
    };

    inline bool operator==(const MarketFilter& lhs, const MarketFilter& rhs) {
        return lhs.marketIds == rhs.marketIds &&
               lhs.bspMarket == rhs.bspMarket &&
               lhs.bettingTypes == rhs.bettingTypes &&
               lhs.eventTypeIds == rhs.eventTypeIds &&
               lhs.eventIds == rhs.eventIds &&
               lhs.turnInPlayEnabled == rhs.turnInPlayEnabled &&
               lhs.marketTypes == rhs.marketTypes &&
               lhs.venues == rhs.venues &&
               lhs.countryCodes == rhs.countryCodes &&
               lhs.raceTypes == rhs.raceTypes;
    }

    inline bool operator!=(const MarketFilter& lhs, const MarketFilter& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const MarketFilter& filter) {
        os << "MarketFilter{";
        os << "marketIds:[";
        for (auto it = filter.marketIds.begin(); it != filter.marketIds.end(); ++it) {
            if (it != filter.marketIds.begin()) os << ",";
            os << *it;
        }
        os << "],bspMarket:";
        if (filter.bspMarket.has_value()) os << std::boolalpha << filter.bspMarket.value();
        else os << "null";
        os << ",bettingTypes:[";
        for (auto it = filter.bettingTypes.begin(); it != filter.bettingTypes.end(); ++it) {
            if (it != filter.bettingTypes.begin()) os << ",";
            os << BetfairAPI::to_string(*it);
        }
        os << "],eventTypeIds:[";
        for (auto it = filter.eventTypeIds.begin(); it != filter.eventTypeIds.end(); ++it) {
            if (it != filter.eventTypeIds.begin()) os << ",";
            os << *it;
        }
        os << "],eventIds:[";
        for (auto it = filter.eventIds.begin(); it != filter.eventIds.end(); ++it) {
            if (it != filter.eventIds.begin()) os << ",";
            os << *it;
        }
        os << "],turnInPlayEnabled:";
        if (filter.turnInPlayEnabled.has_value()) os << std::boolalpha << filter.turnInPlayEnabled.value();
        else os << "null";
        os << ",marketTypes:[";
        for (auto it = filter.marketTypes.begin(); it != filter.marketTypes.end(); ++it) {
            if (it != filter.marketTypes.begin()) os << ",";
            os << *it;
        }
        os << "],venues:[";
        for (auto it = filter.venues.begin(); it != filter.venues.end(); ++it) {
            if (it != filter.venues.begin()) os << ",";
            os << *it;
        }
        os << "],countryCodes:[";
        for (auto it = filter.countryCodes.begin(); it != filter.countryCodes.end(); ++it) {
            if (it != filter.countryCodes.begin()) os << ",";
            os << *it;
        }
        os << "],raceTypes:[";
        for (auto it = filter.raceTypes.begin(); it != filter.raceTypes.end(); ++it) {
            if (it != filter.raceTypes.begin()) os << ",";
            os << *it;
        }
        os << "]}";
        return os;
    }
}