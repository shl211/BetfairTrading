#include "limit_order.h"

#include "utils/math_utils.hpp"

namespace BetfairAPI::BettingType {

    LimitOrder::LimitOrder(double size, double price, BetfairAPI::BettingEnum::PersistenceType persistence_type,
                        BetfairAPI::BettingEnum::TimeInForce time_in_force, double min_fill_size,
                        BetfairAPI::BettingEnum::BetTargetType bet_target_type, double bet_target_size)
        : size_(size),
        price_(price),
        persistence_type_(persistence_type),
        time_in_force_(time_in_force),
        min_fill_size_(min_fill_size),
        bet_target_type_(bet_target_type),
        bet_target_size_(bet_target_size) {}

    bool LimitOrder::operator==(const LimitOrder& other) const {
        return BetfairAPI::Utils::almostEqual(size_,other.size_) &&
                BetfairAPI::Utils::almostEqual(price_,other.price_) &&
                persistence_type_ == other.persistence_type_ &&
                time_in_force_ == other.time_in_force_ &&
                BetfairAPI::Utils::almostEqual(min_fill_size_,other.min_fill_size_) &&
                bet_target_type_ == other.bet_target_type_ &&
                BetfairAPI::Utils::almostEqual(bet_target_size_,other.bet_target_size_);
    }

    bool LimitOrder::operator!=(const LimitOrder& other) const {
        return !(*this == other);
    }

    double LimitOrder::getSize() const {
        return size_;
    }

    double LimitOrder::getPrice() const {
        return price_;
    }

    BetfairAPI::BettingEnum::PersistenceType LimitOrder::getPersistenceType() const {
        return persistence_type_;
    }

    BetfairAPI::BettingEnum::TimeInForce LimitOrder::getTimeInForce() const {
        return time_in_force_;
    }

    double LimitOrder::getMinFillSize() const {
        return min_fill_size_;
    }

    BetfairAPI::BettingEnum::BetTargetType LimitOrder::getBetTargetType() const {
        return bet_target_type_;
    }

    double LimitOrder::getBetTargetSize() const {
        return bet_target_size_;
    }

}