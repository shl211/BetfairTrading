#pragma once

#include <string>

namespace BetfairAPI::BettingType {
    class OfferOverrides {
        public:
            OfferOverrides(int best_price_depth,int rollup_limit,
                double rollup_liability_threshold,int rollup_liability_factor);
            ~OfferOverrides() = default;
            OfferOverrides(const OfferOverrides&) = default;
            OfferOverrides(OfferOverrides&&) noexcept= default;
            OfferOverrides& operator=(const OfferOverrides&) = default;
            OfferOverrides& operator=(OfferOverrides&&) noexcept = default;
            
            int getBestPricesDepth() const;
            const std::string& getRollupModel() const;
            int getRollupLimit() const;
            double getRollupLiabilityThreshold() const;
            int getRollupLiabilityFactor() const;
        
            private:
            int best_prices_depth_;
            std::string rollup_model_ = "STAKE";//unsure what it should be
            int rollup_limit_;
            double rollup_liability_threshold_;
            int rollup_liability_factor_;
    };
}