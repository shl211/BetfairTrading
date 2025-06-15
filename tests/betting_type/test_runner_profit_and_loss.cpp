#include <gtest/gtest.h>

#include "betting_type/runner_profit_loss.h"

TEST(RunnerProfitLoss,ConstructorAndGetter) {
    // Test parameterized constructor
    BetfairAPI::BettingType::RunnerProfitLoss rpl_param(123, 50.5, -10.25,0.0);
    EXPECT_EQ(rpl_param.getSelectionId(), 123);
    EXPECT_DOUBLE_EQ(rpl_param.getIfWin(), 50.5);
    EXPECT_DOUBLE_EQ(rpl_param.getIfLose(), -10.25);
    EXPECT_DOUBLE_EQ(rpl_param.getIfPlace(), 0);
}

TEST(RunnerProfitLoss, EqualityOperator) {
    BetfairAPI::BettingType::RunnerProfitLoss rpl1(123, 50.5, -10.25, 0.0);
    BetfairAPI::BettingType::RunnerProfitLoss rpl2(123, 50.5, -10.25, 0.0);
    BetfairAPI::BettingType::RunnerProfitLoss rpl3(124, 50.5, -10.25, 0.0);

    EXPECT_TRUE(rpl1 == rpl2);
    EXPECT_FALSE(rpl1 != rpl2);
    EXPECT_FALSE(rpl1 == rpl3);
    EXPECT_TRUE(rpl1 != rpl3);
}