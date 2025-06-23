#pragma once

#include <string>
#include <vector>

#include "betting_enum/market_status.hpp"
#include "utils/date_utils.h"
#include "runner.h"
#include "key_line_description.h"

namespace BetfairAPI::BettingType {
    class MarketBook {
        public:
            MarketBook(const std::string& market_id,bool is_market_delayed);
            MarketBook() = default;
            ~MarketBook() = default;
            MarketBook(const MarketBook&) = default;
            MarketBook(MarketBook&&) noexcept = default;
            MarketBook& operator=(const MarketBook&) = default;
            MarketBook& operator=(MarketBook&&) noexcept = default;

            void setStatus(BetfairAPI::BettingEnum::MarketStatus status);
            void setBetDelay(bool is_bet_delay);
            void setBspReconciled(bool is_bsp_reconciled);
            void setComplete(bool is_complete);
            void setInplay(bool is_inplay);
            void setNumberOfWinners(int n);
            void setNumberOfRunners(int n);
            void setNumberOfActiveRunners(int n);
            void setLastMatchTime(BetfairAPI::Utils::Date date);
            void setTotalMatched(double val);
            void setTotalAvailable(double val);
            void setCrossMatching(bool is_cross_matching);
            void setRunnersVoidable(bool is_runners_voidable);
            void setVersion(long version);
            void addRunners(Runner runner);
            void setKeyLineDescription(KeyLineDescription k);

            const std::string& getMarketId() const;
            bool isMarketDataDelayed() const;
            BetfairAPI::BettingEnum::MarketStatus getStatus() const;
            int getBetDelay() const;
            bool isBspReconciled() const;
            bool isComplete() const;
            bool isInplay() const;
            int getNumberOfWinners() const;
            int getNumberOfRunners() const;
            int getNumberOfActiveRunners() const;
            const BetfairAPI::Utils::Date& getLastMatchTime() const;
            double getTotalMatched() const;
            double getTotalAvailable() const;
            bool isCrossMatching() const;
            bool isRunnersVoidable() const;
            long getVersion() const;
            const std::vector<Runner>& getRunners() const;
            const KeyLineDescription& getKeyLineDescription() const;

        private:
            std::string market_id_;
            bool is_market_data_delayed_;
            BetfairAPI::BettingEnum::MarketStatus status_;
            int bet_delay_;
            bool bsp_reconciled_;
            bool complete_;
            bool inplay_;
            int number_of_winners_;
            int number_of_runners_;
            int number_of_active_runners_;
            BetfairAPI::Utils::Date last_match_time_;
            double total_matched_;
            double total_available_;
            bool cross_matching_;
            bool runners_voidable_;
            long version_;
            std::vector<Runner> runners_;
            KeyLineDescription key_line_description_;
    };
}