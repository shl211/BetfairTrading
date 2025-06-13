#include "gtest/gtest.h"

#include "betting_type/market_type_result.h"

TEST(MarketTypeResult,ConstructorAndGetter) {
    std::string market_type = "type";
    int market_count = 1;

    BetfairAPI::BettingType::MarketTypeResult mtr(market_type,market_count);

    EXPECT_EQ(mtr.getMarketCount(),market_count);
    EXPECT_EQ(mtr.getMarketType(),market_type);
}