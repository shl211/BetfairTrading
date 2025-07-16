#pragma once

#include <string>
#include <ostream>

namespace BetfairAPI::BettingType {
    struct MarketTypeResult {
        std::string marketType;
        int marketCount = 0;
    };

    inline bool operator==(const MarketTypeResult& lhs, const MarketTypeResult& rhs) {
        return lhs.marketType == rhs.marketType && lhs.marketCount == rhs.marketCount;
    }

    inline bool operator!=(const MarketTypeResult& lhs, const MarketTypeResult& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const MarketTypeResult& obj) {
        return os << "Market type: " << obj.marketType << " with market count: " << obj.marketCount;
    }
}
