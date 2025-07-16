#pragma once

#include <string>
#include <ostream>

namespace BetfairAPI::BettingType {
    struct VenueResult {
        std::string venue;
        int marketCount = 0;
    };

    inline bool operator==(const VenueResult& lhs, const VenueResult& rhs) {
        return lhs.venue == rhs.venue && lhs.marketCount == rhs.marketCount;
    }

    inline bool operator!=(const VenueResult& lhs, const VenueResult& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const VenueResult& vr) {
        return os << "Venue result: " << vr.venue << " with market count " << vr.marketCount;
    }
}