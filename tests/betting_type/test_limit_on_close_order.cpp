#include <gtest/gtest.h>
#include "betting_type/limit_on_close_order.h"

TEST(LimitOnCloseOrder,ConstructorAndGetter) {
    BetfairAPI::BettingType::LimitOnCloseOrder order(10.5, 2.0);
    EXPECT_DOUBLE_EQ(order.getLiability(), 10.5);
    EXPECT_DOUBLE_EQ(order.getPrice(), 2.0);
}