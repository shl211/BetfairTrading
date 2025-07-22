#pragma once

#include <optional>
#include <ostream>
#include "BetfairAPI/utils.h"
#include "BetfairAPI/betting_enum/persistence_type.hpp"
#include "BetfairAPI/betting_enum/time_in_force.hpp"
#include "BetfairAPI/betting_enum/bet_target_type.hpp"

namespace BetfairAPI::BettingType {
    struct LimitOrder {
        double price;
        double size;
        BettingEnum::PersistenceType persistenceType;
        std::optional<BettingEnum::TimeInForce> timeInForce = std::nullopt;
        std::optional<double> minFillSize = std::nullopt;
        std::optional<BettingEnum::BetTargetType> betTargetType = std::nullopt;
        std::optional<double> betTargetSize = std::nullopt;
    };

    inline bool operator==(const LimitOrder& lhs, const LimitOrder& rhs) {
        constexpr double EPSILON = 1e-9;
        auto double_eq = [](double a, double b) { return std::abs(a - b) < EPSILON; };

        return double_eq(lhs.price, rhs.price) &&
               double_eq(lhs.size, rhs.size) &&
               lhs.persistenceType == rhs.persistenceType &&
               lhs.timeInForce == rhs.timeInForce &&
               ((!lhs.minFillSize && !rhs.minFillSize) ||
            (lhs.minFillSize && rhs.minFillSize && double_eq(*lhs.minFillSize, *rhs.minFillSize))) &&
               lhs.betTargetType == rhs.betTargetType &&
               ((!lhs.betTargetSize && !rhs.betTargetSize) ||
            (lhs.betTargetSize && rhs.betTargetSize && double_eq(*lhs.betTargetSize, *rhs.betTargetSize)));
    }

    inline bool operator!=(const LimitOrder& lhs, const LimitOrder& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const LimitOrder& order) {
        os << "LimitOrder{price=" << order.price
            << ", size=" << order.size
            << ", persistenceType=" << to_string(order.persistenceType)
            << ", timeInForce=";
        if (order.timeInForce)
            os << to_string(*order.timeInForce);
        else
            os << "nullopt";
        os << ", minFillSize=";
        if (order.minFillSize)
            os << *order.minFillSize;
        else
            os << "nullopt";
        os << ", betTargetType=";
        if (order.betTargetType)
            os << to_string(*order.betTargetType);
        else
            os << "nullopt";
        os << ", betTargetSize=";
        if (order.betTargetSize)
            os << *order.betTargetSize;
        else
            os << "nullopt";
        os << "}";
        return os;
    }
}