#pragma once

#include <ostream>
#include "BetfairAPI/betting_type/market_version.h"

namespace BetfairAPI::BettingType {
    struct CurrentItemDescription {
        MarketVersion marketVersion;
    };

    inline bool operator==(const CurrentItemDescription& lhs, const CurrentItemDescription& rhs) {
        return lhs.marketVersion == rhs.marketVersion;
    }

    inline bool operator!=(const CurrentItemDescription& lhs, const CurrentItemDescription& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const CurrentItemDescription& cid) {
        os << "CurrentItemDescription{ marketVersion: " << cid.marketVersion << " }";
        return os;
    }
}
