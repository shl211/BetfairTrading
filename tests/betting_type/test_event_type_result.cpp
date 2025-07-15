#include <gtest/gtest.h>
#include "BetfairAPI/betting_type/event_type_result.h"

TEST(EventTypeResultTest, EqualityOperator) {
    BetfairAPI::BettingType::EventTypeResult a;
    a.eventType.id = "1";
    a.eventType.name = "Football";
    a.marketCount = 10;

    BetfairAPI::BettingType::EventTypeResult b;
    b.eventType.id = "1";
    b.eventType.name = "Football";
    b.marketCount = 10;

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST(EventTypeResultTest, InequalityOperator) {
    BetfairAPI::BettingType::EventTypeResult a;
    a.eventType.id = "1";
    a.eventType.name = "Football";
    a.marketCount = 10;

    BetfairAPI::BettingType::EventTypeResult b;
    b.eventType.id = "2";
    b.eventType.name = "Tennis";
    b.marketCount = 5;

    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}