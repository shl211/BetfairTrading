#pragma once

#include <string>
#include <ostream>

namespace BetfairAPI::BettingType {
    struct ReplaceInstruction {
        std::string betId;
        double newPrice;
    };

    inline bool operator==(const ReplaceInstruction& lhs, const ReplaceInstruction& rhs) {
        return lhs.betId == rhs.betId && lhs.newPrice == rhs.newPrice;
    }

    inline bool operator!=(const ReplaceInstruction& lhs, const ReplaceInstruction& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const ReplaceInstruction& instr) {
        return os << "ReplaceInstruction{betId=\"" << instr.betId << "\", newPrice=" << instr.newPrice << "}";
    }
}