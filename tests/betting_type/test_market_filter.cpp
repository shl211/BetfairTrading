#include <gtest/gtest.h>
#include "BetfairAPI/betting_type/market_filter.h"

TEST(MarketFilter,Comparison) {
    BetfairAPI::BettingType::MarketFilter mf1;
    mf1.inPlayOnly = false;
    mf1.eventTypeIds = {"123","343"};

    BetfairAPI::BettingType::MarketFilter mf2;
    mf2.inPlayOnly = false;
    mf2.eventTypeIds = {"123","343"};

    EXPECT_TRUE(mf1 == mf2);
    EXPECT_FALSE(mf1 != mf2);
}