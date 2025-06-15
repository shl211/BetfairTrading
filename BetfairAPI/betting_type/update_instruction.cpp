#include "update_instruction.h"

namespace BetfairAPI::BettingType {
    UpdateInstruction::UpdateInstruction(std::string_view bet_id, BetfairAPI::BettingEnum::PersistenceType new_persistence_type)
        : bet_id_(bet_id), new_persistence_type_(new_persistence_type) {};

    bool UpdateInstruction::operator==(const UpdateInstruction& other) const {
        return bet_id_ == other.bet_id_ &&
                new_persistence_type_ == other.new_persistence_type_;
    }

    bool UpdateInstruction::operator!=(const UpdateInstruction& other) const {
        return !(*this == other);
    }

    std::string UpdateInstruction::getBetId() const {
        return bet_id_;
    }

    BetfairAPI::BettingEnum::PersistenceType UpdateInstruction::getNewPersistenceType() const {
        return new_persistence_type_;
    }
}