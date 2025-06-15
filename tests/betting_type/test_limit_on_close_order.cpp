#include <gtest/gtest.h>
#include "betting_type/limit_on_close_order.h"

TEST(LimitOnCloseOrder,ConstructorAndGetter) {
    BetfairAPI::BettingType::LimitOnCloseOrder order(10.5, 2.0);
    EXPECT_DOUBLE_EQ(order.getLiability(), 10.5);
    EXPECT_DOUBLE_EQ(order.getPrice(), 2.0);
}
TEST(LimitOnCloseOrder, EqualityOperator) {
    BetfairAPI::BettingType::LimitOnCloseOrder order1(10.5, 2.0);
    BetfairAPI::BettingType::LimitOnCloseOrder order2(10.5, 2.0);
    EXPECT_TRUE(order1 == order2);
}

TEST(LimitOnCloseOrder, InequalityOperator) {
    BetfairAPI::BettingType::LimitOnCloseOrder order1(10.5, 2.0);
    BetfairAPI::BettingType::LimitOnCloseOrder order2(11.0, 2.0);
    BetfairAPI::BettingType::LimitOnCloseOrder order3(10.5, 2.5);
    EXPECT_TRUE(order1 != order2);
    EXPECT_TRUE(order1 != order3);
}
