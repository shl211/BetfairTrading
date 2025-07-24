#pragma once

#include <optional>
#include <string>
#include <ostream>
#include "BetfairAPI/utils.h"
#include "BetfairAPI/date.h"
#include "BetfairAPI/betting_enum/persistence_type.hpp"
#include "BetfairAPI/betting_enum/order_type.hpp"
#include "BetfairAPI/betting_enum/side.hpp"
#include "BetfairAPI/betting_type/item_description.h"

namespace BetfairAPI::BettingType {
    struct ClearedOrderSummary {
        std::optional<std::string> eventTypeId;
        std::optional<std::string> eventId;
        std::optional<std::string> marketId;
        std::optional<long> selectionId;
        std::optional<double> handicap;
        std::optional<std::string> betId;
        std::optional<Date> placedDate;
        std::optional<BettingEnum::PersistenceType> persistenceType;
        std::optional<BettingEnum::OrderType> orderType;
        std::optional<BettingEnum::Side> side;
        std::optional<ItemDescription> itemDescription;
        std::optional<std::string> betOutcome;
        std::optional<double> priceRequested;
        std::optional<Date> settledDate;
        std::optional<Date> lastMatchedDate;
        std::optional<int> betCount;
        std::optional<double> commission;
        std::optional<double> priceMatched;
        std::optional<bool> priceReduced;
        std::optional<double> sizeSettled;
        std::optional<double> profit;
        std::optional<double> sizeCancelled;
        std::optional<std::string> customerOrderRef;
        std::optional<std::string> customerStrategyRef;
        std::optional<std::string> sourceIdKey;
        std::optional<std::string> sourceIdDescription;
    };

    inline bool operator==(const ClearedOrderSummary& lhs, const ClearedOrderSummary& rhs) {
        auto double_eq = [](const std::optional<double>& a, const std::optional<double>& b) {
            if (a.has_value() != b.has_value()) return false;
            if (!a.has_value()) return true;
            return std::abs(*a - *b) < 1e-9;
        };

        return lhs.eventTypeId == rhs.eventTypeId &&
               lhs.eventId == rhs.eventId &&
               lhs.marketId == rhs.marketId &&
               lhs.selectionId == rhs.selectionId &&
               double_eq(lhs.handicap, rhs.handicap) &&
               lhs.betId == rhs.betId &&
               lhs.placedDate == rhs.placedDate &&
               lhs.persistenceType == rhs.persistenceType &&
               lhs.orderType == rhs.orderType &&
               lhs.side == rhs.side &&
               lhs.itemDescription == rhs.itemDescription &&
               lhs.betOutcome == rhs.betOutcome &&
               double_eq(lhs.priceRequested, rhs.priceRequested) &&
               lhs.settledDate == rhs.settledDate &&
               lhs.lastMatchedDate == rhs.lastMatchedDate &&
               lhs.betCount == rhs.betCount &&
               double_eq(lhs.commission, rhs.commission) &&
               double_eq(lhs.priceMatched, rhs.priceMatched) &&
               lhs.priceReduced == rhs.priceReduced &&
               double_eq(lhs.sizeSettled, rhs.sizeSettled) &&
               double_eq(lhs.profit, rhs.profit) &&
               double_eq(lhs.sizeCancelled, rhs.sizeCancelled) &&
               lhs.customerOrderRef == rhs.customerOrderRef &&
               lhs.customerStrategyRef == rhs.customerStrategyRef &&
               lhs.sourceIdKey == rhs.sourceIdKey &&
               lhs.sourceIdDescription == rhs.sourceIdDescription;
    }

    inline bool operator!=(const ClearedOrderSummary& lhs, const ClearedOrderSummary& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const ClearedOrderSummary& obj) {
        os << "ClearedOrderSummary{";
        os << "eventTypeId=" << (obj.eventTypeId ? *obj.eventTypeId : "null") << ", ";
        os << "eventId=" << (obj.eventId ? *obj.eventId : "null") << ", ";
        os << "marketId=" << (obj.marketId ? *obj.marketId : "null") << ", ";
        os << "selectionId=" << (obj.selectionId ? std::to_string(*obj.selectionId) : "null") << ", ";
        os << "handicap=" << (obj.handicap ? std::to_string(*obj.handicap) : "null") << ", ";
        os << "betId=" << (obj.betId ? *obj.betId : "null") << ", ";
        os << "placedDate=" << (obj.placedDate ? obj.placedDate->getIsoString() : "null") << ", ";
        os << "persistenceType=" << (obj.persistenceType ? to_string(*obj.persistenceType) : "null") << ", ";
        os << "orderType=" << (obj.orderType ? to_string(*obj.orderType) : "null") << ", ";
        os << "side=" << (obj.side ? to_string(*obj.side) : "null") << ", ";
        os << "itemDescription=" << (obj.itemDescription ? *obj.itemDescription : ItemDescription{}) << ", ";
        os << "betOutcome=" << (obj.betOutcome ? *obj.betOutcome : "null") << ", ";
        os << "priceRequested=" << (obj.priceRequested ? std::to_string(*obj.priceRequested) : "null") << ", ";
        os << "settledDate=" << (obj.settledDate ? obj.settledDate->getIsoString() : "null") << ", ";
        os << "lastMatchedDate=" << (obj.lastMatchedDate ? obj.lastMatchedDate->getIsoString() : "null") << ", ";
        os << "betCount=" << (obj.betCount ? std::to_string(*obj.betCount) : "null") << ", ";
        os << "commission=" << (obj.commission ? std::to_string(*obj.commission) : "null") << ", ";
        os << "priceMatched=" << (obj.priceMatched ? std::to_string(*obj.priceMatched) : "null") << ", ";
        os << "priceReduced=" << (obj.priceReduced ? (*obj.priceReduced ? "true" : "false") : "null") << ", ";
        os << "sizeSettled=" << (obj.sizeSettled ? std::to_string(*obj.sizeSettled) : "null") << ", ";
        os << "profit=" << (obj.profit ? std::to_string(*obj.profit) : "null") << ", ";
        os << "sizeCancelled=" << (obj.sizeCancelled ? std::to_string(*obj.sizeCancelled) : "null") << ", ";
        os << "customerOrderRef=" << (obj.customerOrderRef ? *obj.customerOrderRef : "null") << ", ";
        os << "customerStrategyRef=" << (obj.customerStrategyRef ? *obj.customerStrategyRef : "null") << ", ";
        os << "sourceIdKey=" << (obj.sourceIdKey ? *obj.sourceIdKey : "null") << ", ";
        os << "sourceIdDescription=" << (obj.sourceIdDescription ? *obj.sourceIdDescription : "null");
        os << "}";
        return os;
    }
}