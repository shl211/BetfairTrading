#include <gtest/gtest.h>
#include "betting_type/market_on_close_order.h"

TEST(MarketOnCloseOrder,ConstructorAndGetter) {
    BetfairAPI::BettingType::MarketOnCloseOrder order(12.5);
    EXPECT_DOUBLE_EQ(order.getLiability(), 12.5);
}

TEST(MarketOnCloseOrder, EqualityOperator) {
    BetfairAPI::BettingType::MarketOnCloseOrder order1(10.0);
    BetfairAPI::BettingType::MarketOnCloseOrder order2(10.0);
    EXPECT_TRUE(order1 == order2);
}

TEST(MarketOnCloseOrder, InequalityOperator) {
    BetfairAPI::BettingType::MarketOnCloseOrder order1(10.0);
    BetfairAPI::BettingType::MarketOnCloseOrder order2(15.0);
    EXPECT_TRUE(order1 != order2);
}
