#pragma once

#include <string>

namespace BetfairAPI::BettingType {
    class CancelInstruction {
        public:
            CancelInstruction(std::string_view bet_id,double size_reduction);
            ~CancelInstruction() = default;
            CancelInstruction(const CancelInstruction&) = default;
            CancelInstruction(CancelInstruction&&) noexcept = default;
            CancelInstruction& operator=(const CancelInstruction&) = default;
            CancelInstruction& operator=(CancelInstruction&&) noexcept = default;
        
            const std::string& getBetId() const;
            double getSizeReduction() const;
        
        private:
            std::string bet_id_;
            double size_reduction_;
    };
}