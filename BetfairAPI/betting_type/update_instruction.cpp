#include "update_instruction.h"

namespace BetfairAPI::BettingType {
    UpdateInstruction::UpdateInstruction(std::string_view bet_id, BetfairAPI::BettingEnum::PersistenceType new_persistence_type)
        : bet_id_(bet_id), new_persistence_type_(new_persistence_type) {};

    std::string UpdateInstruction::getBetId() const {
        return bet_id_;
    }

    BetfairAPI::BettingEnum::PersistenceType UpdateInstruction::getNewPersistenceType() const {
        return new_persistence_type_;
    }
}