#include <gtest/gtest.h>

#include "betting_type/market_version.h"

TEST(MarketVersion,ConstructorAndGetter) {
    BetfairAPI::BettingType::MarketVersion mv1(12345L);
    EXPECT_EQ(mv1.getVersion(), 12345L);

    // Test with large version number
    BetfairAPI::BettingType::MarketVersion mv4(9223372036854775807L); // max int64_t
    EXPECT_EQ(mv4.getVersion(), 9223372036854775807L);
}
TEST(MarketVersion, EqualityOperator) {
    BetfairAPI::BettingType::MarketVersion mv1(100L);
    BetfairAPI::BettingType::MarketVersion mv2(100L);
    BetfairAPI::BettingType::MarketVersion mv3(200L);

    EXPECT_TRUE(mv1 == mv2);
    EXPECT_FALSE(mv1 == mv3);
}

TEST(MarketVersion, InequalityOperator) {
    BetfairAPI::BettingType::MarketVersion mv1(300L);
    BetfairAPI::BettingType::MarketVersion mv2(400L);
    BetfairAPI::BettingType::MarketVersion mv3(300L);

    EXPECT_TRUE(mv1 != mv2);
    EXPECT_FALSE(mv1 != mv3);
}
