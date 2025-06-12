#include "replace_instruction.h"

namespace BetfairAPI::BettingType {
    ReplaceInstruction::ReplaceInstruction(std::string_view bet_id,double new_price)
        : bet_id_(bet_id), new_price_(new_price) {};

    std::string ReplaceInstruction::getBetId() const {
        return bet_id_;
    }

    double ReplaceInstruction::getNewPrice() const {
        return new_price_;
    }
}