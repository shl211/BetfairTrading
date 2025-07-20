#pragma once

#include <optional>
#include <string>
#include <ostream>

namespace BetfairAPI::BettingType {
    struct RunnerId {
        std::string marketId;
        long selectionId;
        std::optional<double> handicap;
    };

    inline bool operator==(const RunnerId& lhs, const RunnerId& rhs) {
        return lhs.marketId == rhs.marketId &&
                lhs.selectionId == rhs.selectionId &&
                lhs.handicap == rhs.handicap;
    }

    inline bool operator!=(const RunnerId& lhs, const RunnerId& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const RunnerId& runner) {
        os << "RunnerId{marketId=" << runner.marketId
            << ", selectionId=" << runner.selectionId
            << ", handicap=";
        if (runner.handicap.has_value()) {
            os << runner.handicap.value();
        } else {
            os << "nullopt";
        }
        os << "}";
        return os;
    }
}