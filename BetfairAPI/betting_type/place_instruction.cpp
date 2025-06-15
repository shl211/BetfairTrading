#include "place_instruction.h"

namespace BetfairAPI::BettingType {

    PlaceInstruction::PlaceInstruction(
        BetfairAPI::BettingEnum::OrderType order_type,
        long selection_id,
        double handicap,
        LimitOrder limit_order,
        LimitOnCloseOrder limit_on_close_order,
        MarketOnCloseOrder market_on_close_order,
        std::string_view customer_order_ref)
        : order_type_(order_type),
        selection_id_(selection_id),
        handicap_(handicap),
        limit_order_(std::move(limit_order)),
        limit_on_close_order_(std::move(limit_on_close_order)),
        market_on_close_order_(std::move(market_on_close_order)),
        customer_order_ref_(customer_order_ref) {}

    BetfairAPI::BettingEnum::OrderType PlaceInstruction::getOrderType() const {
        return order_type_;
    }

    long PlaceInstruction::getSelectionId() const {
        return selection_id_;
    }

    double PlaceInstruction::getHandicap() const {
        return handicap_;
    }

    const LimitOrder& PlaceInstruction::getLimitOrder() const {
        return limit_order_;
    }

    const LimitOnCloseOrder& PlaceInstruction::getLimitOnCloseOrder() const {
        return limit_on_close_order_;
    }

    const MarketOnCloseOrder& PlaceInstruction::getMarketOnCloseOrder() const {
        return market_on_close_order_;
    }

    const std::string& PlaceInstruction::getCustomerOrderRef() const {
        return customer_order_ref_;
    }

}