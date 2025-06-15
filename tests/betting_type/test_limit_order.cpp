#include <gtest/gtest.h>

#include "betting_type/limit_order.h"

TEST(LimitOrder, ConstructorAndGetter) {
    double size = 100.5;
    double price = 2.34;
    BetfairAPI::BettingEnum::PersistenceType persistence_type = BetfairAPI::BettingEnum::PersistenceType::LAPSE;
    BetfairAPI::BettingEnum::TimeInForce time_in_force = BetfairAPI::BettingEnum::TimeInForce::FILL_OR_KILL;
    double min_fill_size = 50.0;
    BetfairAPI::BettingEnum::BetTargetType bet_target_type = BetfairAPI::BettingEnum::BetTargetType::BACKERS_PROFIT;
    double bet_target_size = 25.0;

    BetfairAPI::BettingType::LimitOrder order(size, price, persistence_type, time_in_force, min_fill_size, bet_target_type, bet_target_size);

    EXPECT_DOUBLE_EQ(order.getSize(), size);
    EXPECT_DOUBLE_EQ(order.getPrice(), price);
    EXPECT_EQ(order.getPersistenceType(), persistence_type);
    EXPECT_EQ(order.getTimeInForce(), time_in_force);
    EXPECT_DOUBLE_EQ(order.getMinFillSize(), min_fill_size);
    EXPECT_EQ(order.getBetTargetType(), bet_target_type);
    EXPECT_DOUBLE_EQ(order.getBetTargetSize(), bet_target_size);
}
TEST(LimitOrder, EqualityOperator) {
    double size = 100.5;
    double price = 2.34;
    BetfairAPI::BettingEnum::PersistenceType persistence_type = BetfairAPI::BettingEnum::PersistenceType::LAPSE;
    BetfairAPI::BettingEnum::TimeInForce time_in_force = BetfairAPI::BettingEnum::TimeInForce::FILL_OR_KILL;
    double min_fill_size = 50.0;
    BetfairAPI::BettingEnum::BetTargetType bet_target_type = BetfairAPI::BettingEnum::BetTargetType::BACKERS_PROFIT;
    double bet_target_size = 25.0;

    BetfairAPI::BettingType::LimitOrder order1(size, price, persistence_type, time_in_force, min_fill_size, bet_target_type, bet_target_size);
    BetfairAPI::BettingType::LimitOrder order2(size, price, persistence_type, time_in_force, min_fill_size, bet_target_type, bet_target_size);

    EXPECT_TRUE(order1 == order2);
}

TEST(LimitOrder, InequalityOperator) {
    double size = 100.5;
    double price = 2.34;
    BetfairAPI::BettingEnum::PersistenceType persistence_type = BetfairAPI::BettingEnum::PersistenceType::LAPSE;
    BetfairAPI::BettingEnum::TimeInForce time_in_force = BetfairAPI::BettingEnum::TimeInForce::FILL_OR_KILL;
    double min_fill_size = 50.0;
    BetfairAPI::BettingEnum::BetTargetType bet_target_type = BetfairAPI::BettingEnum::BetTargetType::BACKERS_PROFIT;
    double bet_target_size = 25.0;

    BetfairAPI::BettingType::LimitOrder order1(size, price, persistence_type, time_in_force, min_fill_size, bet_target_type, bet_target_size);
    // Change one parameter to ensure inequality
    BetfairAPI::BettingType::LimitOrder order2(size + 1.0, price, persistence_type, time_in_force, min_fill_size, bet_target_type, bet_target_size);

    EXPECT_TRUE(order1 != order2);
}

