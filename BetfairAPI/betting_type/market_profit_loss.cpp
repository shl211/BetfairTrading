#include "market_profit_loss.h"

namespace BetfairAPI::BettingType {
    MarketProfitLoss::MarketProfitLoss(std::string_view market_id, double commission_applied, 
        const std::vector<RunnerProfitLoss>& profit_loss)
        : market_id_(market_id), commission_applied_(commission_applied), profit_loss_(profit_loss) {}

    std::string MarketProfitLoss::getMarketId() const {
        return market_id_;
    }

    double MarketProfitLoss::getCommissionApplied() const {
        return commission_applied_;
    }

    const std::vector<RunnerProfitLoss>& MarketProfitLoss::getProfitLoss() const {
        return profit_loss_;
    }
}