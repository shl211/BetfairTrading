#pragma once

#include <optional>
#include <string>
#include <ostream>
#include "BetfairAPI/date.h"

namespace BetfairAPI::BettingType {
    struct ItemDescription {
        std::optional<std::string> eventTypeDesc;
        std::optional<std::string> eventDesc;
        std::optional<std::string> marketDesc;
        std::optional<std::string> marketType;
        std::optional<Date> marketStartTime;
        std::optional<std::string> runnerDesc;
        std::optional<int> numberOfWinners;
        std::optional<double> eachWayDivisor;
    };

    inline bool operator==(const ItemDescription& lhs, const ItemDescription& rhs) {
        return lhs.eventTypeDesc == rhs.eventTypeDesc &&
                lhs.eventDesc == rhs.eventDesc &&
                lhs.marketDesc == rhs.marketDesc &&
                lhs.marketType == rhs.marketType &&
                lhs.marketStartTime == rhs.marketStartTime &&
                lhs.runnerDesc == rhs.runnerDesc &&
                lhs.numberOfWinners == rhs.numberOfWinners &&
                lhs.eachWayDivisor == rhs.eachWayDivisor;
    }

    inline bool operator!=(const ItemDescription& lhs, const ItemDescription& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const ItemDescription& item) {
        os << "ItemDescription{";
        os << "eventTypeDesc=" << (item.eventTypeDesc ? *item.eventTypeDesc : "null") << ", ";
        os << "eventDesc=" << (item.eventDesc ? *item.eventDesc : "null") << ", ";
        os << "marketDesc=" << (item.marketDesc ? *item.marketDesc : "null") << ", ";
        os << "marketType=" << (item.marketType ? *item.marketType : "null") << ", ";
        os << "marketStartTime=";
        if (item.marketStartTime) {
            os << item.marketStartTime->getIsoString();
        } else {
            os << "null";
        }
        os << ", runnerDesc=" << (item.runnerDesc ? *item.runnerDesc : "null") << ", ";
        os << "numberOfWinners=";
        if (item.numberOfWinners) {
            os << *item.numberOfWinners;
        } else {
            os << "null";
        }
        os << ", eachWayDivisor=";
        if (item.eachWayDivisor) {
            os << *item.eachWayDivisor;
        } else {
            os << "null";
        }
        os << "}";
        return os;
    }
}