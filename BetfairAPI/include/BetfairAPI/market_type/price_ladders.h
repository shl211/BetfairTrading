#pragma once

#include <ostream>

namespace BetfairAPI::MarketType {
    using Price = double;
    using Size = double;
    using LadderLevel = int;

    struct DepthBasedLadder {
        LadderLevel level;
        Price price = 0;
        Size size = 0;
    };

    inline bool operator==(const DepthBasedLadder& lhs, const DepthBasedLadder& rhs) {
        return lhs.level == rhs.level && lhs.price == rhs.price && lhs.size == rhs.size;
    }

    inline bool operator!=(const DepthBasedLadder& lhs, const DepthBasedLadder& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const DepthBasedLadder& ladder) {
        os << "Level: " << ladder.level << ", Price: " << ladder.price << ", Size: " << ladder.size;
        return os;
    }

    struct PriceSize {
        Price price;
        Size size;
    };
}