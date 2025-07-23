#pragma once

#include <string>
#include <optional>
#include "BetfairAPI/betting_enum/order_type.hpp"
#include "BetfairAPI/betting_enum/order_status.hpp"
#include "BetfairAPI/betting_enum/side.hpp"
#include "BetfairAPI/betting_enum/persistence_type.hpp"
#include "BetfairAPI/date.h"
#include "BetfairAPI/utils.h"

namespace BetfairAPI::BettingType {
    struct Order {
        std::string betId;
        BettingEnum::OrderType orderType;
        BettingEnum::OrderStatus status;
        BettingEnum::PersistenceType persistenceType;
        BettingEnum::Side side;
        double price;
        double size;
        double bspLiability;
        std::optional<Date> placedDate;
        std::optional<double> avgPriceMatched;
        std::optional<double> sizeMatched;
        std::optional<double> sizeRemaining;
        std::optional<double> sizeLapsed;
        std::optional<double> sizeCancelled;
        std::optional<double> sizeVoided;
        std::optional<std::string> customerOrderRef;
        std::optional<std::string> customerStrategyRef;
    };

    inline bool operator==(const Order& lhs, const Order& rhs) {
        return lhs.betId == rhs.betId &&
               lhs.orderType == rhs.orderType &&
               lhs.status == rhs.status &&
               lhs.persistenceType == rhs.persistenceType &&
               lhs.side == rhs.side &&
               lhs.price == rhs.price &&
               lhs.size == rhs.size &&
               lhs.bspLiability == rhs.bspLiability &&
               lhs.placedDate == rhs.placedDate &&
               lhs.avgPriceMatched == rhs.avgPriceMatched &&
               lhs.sizeMatched == rhs.sizeMatched &&
               lhs.sizeRemaining == rhs.sizeRemaining &&
               lhs.sizeLapsed == rhs.sizeLapsed &&
               lhs.sizeCancelled == rhs.sizeCancelled &&
               lhs.sizeVoided == rhs.sizeVoided &&
               lhs.customerOrderRef == rhs.customerOrderRef &&
               lhs.customerStrategyRef == rhs.customerStrategyRef;
    }

    inline bool operator!=(const Order& lhs, const Order& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const Order& order) {
        os << "Order{"
           << "betId: " << order.betId
           << ", orderType: " << to_string(order.orderType)
           << ", status: " << to_string(order.status)
           << ", persistenceType: " << to_string(order.persistenceType)
           << ", side: " << to_string(order.side)
           << ", price: " << order.price
           << ", size: " << order.size
           << ", bspLiability: " << order.bspLiability
           << ", placedDate: " << (order.placedDate ? order.placedDate->getIsoString() : "null")
           << ", avgPriceMatched: " << (order.avgPriceMatched ? std::to_string(*order.avgPriceMatched) : "null")
           << ", sizeMatched: " << (order.sizeMatched ? std::to_string(*order.sizeMatched) : "null")
           << ", sizeRemaining: " << (order.sizeRemaining ? std::to_string(*order.sizeRemaining) : "null")
           << ", sizeLapsed: " << (order.sizeLapsed ? std::to_string(*order.sizeLapsed) : "null")
           << ", sizeCancelled: " << (order.sizeCancelled ? std::to_string(*order.sizeCancelled) : "null")
           << ", sizeVoided: " << (order.sizeVoided ? std::to_string(*order.sizeVoided) : "null")
           << ", customerOrderRef: " << (order.customerOrderRef ? *order.customerOrderRef : "null")
           << ", customerStrategyRef: " << (order.customerStrategyRef ? *order.customerStrategyRef : "null")
           << "}";
        return os;
    }
}