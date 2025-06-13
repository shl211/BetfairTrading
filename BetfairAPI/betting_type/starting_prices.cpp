#include "starting_prices.h"

namespace BetfairAPI::BettingType {
    StartingPrices::StartingPrices(double near_price,double far_price,double actual_sp,
                std::vector<PriceSize> back_stake_taken, std::vector<PriceSize> lay_liability_taken)
                    : near_price_(near_price), far_price_(far_price), actual_sp_(actual_sp),
                    back_stake_taken_(back_stake_taken), lay_liability_taken_(lay_liability_taken) {};
                    
    double StartingPrices::getNearPrice() const {
        return near_price_;
    }

    double StartingPrices::getFarPrice() const {
        return far_price_;
    }

    double StartingPrices::getActualSP() const {
        return actual_sp_;
    }

    const std::vector<PriceSize>& StartingPrices::getBackStakeTaken() const {
        return back_stake_taken_;
    }

    const std::vector<PriceSize>& StartingPrices::getLayLiabilityTaken() const {
        return lay_liability_taken_;
    }
}