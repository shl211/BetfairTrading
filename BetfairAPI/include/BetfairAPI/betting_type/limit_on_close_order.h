#pragma once

#include <ostream>

namespace BetfairAPI::BettingType {
    struct LimitOnCloseOrder {
        double liability;
        double price;
    };

    inline bool operator==(const LimitOnCloseOrder& lhs, const LimitOnCloseOrder& rhs) {
        return lhs.liability == rhs.liability && lhs.price == rhs.price;
    }

    inline bool operator!=(const LimitOnCloseOrder& lhs, const LimitOnCloseOrder& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const LimitOnCloseOrder& order) {
        os << "LimitOnCloseOrder{liability=" << order.liability << ", price=" << order.price << "}";
        return os;
    }
}