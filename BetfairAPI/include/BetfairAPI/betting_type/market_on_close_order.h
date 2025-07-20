#pragma once

#include <ostream>

namespace BetfairAPI::BettingType {
    struct MarketOnCloseOrder {
        double liability;
    };

    inline bool operator==(const MarketOnCloseOrder& lhs, const MarketOnCloseOrder& rhs) {
        return lhs.liability == rhs.liability;
    }

    inline bool operator!=(const MarketOnCloseOrder& lhs, const MarketOnCloseOrder& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const MarketOnCloseOrder& order) {
        os << "MarketOnCloseOrder{liability=" << order.liability << "}";
        return os;
    }
}