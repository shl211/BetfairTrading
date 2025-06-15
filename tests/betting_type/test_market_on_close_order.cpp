#include <gtest/gtest.h>
#include "betting_type/market_on_close_order.h"

TEST(MarketOnCloseOrder,ConstructorAndGetter) {
    BetfairAPI::BettingType::MarketOnCloseOrder order(12.5);
    EXPECT_DOUBLE_EQ(order.getLiability(), 12.5);
}