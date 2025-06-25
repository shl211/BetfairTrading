#pragma once

#include "betting_enum/price_ladder_type.hpp"

namespace BetfairAPI::BettingType {
    class PriceLadderDescription {
        public:
            explicit PriceLadderDescription(BetfairAPI::BettingEnum::PriceLadderType type);
            PriceLadderDescription() = default;
            ~PriceLadderDescription() = default;
            PriceLadderDescription(const PriceLadderDescription&) = default;
            PriceLadderDescription(PriceLadderDescription&&) noexcept = default;
            PriceLadderDescription& operator=(const PriceLadderDescription&) = default;
            PriceLadderDescription& operator=(PriceLadderDescription&&) noexcept = default;

            BetfairAPI::BettingEnum::PriceLadderType getType() const;

        private:
            BetfairAPI::BettingEnum::PriceLadderType type_;
    };
}