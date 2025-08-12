#include <gtest/gtest.h>

#include "BetfairAPI/market_type/runner_data.h"

TEST(Runner,RunnerData) {
    BetfairAPI::MarketType::RunnerData data;

    BetfairAPI::StreamingType::RunnerChange rc1;
    rc1.bestAvailableToBack = {{0,1.2,1.3},{1,1.4,1.5}};
    data.updateData(rc1);

    auto res = data.getBestPrice(BetfairAPI::MarketType::Side::BACK,false);
    std::vector<BetfairAPI::MarketType::DepthBasedLadder> expected = {{0,1.2,1.3},{1,1.4,1.5}};

    EXPECT_EQ(res,expected);
}

TEST(Runner,RunnerData2) {
    BetfairAPI::MarketType::RunnerData data;

    BetfairAPI::StreamingType::RunnerChange rc1;
    rc1.bestAvailableToBack = {{0,1.2,1.3},{1,1.4,1.5}};

    BetfairAPI::StreamingType::RunnerChange rc2;
    rc2.bestAvailableToBack = {{1,2.0,1.5},{2,1.2,2}};
    
    //update test
    data.updateData(rc1);
    data.updateData(rc2);

    auto res = data.getBestPrice(BetfairAPI::MarketType::Side::BACK,false);
    std::vector<BetfairAPI::MarketType::DepthBasedLadder> expected = {{0,1.2,1.3},{1,2.0,1.5},{2,1.2,2}};

    EXPECT_EQ(res,expected);
}