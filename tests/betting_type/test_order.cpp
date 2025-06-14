#include <gtest/gtest.h>

#include "betting_type/order.h"

TEST(Order, ConstructorAndGetter) {
    BetfairAPI::BettingType::OrderParams params;
    params.bet_id = "bet123";
    params.order_type = BetfairAPI::BettingEnum::OrderType::LIMIT;
    params.order_status = BetfairAPI::BettingEnum::OrderStatus::EXECUTABLE;
    params.persistence_type = BetfairAPI::BettingEnum::PersistenceType::LAPSE;
    params.side = BetfairAPI::BettingEnum::Side::BACK;
    params.price = 2.5;
    params.size = 100.0;
    params.bsp_liability = 0.0;
    params.placed_date = BetfairAPI::Utils::Date("2024-06-01T12:00:00Z");
    params.avg_price_matched = 2.4;
    params.size_matched = 50.0;
    params.size_remaining = 50.0;
    params.size_lapsed = 0.0;
    params.size_cancelled = 0.0;
    params.size_voided = 0.0;
    params.customer_order_ref = "orderRef";
    params.customer_strategy_ref = "strategyRef";

    BetfairAPI::BettingType::Order order(params);

    EXPECT_EQ(order.getBetId(), "bet123");
    EXPECT_EQ(order.getOrderType(), BetfairAPI::BettingEnum::OrderType::LIMIT);
    EXPECT_EQ(order.getOrderStatus(), BetfairAPI::BettingEnum::OrderStatus::EXECUTABLE);
    EXPECT_EQ(order.getPersistenceType(), BetfairAPI::BettingEnum::PersistenceType::LAPSE);
    EXPECT_EQ(order.getSide(), BetfairAPI::BettingEnum::Side::BACK);
    EXPECT_DOUBLE_EQ(order.getPrice(), 2.5);
    EXPECT_DOUBLE_EQ(order.getSize(), 100.0);
    EXPECT_DOUBLE_EQ(order.getBspLiability(), 0.0);
    EXPECT_EQ(order.getPlacedDate(), BetfairAPI::Utils::Date("2024-06-01T12:00:00Z"));
    EXPECT_DOUBLE_EQ(order.getAvgPriceMatched(), 2.4);
    EXPECT_DOUBLE_EQ(order.getSizeMatched(), 50.0);
    EXPECT_DOUBLE_EQ(order.getSizeRemaining(), 50.0);
    EXPECT_DOUBLE_EQ(order.getSizeLapsed(), 0.0);
    EXPECT_DOUBLE_EQ(order.getSizeCancelled(), 0.0);
    EXPECT_DOUBLE_EQ(order.getSizeVoided(), 0.0);
    EXPECT_EQ(order.getCustomerOrderRef(), "orderRef");
    EXPECT_EQ(order.getCustomerStrategyRef(), "strategyRef");
}
