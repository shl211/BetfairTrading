#pragma once

#include <vector>
#include "betting_enum/price_data.hpp"
#include "offer_overrides.h"

namespace BetfairAPI::BettingType {
    class PriceProjection {
        public:
            PriceProjection(std::vector<BetfairAPI::BettingEnum::PriceData> price_data,
                OfferOverrides override, bool virtualise, bool rollover_stakes);
            ~PriceProjection() = default;
            PriceProjection(const PriceProjection&) = default;
            PriceProjection& operator=(const PriceProjection&) = default;
            PriceProjection(PriceProjection&&) = default;
            PriceProjection& operator=(PriceProjection&&) = default;

            const std::vector<BetfairAPI::BettingEnum::PriceData>& getPriceData() const;
            const OfferOverrides& getOfferOverrides() const;
            bool getVirtualise() const;
            bool getRolloverStakes() const;

        private:
            std::vector<BetfairAPI::BettingEnum::PriceData> price_data_;
            OfferOverrides offer_overrides_;
            bool virtualise_;
            bool rollover_stakes_;
    };
}
