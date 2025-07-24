#pragma once

#include <string>
#include <vector>
#include <optional>
#include "BetfairAPI/betting_enum/market_status.hpp"
#include "BetfairAPI/date.h"
#include "BetfairAPI/betting_type/runner.h"
#include "BetfairAPI/betting_type/key_line_description.h"

namespace BetfairAPI::BettingType {
    struct MarketBook {
        std::string marketId;
        bool isMarketDataDelayed;
        std::optional<BettingEnum::MarketStatus> status;
        std::optional<int> betDelay;
        std::optional<bool> bspReconciled;
        std::optional<bool> complete;
        std::optional<bool> inplay;
        std::optional<int> numberOfWinners;
        std::optional<int> numberOfRunners;
        std::optional<int> numberOfActiveRunners;
        std::optional<Date> lastMatchTime;
        std::optional<double> totalMatched;
        std::optional<double> totalAvailable;
        std::optional<bool> crossMatching;
        std::optional<bool> runnersVoidable;
        std::optional<long> version;
        std::vector<Runner> runners;
        std::optional<KeyLineDescription> keyLineDescription;
    };

    inline bool operator==(const MarketBook& lhs, const MarketBook& rhs) {
        return lhs.marketId == rhs.marketId &&
               lhs.isMarketDataDelayed == rhs.isMarketDataDelayed &&
               lhs.status == rhs.status &&
               lhs.betDelay == rhs.betDelay &&
               lhs.bspReconciled == rhs.bspReconciled &&
               lhs.complete == rhs.complete &&
               lhs.inplay == rhs.inplay &&
               lhs.numberOfWinners == rhs.numberOfWinners &&
               lhs.numberOfRunners == rhs.numberOfRunners &&
               lhs.numberOfActiveRunners == rhs.numberOfActiveRunners &&
               lhs.lastMatchTime == rhs.lastMatchTime &&
               lhs.totalMatched == rhs.totalMatched &&
               lhs.totalAvailable == rhs.totalAvailable &&
               lhs.crossMatching == rhs.crossMatching &&
               lhs.runnersVoidable == rhs.runnersVoidable &&
               lhs.version == rhs.version &&
               lhs.runners == rhs.runners &&
               lhs.keyLineDescription == rhs.keyLineDescription;
    }

    inline bool operator!=(const MarketBook& lhs, const MarketBook& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const MarketBook& mb) {
        os << "MarketBook{marketId=" << mb.marketId
           << ", isMarketDataDelayed=" << mb.isMarketDataDelayed
           << ", status=";
        if (mb.status) os << static_cast<int>(*mb.status); else os << "null";
        os << ", betDelay=";
        if (mb.betDelay) os << *mb.betDelay; else os << "null";
        os << ", bspReconciled=";
        if (mb.bspReconciled) os << *mb.bspReconciled; else os << "null";
        os << ", complete=";
        if (mb.complete) os << *mb.complete; else os << "null";
        os << ", inplay=";
        if (mb.inplay) os << *mb.inplay; else os << "null";
        os << ", numberOfWinners=";
        if (mb.numberOfWinners) os << *mb.numberOfWinners; else os << "null";
        os << ", numberOfRunners=";
        if (mb.numberOfRunners) os << *mb.numberOfRunners; else os << "null";
        os << ", numberOfActiveRunners=";
        if (mb.numberOfActiveRunners) os << *mb.numberOfActiveRunners; else os << "null";
        os << ", lastMatchTime=";
        if (mb.lastMatchTime) os << mb.lastMatchTime->getIsoString(); else os << "null";
        os << ", totalMatched=";
        if (mb.totalMatched) os << *mb.totalMatched; else os << "null";
        os << ", totalAvailable=";
        if (mb.totalAvailable) os << *mb.totalAvailable; else os << "null";
        os << ", crossMatching=";
        if (mb.crossMatching) os << *mb.crossMatching; else os << "null";
        os << ", runnersVoidable=";
        if (mb.runnersVoidable) os << *mb.runnersVoidable; else os << "null";
        os << ", version=";
        if (mb.version) os << *mb.version; else os << "null";
        os << ", runners=[";
        for (size_t i = 0; i < mb.runners.size(); ++i) {
            os << mb.runners[i];
            if (i + 1 < mb.runners.size()) os << ", ";
        }
        os << "]";
        os << ", keyLineDescription=";
        if (mb.keyLineDescription) os << *mb.keyLineDescription; else os << "null";
        os << "}";
        return os;
    }
}