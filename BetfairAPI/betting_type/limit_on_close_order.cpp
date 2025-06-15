#include "limit_on_close_order.h"

namespace BetfairAPI::BettingType {
    LimitOnCloseOrder::LimitOnCloseOrder(double liability, double price)
        : liability_(liability), price_(price) {}

    double LimitOnCloseOrder::getLiability() const {
        return liability_;
    }

    double LimitOnCloseOrder::getPrice() const {
        return price_;
    }
}