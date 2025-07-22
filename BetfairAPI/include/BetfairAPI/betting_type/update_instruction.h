#pragma once

#include <string>
#include <ostream>
#include "BetfairAPI/betting_enum/persistence_type.hpp"

namespace BetfairAPI::BettingType {
    struct UpdateInstruction {
        std::string betId;
        BettingEnum::PersistenceType newPersistenceType;
    };

    inline bool operator==(const UpdateInstruction& lhs, const UpdateInstruction& rhs) {
        return lhs.betId == rhs.betId &&
               lhs.newPersistenceType == rhs.newPersistenceType;
    }

    inline bool operator!=(const UpdateInstruction& lhs, const UpdateInstruction& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const UpdateInstruction& ui) {
        return os << "UpdateInstruction{betId=" << ui.betId
                  << ", newPersistenceType=" << static_cast<int>(ui.newPersistenceType) << "}";
    }
}