#pragma once

#include <string>

namespace BetfairAPI::BettingType {
    class ReplaceInstruction {
        public:
            ReplaceInstruction(std::string_view bet_id,double new_price);
            ~ReplaceInstruction() = default;
            ReplaceInstruction(const ReplaceInstruction&) = default;
            ReplaceInstruction(ReplaceInstruction&&) noexcept = default;
            ReplaceInstruction& operator=(const ReplaceInstruction&) = default;
            ReplaceInstruction& operator=(ReplaceInstruction&&) noexcept = default;

            std::string getBetId() const;
            double getNewPrice() const;

        private:
            std::string bet_id_;
            double new_price_;//price to replace bet at
            
    };
}