#pragma once

#include <ostream>

namespace BetfairAPI::BettingType {
    struct MarketVersion {
        long version = 0.0;
    };

    inline bool operator==(const MarketVersion& lhs, const MarketVersion& rhs) {
        return lhs.version == rhs.version;
    }

    inline bool operator!=(const MarketVersion& lhs, const MarketVersion& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const MarketVersion& mv) {
        os << "MarketVersion{version=" << mv.version << "}";
        return os;
    }
}