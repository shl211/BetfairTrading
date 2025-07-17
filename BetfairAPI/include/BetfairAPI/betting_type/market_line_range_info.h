#pragma once

#include <string>
#include <ostream>

namespace BetfairAPI::BettingType {
    struct MarketLineRangeInfo {
        double maxUnitValue;
        double minUnitValue;
        double interval;
        std::string marketUnit;
    };

    inline bool operator==(const MarketLineRangeInfo& lhs, const MarketLineRangeInfo& rhs) {
        return lhs.maxUnitValue == rhs.maxUnitValue &&
                lhs.minUnitValue == rhs.minUnitValue &&
                lhs.interval == rhs.interval &&
                lhs.marketUnit == rhs.marketUnit;
    }

    inline bool operator!=(const MarketLineRangeInfo& lhs, const MarketLineRangeInfo& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const MarketLineRangeInfo& info) {
        os << "Market Line/Range Info: maxUnitVal=" << info.maxUnitValue
            << ", minUnitVal=" << info.minUnitValue
            << ", interval=" << info.interval
            << ", marketUnit=" << info.marketUnit;
        return os;
    }
}