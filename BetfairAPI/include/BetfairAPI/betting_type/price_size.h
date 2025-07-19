#pragma once

#include <ostream>

namespace BetfairAPI::BettingType {
    struct PriceSize {
        double price = 0.0;
        double size = 0.0;
    };

    inline bool operator==(const PriceSize& lhs, const PriceSize& rhs) {
        return lhs.price == rhs.price && lhs.size == rhs.size;
    }

    inline bool operator!=(const PriceSize& lhs, const PriceSize& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const PriceSize& ps) {
        os << "{ price: " << ps.price << ", size: " << ps.size << " }";
        return os;
    }
}