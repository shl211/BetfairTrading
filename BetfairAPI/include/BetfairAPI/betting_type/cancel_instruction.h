#pragma once

#include <string>
#include <optional>
#include <ostream>

namespace BetfairAPI::BettingType {
    struct CancelInstruction {
        std::string betId;
        std::optional<double> sizeReduction = std::nullopt;
    };

    inline bool operator==(const CancelInstruction& lhs, const CancelInstruction& rhs) {
        return lhs.betId == rhs.betId && lhs.sizeReduction == rhs.sizeReduction;
    }

    inline bool operator!=(const CancelInstruction& lhs, const CancelInstruction& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const CancelInstruction& ci) {
        os << "CancelInstruction{betId=" << ci.betId << ", sizeReduction=";
        if (ci.sizeReduction.has_value()) {
            os << ci.sizeReduction.value();
        } else {
            os << "nullopt";
        }
        os << "}";
        return os;
    }
}