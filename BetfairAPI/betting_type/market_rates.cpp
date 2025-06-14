#include "market_rates.h"

namespace BetfairAPI::BettingType {
    MarketRates::MarketRates(double market_base_rate, bool discount_allowed) 
        : market_base_rate_(market_base_rate), discount_allowed_(discount_allowed) {}

    double MarketRates::getMarketBaseRate() const {
        return market_base_rate_;
    }

    bool MarketRates::isDiscountAllowed() const {
        return discount_allowed_;
    }


}