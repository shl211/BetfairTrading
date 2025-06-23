#include "cancel_instruction.h"

namespace BetfairAPI::BettingType {
    CancelInstruction::CancelInstruction(std::string_view bet_id,double size_reduction) 
        : bet_id_(bet_id),size_reduction_(size_reduction) {}
        
    const std::string& CancelInstruction::getBetId() const {
        return bet_id_;
    }
    double CancelInstruction::getSizeReduction() const {
        return size_reduction_;
    }
}