#include <gtest/gtest.h>

#include "betting_type/place_instruction.h"

TEST(PlaceInstruction,ConstructorAndGetter) {

    BetfairAPI::BettingType::LimitOrder limit_order{1.5, 10.0, BetfairAPI::BettingEnum::PersistenceType::PERSIST,
                                                    BetfairAPI::BettingEnum::TimeInForce::FILL_OR_KILL,0.0,
                                                    BetfairAPI::BettingEnum::BetTargetType::BACKERS_PROFIT, 1.0};
    BetfairAPI::BettingType::LimitOnCloseOrder limit_on_close_order{2.0, 5.0};
    BetfairAPI::BettingType::MarketOnCloseOrder market_on_close_order{3.0};
    std::string customer_ref = "order123";

    BetfairAPI::BettingType::PlaceInstruction instr(
        BetfairAPI::BettingEnum::OrderType::LIMIT,
        123456,
        0.0,
        limit_order,
        limit_on_close_order,
        market_on_close_order,
        customer_ref
    );

    // Test getters
    EXPECT_EQ(instr.getOrderType(), BetfairAPI::BettingEnum::OrderType::LIMIT);
    EXPECT_EQ(instr.getSelectionId(), 123456);
    EXPECT_DOUBLE_EQ(instr.getHandicap(), 0.0);
    EXPECT_EQ(instr.getLimitOrder(),limit_order);
    EXPECT_EQ(instr.getLimitOnCloseOrder(),limit_on_close_order);
    EXPECT_EQ(instr.getMarketOnCloseOrder(), market_on_close_order);
    EXPECT_EQ(instr.getCustomerOrderRef(), customer_ref);
}