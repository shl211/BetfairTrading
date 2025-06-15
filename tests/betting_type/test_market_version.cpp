#include <gtest/gtest.h>

#include "betting_type/market_version.h"

TEST(MarketVersion,ConstructorAndGetter) {
    BetfairAPI::BettingType::MarketVersion mv1(12345L);
    EXPECT_EQ(mv1.getVersion(), 12345L);

    // Test with large version number
    BetfairAPI::BettingType::MarketVersion mv4(9223372036854775807L); // max int64_t
    EXPECT_EQ(mv4.getVersion(), 9223372036854775807L);
}