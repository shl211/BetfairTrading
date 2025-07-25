#pragma once

#include <optional>
#include <ostream>

namespace BetfairAPI::AccountType {
    struct AccountFundsResponse {
        std::optional<double> availableToBetBalance;
        std::optional<double> exposure;
        std::optional<double> retainedCommission;
        std::optional<double> exposureLimit;
        std::optional<double> discountRate;
        std::optional<double> pointsBalance;
    };

    inline bool operator==(const AccountFundsResponse& lhs, const AccountFundsResponse& rhs) {
        return lhs.availableToBetBalance == rhs.availableToBetBalance &&
               lhs.exposure == rhs.exposure &&
               lhs.retainedCommission == rhs.retainedCommission &&
               lhs.exposureLimit == rhs.exposureLimit &&
               lhs.discountRate == rhs.discountRate &&
               lhs.pointsBalance == rhs.pointsBalance;
    }

    inline bool operator!=(const AccountFundsResponse& lhs, const AccountFundsResponse& rhs) {
        return !(lhs == rhs);
    }

    #include <ostream>

    inline std::ostream& operator<<(std::ostream& os, const AccountFundsResponse& afr) {
        os << "AccountFundsResponse{"
           << "availableToBetBalance=" << (afr.availableToBetBalance ? std::to_string(*afr.availableToBetBalance) : "nullopt") << ", "
           << "exposure=" << (afr.exposure ? std::to_string(*afr.exposure) : "nullopt") << ", "
           << "retainedCommission=" << (afr.retainedCommission ? std::to_string(*afr.retainedCommission) : "nullopt") << ", "
           << "exposureLimit=" << (afr.exposureLimit ? std::to_string(*afr.exposureLimit) : "nullopt") << ", "
           << "discountRate=" << (afr.discountRate ? std::to_string(*afr.discountRate) : "nullopt") << ", "
           << "pointsBalance=" << (afr.pointsBalance ? std::to_string(*afr.pointsBalance) : "nullopt")
           << "}";
        return os;
    }
}