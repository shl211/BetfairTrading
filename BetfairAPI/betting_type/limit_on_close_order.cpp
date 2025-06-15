#include "limit_on_close_order.h"

#include "utils/math_utils.hpp"

namespace BetfairAPI::BettingType {
    LimitOnCloseOrder::LimitOnCloseOrder(double liability, double price)
        : liability_(liability), price_(price) {}

    bool LimitOnCloseOrder::operator==(const LimitOnCloseOrder& other) const {
        return BetfairAPI::Utils::almostEqual(liability_,other.liability_) && 
            BetfairAPI::Utils::almostEqual(price_,other.price_);
    }

    bool LimitOnCloseOrder::operator!=(const LimitOnCloseOrder& other) const {
        return !(*this == other);
    }

    double LimitOnCloseOrder::getLiability() const {
        return liability_;
    }

    double LimitOnCloseOrder::getPrice() const {
        return price_;
    }
}