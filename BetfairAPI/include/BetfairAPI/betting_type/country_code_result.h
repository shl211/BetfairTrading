#pragma once

#include <string>
#include <ostream>

namespace BetfairAPI::BettingType {
    struct CountryCodeResult {
        std::string countryCode;
        int marketCount;
    };

    inline bool operator==(const CountryCodeResult& lhs, const CountryCodeResult& rhs) {
        return lhs.countryCode == rhs.countryCode && lhs.marketCount == rhs.marketCount;
    }

    inline bool operator!=(const CountryCodeResult& lhs, const CountryCodeResult& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const CountryCodeResult& obj) {
        return os << "Country code: " << obj.countryCode << " with market count " << obj.marketCount;
    }
}