#pragma once

#include <optional>
#include <ostream>
#include "BetfairAPI/utils.h"
#include "BetfairAPI/betting_enum/order_type.hpp"
#include "BetfairAPI/betting_enum/side.hpp"
#include "BetfairAPI/betting_type/limit_order.h"
#include "BetfairAPI/betting_type/limit_on_close_order.h"
#include "BetfairAPI/betting_type/market_on_close_order.h"

namespace BetfairAPI::BettingType {
    struct PlaceInstruction {
        BettingEnum::OrderType orderType;
        long selectionId;
        BettingEnum::Side side;
        std::optional<double> handicap;
        std::optional<LimitOrder> limitOrder;
        std::optional<LimitOnCloseOrder> limitOnCloseOrder;
        std::optional<MarketOnCloseOrder> marketOnCloseOrder;
        std::optional<std::string> customerOrderRef;
    };

    inline bool operator==(const PlaceInstruction& lhs, const PlaceInstruction& rhs) {
        return lhs.orderType == rhs.orderType &&
                lhs.selectionId == rhs.selectionId &&
                lhs.side == rhs.side &&
                lhs.handicap == rhs.handicap &&
                lhs.limitOrder == rhs.limitOrder &&
                lhs.limitOnCloseOrder == rhs.limitOnCloseOrder &&
                lhs.marketOnCloseOrder == rhs.marketOnCloseOrder &&
                lhs.customerOrderRef == rhs.customerOrderRef;
    }

    inline bool operator!=(const PlaceInstruction& lhs, const PlaceInstruction& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const PlaceInstruction& pi) {
        os << "PlaceInstruction{"
            << "orderType: " << to_string(pi.orderType)
            << ", selectionId: " << pi.selectionId
            << ", side: " << to_string(pi.side)
            << ", handicap: " << (pi.handicap ? std::to_string(*pi.handicap) : "null")
            << ", limitOrder: " << (pi.limitOrder ? "set" : "null")
            << ", limitOnCloseOrder: " << (pi.limitOnCloseOrder ? "set" : "null")
            << ", marketOnCloseOrder: " << (pi.marketOnCloseOrder ? "set" : "null")
            << ", customerOrderRef: " << (pi.customerOrderRef ? *pi.customerOrderRef : "null")
            << "}";
        return os;
    }
}