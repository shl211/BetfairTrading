#include "price_projection.h"

namespace BetfairAPI::BettingType {

    PriceProjection::PriceProjection(
        std::vector<BetfairAPI::BettingEnum::PriceData> price_data,
        OfferOverrides override, bool virtualise, bool rollover_stakes)
        : price_data_(price_data),
            offer_overrides_(std::move(override)),
            virtualise_(virtualise),
            rollover_stakes_(rollover_stakes) {}

    const std::vector<BetfairAPI::BettingEnum::PriceData>& PriceProjection::getPriceData() const {
        return price_data_;
    }

    const OfferOverrides& PriceProjection::getOfferOverrides() const {
        return offer_overrides_;
    }

    bool PriceProjection::getVirtualise() const {
        return virtualise_;
    }

    bool PriceProjection::getRolloverStakes() const {
        return rollover_stakes_;
    }

}