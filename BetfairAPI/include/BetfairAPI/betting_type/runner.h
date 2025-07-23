#pragma once

#include <optional>
#include <vector>
#include <ostream>
#include <map>
#include "BetfairAPI/betting_enum/runner_status.hpp"
#include "BetfairAPI/date.h"
#include "starting_prices.h"
#include "exchange_prices.h"
#include "order.h"
#include "match.h"

namespace BetfairAPI::BettingType {
    struct Runner {
        long selectionId;
        double handicap;
        BettingEnum::RunnerStatus status;
        std::optional<double> adjustmentFactor;
        std::optional<double> lastPriceTraded;
        std::optional<double> totalMatched;
        std::optional<Date> removalDate;
        std::optional<StartingPrices> sp;
        std::optional<ExchangePrices> ex;
        std::vector<Order> orders;
        std::vector<Match> matches;
        std::unordered_map<std::string,std::vector<Match>> matchesByStrategy;
    };

    inline bool operator==(const Runner& lhs, const Runner& rhs) {
        return lhs.selectionId == rhs.selectionId &&
               lhs.handicap == rhs.handicap &&
               lhs.status == rhs.status &&
               lhs.adjustmentFactor == rhs.adjustmentFactor &&
               lhs.lastPriceTraded == rhs.lastPriceTraded &&
               lhs.totalMatched == rhs.totalMatched &&
               lhs.removalDate == rhs.removalDate &&
               lhs.sp == rhs.sp &&
               lhs.ex == rhs.ex &&
               lhs.orders == rhs.orders &&
               lhs.matches == rhs.matches &&
               lhs.matchesByStrategy == rhs.matchesByStrategy;
    }

    inline bool operator!=(const Runner& lhs, const Runner& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const Runner& runner) {
        os << "Runner{selectionId=" << runner.selectionId
           << ", handicap=" << runner.handicap
           << ", status=" << static_cast<int>(runner.status)
           << ", adjustmentFactor=";
        if (runner.adjustmentFactor) os << *runner.adjustmentFactor; else os << "null";
        os << ", lastPriceTraded=";
        if (runner.lastPriceTraded) os << *runner.lastPriceTraded; else os << "null";
        os << ", totalMatched=";
        if (runner.totalMatched) os << *runner.totalMatched; else os << "null";
        os << ", removalDate=";
        if (runner.removalDate) os << runner.removalDate->getIsoString(); else os << "null";
        os << ", sp=";
        if (runner.sp) os << *runner.sp; else os << "null";
        os << ", ex=";
        if (runner.ex) os << *runner.ex; else os << "null";
        os << ", orders=[";
        for (size_t i = 0; i < runner.orders.size(); ++i) {
            if (i > 0) os << ", ";
            os << runner.orders[i];
        }
        os << "], matches=[";
        for (size_t i = 0; i < runner.matches.size(); ++i) {
            if (i > 0) os << ", ";
            os << runner.matches[i];
        }
        os << "], matchesByStrategy={";
        bool first = true;
        for (const auto& [key, vec] : runner.matchesByStrategy) {
            if (!first) os << ", ";
            os << key << ":[";
            for (size_t i = 0; i < vec.size(); ++i) {
                if (i > 0) os << ", ";
                os << vec[i];
            }
            os << "]";
            first = false;
        }
        os << "}}";
        return os;
    }
}