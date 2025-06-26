#pragma once

#include <vector>
#include <string>

#include "runner_profit_loss.h"

namespace BetfairAPI::BettingType {
    class MarketProfitLoss {
        public:
            MarketProfitLoss(std::string_view market_id, double commission_applied, 
                const std::vector<RunnerProfitLoss>& profit_loss);
            MarketProfitLoss() = default;
            ~MarketProfitLoss() = default;
            MarketProfitLoss(const MarketProfitLoss&) = default;
            MarketProfitLoss(MarketProfitLoss&&) noexcept = default;
            MarketProfitLoss& operator=(const MarketProfitLoss&) = default;
            MarketProfitLoss& operator=(MarketProfitLoss&&) noexcept = default;

            friend std::ostream& operator<<(std::ostream& os, const MarketProfitLoss& mpl);

            std::string getMarketId() const;
            double getCommissionApplied() const;
            const std::vector<RunnerProfitLoss>& getProfitLoss() const;

        private:
            std::string market_id_;
            double commission_applied_;
            std::vector<RunnerProfitLoss> profit_loss_;
    };
}