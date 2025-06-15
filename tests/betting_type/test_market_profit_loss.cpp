#include <gtest/gtest.h>

#include "betting_type/market_profit_loss.h"

TEST(MarketProfitLoss,ConstructorAndGetter) {
    std::string market_id = "1234567";
    double commission = 5.0;
    std::vector<BetfairAPI::BettingType::RunnerProfitLoss> profit_loss = {
        BetfairAPI::BettingType::RunnerProfitLoss(101, 10.5, -2.0, 0.0),
        BetfairAPI::BettingType::RunnerProfitLoss(102, 5.0, 0.0, 0.0)
    };

    BetfairAPI::BettingType::MarketProfitLoss mpl(market_id, commission, profit_loss);

    EXPECT_EQ(mpl.getMarketId(), market_id);
    EXPECT_DOUBLE_EQ(mpl.getCommissionApplied(), commission);
    ASSERT_EQ(mpl.getProfitLoss(),profit_loss);
}