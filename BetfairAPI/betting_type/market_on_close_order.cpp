#include "market_on_close_order.h"

namespace BetfairAPI::BettingType {

    MarketOnCloseOrder::MarketOnCloseOrder(double liability)
        : liability_(liability) {}

    double MarketOnCloseOrder::getLiability() const {
        return liability_;
    }
}