#include "offer_overrides.h"

namespace BetfairAPI::BettingType {

    OfferOverrides::OfferOverrides(int best_price_depth, int rollup_limit,
        double rollup_liability_threshold, int rollup_liability_factor)
        : best_prices_depth_(best_price_depth),
        rollup_limit_(rollup_limit),
        rollup_liability_threshold_(rollup_liability_threshold),
        rollup_liability_factor_(rollup_liability_factor) {}

    int OfferOverrides::getBestPricesDepth() const {
        return best_prices_depth_;
    }

    const std::string& OfferOverrides::getRollupModel() const {
        return rollup_model_;
    }

    int OfferOverrides::getRollupLimit() const {
        return rollup_limit_;
    }

    double OfferOverrides::getRollupLiabilityThreshold() const {
        return rollup_liability_threshold_;
    }

    int OfferOverrides::getRollupLiabilityFactor() const {
        return rollup_liability_factor_;
    }

}