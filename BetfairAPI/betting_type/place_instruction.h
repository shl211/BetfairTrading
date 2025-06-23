#pragma once

#include <string>
#include "betting_enum/order_type.hpp"
#include "betting_enum/side.hpp"
#include "limit_order.h"
#include "limit_on_close_order.h"
#include "market_on_close_order.h"

namespace BetfairAPI::BettingType {
    class PlaceInstruction {
        public:
            PlaceInstruction(BetfairAPI::BettingEnum::OrderType order_type, long selection_id,
                double handicap,LimitOrder limit_order, LimitOnCloseOrder limit_on_close_order,
                MarketOnCloseOrder market_on_close_order, std::string_view customer_order_ref);
            PlaceInstruction() = default;
            ~PlaceInstruction() = default;
            PlaceInstruction(const PlaceInstruction&) = default;
            PlaceInstruction(PlaceInstruction&&) noexcept = default;
            PlaceInstruction& operator=(const PlaceInstruction&) = default;
            PlaceInstruction& operator=(PlaceInstruction&&) noexcept = default;
            
            BetfairAPI::BettingEnum::OrderType getOrderType() const;
            long getSelectionId() const;
            double getHandicap() const;
            const LimitOrder& getLimitOrder() const;
            const LimitOnCloseOrder& getLimitOnCloseOrder() const;
            const MarketOnCloseOrder& getMarketOnCloseOrder() const;
            const std::string& getCustomerOrderRef() const;
        
        private:
            BetfairAPI::BettingEnum::OrderType order_type_;
            long selection_id_;
            double handicap_;
            LimitOrder limit_order_;
            LimitOnCloseOrder limit_on_close_order_;
            MarketOnCloseOrder market_on_close_order_;
            std::string customer_order_ref_;
    };
}