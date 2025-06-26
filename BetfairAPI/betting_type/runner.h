#pragma once

#include <vector>
#include <map>
#include <string>

#include "betting_enum/runner_status.hpp"
#include "utils/date_utils.h"
#include "starting_prices.h"
#include "exchange_prices.h"
#include "order.h"
#include "match.h"

namespace BetfairAPI::BettingType {
    class Runner {
        public:
            Runner(long selection_id,double handicap, BetfairAPI::BettingEnum::RunnerStatus status);
            Runner() = default;
            ~Runner() = default;
            Runner(const Runner&) = default;
            Runner(Runner&&) noexcept = default;
            Runner& operator=(const Runner&) = default;
            Runner& operator=(Runner&&) noexcept = default;

            void setAdjustmentFactor(double val);
            void setLastPriceTraded(double val);
            void setTotalMatched(double val);
            void setRemovalDate(BetfairAPI::Utils::Date date);
            void setStartingPrices(StartingPrices sp);
            void setExchangePrices(ExchangePrices ex);
            void addOrder(Order order);
            void addMatch(Match match);
            void addMatchByStrategy(const std::string& strategy, Match match);

            long getSelectionId() const;
            double getHandicap() const;
            BetfairAPI::BettingEnum::RunnerStatus getStatus() const;
            double getAdjustmentFactor() const;
            double getLastPriceTraded() const;
            double getTotalMatched() const;
            BetfairAPI::Utils::Date getRemovalDate() const;
            const StartingPrices& getStartingPrices() const;
            const ExchangePrices& getExchangePrices() const;
            const std::vector<Order>& getOrders() const;
            const std::vector<Match>& getMatches() const;
            const std::map<std::string, Match>& getMatchesByStrategy() const;

        private:
            long selection_id_;
            double handicap_;
            BetfairAPI::BettingEnum::RunnerStatus status_;
            double adjustment_factor_;
            double last_price_traded_;
            double total_matched_;
            BetfairAPI::Utils::Date removal_date_;
            StartingPrices sp_;
            ExchangePrices ex_;
            std::vector<Order> orders_;
            std::vector<Match> matches_;
            std::map<std::string,Match> matches_by_strategy_;
    };
}