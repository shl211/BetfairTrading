#pragma once

#include <vector>
#include "price_size.h"

namespace BetfairAPI::BettingType {
    class StartingPrices {
        public:
            StartingPrices(double near_price,double far_price,double actual_sp,
                std::vector<PriceSize> back_stake_taken, std::vector<PriceSize> lay_liability_taken);
            ~StartingPrices() = default;

            StartingPrices(const StartingPrices&) = default;
            StartingPrices(StartingPrices&&) noexcept = default;
            StartingPrices& operator=(const StartingPrices&) = default;
            StartingPrices& operator=(StartingPrices&&) noexcept = default;

            double getNearPrice() const;
            double getFarPrice() const;
            double getActualSP() const;
            const std::vector<PriceSize>& getBackStakeTaken() const;
            const std::vector<PriceSize>& getLayLiabilityTaken() const;

        private:
            double near_price_;//What the starting price would be if the market was reconciled now taking into account the SP bets as well as unmatched exchange bets on the same selection in the exchange. This data is cached and update every 60 seconds.
            double far_price_;//What the starting price would be if the market was reconciled now taking into account only the currently place SP bets. The Far Price is not as complicated but not as accurate and only accounts for money on the exchange at SP. This data is cached and updated every 60 seconds. 
            double actual_sp_;//The final BSP price for this runner. Only available for a BSP market that has been reconciled. Please note: for REMOVED runners the actualSP will be returned as 'NaN. Value may be returned as 'Infinity' if no BSP can be calculated.
            std::vector<PriceSize> back_stake_taken_;//The total amount of back bets matched at the actual Betfair Starting Price. Pre-reconciliation, this field is zero for all prices except 1.01 (for Market on Close bets) and at the limit price for any Limit on Close bets.
            std::vector<PriceSize> lay_liability_taken_;//The lay amount matched at the actual Betfair Starting Price. Pre-reconciliation, this field is zero for all prices except 1000 (for Market on Close bets) and at the limit price for any Limit on Close bets.
    };
}