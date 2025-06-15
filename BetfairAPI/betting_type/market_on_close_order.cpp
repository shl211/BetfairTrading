#include "market_on_close_order.h"

#include "utils/math_utils.hpp"

namespace BetfairAPI::BettingType {

    MarketOnCloseOrder::MarketOnCloseOrder(double liability)
        : liability_(liability) {}

    bool MarketOnCloseOrder::operator==(const MarketOnCloseOrder& other) const {
        return BetfairAPI::Utils::almostEqual(liability_,other.liability_);
    }

    bool MarketOnCloseOrder::operator!=(const MarketOnCloseOrder& other) const {
        return !(*this == other);
    }

    double MarketOnCloseOrder::getLiability() const {
        return liability_;
    }
}