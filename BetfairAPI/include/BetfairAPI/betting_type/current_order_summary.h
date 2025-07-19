#pragma once

#include <string>
#include <optional>
#include "price_size.h"
#include "current_item_description.h"
#include "BetfairAPI/betting_enum/side.hpp"
#include "BetfairAPI/betting_enum/order_status.hpp"
#include "BetfairAPI/betting_enum/persistence_type.hpp"
#include "BetfairAPI/betting_enum/order_type.hpp"
#include "BetfairAPI/date.h"

namespace BetfairAPI::BettingType {
    struct CurrentOrderSummary {
        std::string betId;
        std::string marketId;
        long selectionId;
        double handicap;
        PriceSize priceSize;
        double bspLiability;
        BettingEnum::Side side;
        BettingEnum::OrderStatus status;
        BettingEnum::PersistenceType persistenceType;
        BettingEnum::OrderType orderType;
        std::optional<Date> placedDate;
        std::optional<Date> matchedDate;
        std::optional<double> averagePriceMatched;
        std::optional<double> sizeMatched;
        std::optional<double> sizeRemaining;
        std::optional<double> sizeLapsed;
        std::optional<double> sizeCancelled;
        std::optional<double> sizeVoided;
        std::optional<std::string> regulatorAuthCode;
        std::optional<std::string> regulatorCode;
        std::optional<std::string> customerOrderRef;
        std::optional<std::string> customerStrategyRef;
        std::optional<CurrentItemDescription> currentItemDescription;
        std::optional<std::string> sourceIdKey;
        std::optional<std::string> sourceIdDescription;
    };

    inline bool operator==(const CurrentOrderSummary& lhs, const CurrentOrderSummary& rhs) {
        return lhs.betId == rhs.betId &&
                lhs.marketId == rhs.marketId &&
                lhs.selectionId == rhs.selectionId &&
                lhs.handicap == rhs.handicap &&
                lhs.priceSize == rhs.priceSize &&
                lhs.bspLiability == rhs.bspLiability &&
                lhs.side == rhs.side &&
                lhs.status == rhs.status &&
                lhs.persistenceType == rhs.persistenceType &&
                lhs.orderType == rhs.orderType &&
                lhs.placedDate == rhs.placedDate &&
                lhs.matchedDate == rhs.matchedDate &&
                lhs.averagePriceMatched == rhs.averagePriceMatched &&
                lhs.sizeMatched == rhs.sizeMatched &&
                lhs.sizeRemaining == rhs.sizeRemaining &&
                lhs.sizeLapsed == rhs.sizeLapsed &&
                lhs.sizeCancelled == rhs.sizeCancelled &&
                lhs.sizeVoided == rhs.sizeVoided &&
                lhs.regulatorAuthCode == rhs.regulatorAuthCode &&
                lhs.regulatorCode == rhs.regulatorCode &&
                lhs.customerOrderRef == rhs.customerOrderRef &&
                lhs.customerStrategyRef == rhs.customerStrategyRef &&
                lhs.currentItemDescription == rhs.currentItemDescription &&
                lhs.sourceIdKey == rhs.sourceIdKey &&
                lhs.sourceIdDescription == rhs.sourceIdDescription;
    }

    inline bool operator!=(const CurrentOrderSummary& lhs, const CurrentOrderSummary& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const CurrentOrderSummary& obj) {
        os << "CurrentOrderSummary{"
            << "betId: " << obj.betId << ", "
            << "marketId: " << obj.marketId << ", "
            << "selectionId: " << obj.selectionId << ", "
            << "handicap: " << obj.handicap << ", "
            << "priceSize: " << obj.priceSize << ", "
            << "bspLiability: " << obj.bspLiability << ", "
            << "side: " << static_cast<int>(obj.side) << ", "
            << "status: " << static_cast<int>(obj.status) << ", "
            << "persistenceType: " << static_cast<int>(obj.persistenceType) << ", "
            << "orderType: " << static_cast<int>(obj.orderType) << ", "
            << "placedDate: " << (obj.placedDate ? obj.placedDate->getIsoString() : "null") << ", "
            << "matchedDate: " << (obj.matchedDate ? obj.matchedDate->getIsoString() : "null") << ", "
            << "averagePriceMatched: " << (obj.averagePriceMatched ? std::to_string(*obj.averagePriceMatched) : "null") << ", "
            << "sizeMatched: " << (obj.sizeMatched ? std::to_string(*obj.sizeMatched) : "null") << ", "
            << "sizeRemaining: " << (obj.sizeRemaining ? std::to_string(*obj.sizeRemaining) : "null") << ", "
            << "sizeLapsed: " << (obj.sizeLapsed ? std::to_string(*obj.sizeLapsed) : "null") << ", "
            << "sizeCancelled: " << (obj.sizeCancelled ? std::to_string(*obj.sizeCancelled) : "null") << ", "
            << "sizeVoided: " << (obj.sizeVoided ? std::to_string(*obj.sizeVoided) : "null") << ", "
            << "regulatorAuthCode: " << (obj.regulatorAuthCode ? *obj.regulatorAuthCode : "null") << ", "
            << "regulatorCode: " << (obj.regulatorCode ? *obj.regulatorCode : "null") << ", "
            << "customerOrderRef: " << (obj.customerOrderRef ? *obj.customerOrderRef : "null") << ", "
            << "customerStrategyRef: " << (obj.customerStrategyRef ? *obj.customerStrategyRef : "null") << ", "
            << "currentItemDescription: " << (obj.currentItemDescription ? *obj.currentItemDescription : CurrentItemDescription{}) << ", "
            << "sourceIdKey: " << (obj.sourceIdKey ? *obj.sourceIdKey : "null") << ", "
            << "sourceIdDescription: " << (obj.sourceIdDescription ? *obj.sourceIdDescription : "null")
            << "}";
        return os;
    }
}