#include "order.h"

namespace BetfairAPI::BettingType {
    Order::Order(const OrderParams& params)
        : bet_id_(params.bet_id),
            order_type_(params.order_type),
            order_status_(params.order_status),
            persistence_type_(params.persistence_type),
            side_(params.side),
            price_(params.price),
            size_(params.size),
            bsp_liability_(params.bsp_liability),
            placed_date_(params.placed_date),
            avg_price_matched_(params.avg_price_matched),
            size_matched_(params.size_matched),
            size_remaining_(params.size_remaining),
            size_lapsed_(params.size_lapsed),
            size_cancelled_(params.size_cancelled),
            size_voided_(params.size_voided),
            customer_order_ref_(params.customer_order_ref),
            customer_strategy_ref_(params.customer_strategy_ref) {}

    std::string Order::getBetId() const {
        return bet_id_;
    }

    BetfairAPI::BettingEnum::OrderType Order::getOrderType() const {
        return order_type_;
    }

    BetfairAPI::BettingEnum::OrderStatus Order::getOrderStatus() const {
        return order_status_;
    }

    BetfairAPI::BettingEnum::PersistenceType Order::getPersistenceType() const {
        return persistence_type_;
    }

    BetfairAPI::BettingEnum::Side Order::getSide() const {
        return side_;
    }

    double Order::getPrice() const {
        return price_;
    }

    double Order::getSize() const {
        return size_;
    }

    double Order::getBspLiability() const {
        return bsp_liability_;
    }

    const BetfairAPI::Utils::Date& Order::getPlacedDate() const {
        return placed_date_;
    }

    double Order::getAvgPriceMatched() const {
        return avg_price_matched_;
    }

    double Order::getSizeMatched() const {
        return size_matched_;
    }

    double Order::getSizeRemaining() const {
        return size_remaining_;
    }

    double Order::getSizeLapsed() const {
        return size_lapsed_;
    }

    double Order::getSizeCancelled() const {
        return size_cancelled_;
    }

    double Order::getSizeVoided() const {
        return size_voided_;
    }

    std::string Order::getCustomerOrderRef() const {
        return customer_order_ref_;
    }

    std::string Order::getCustomerStrategyRef() const {
        return customer_strategy_ref_;
    }
}