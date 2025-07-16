#include <gtest/gtest.h>

#include "BetfairAPI/betting_type/event.h"

TEST(Event,Comparison) {
    BetfairAPI::BettingType::Event event1;
    BetfairAPI::BettingType::Event event2;
    BetfairAPI::BettingType::Event event3;

    event1.id = "A";
    event2.id = "A";
    event3.id = "B";

    event1.name = "A";
    event2.name = "A";
    event3.name = "B";

    // Test equality
    EXPECT_EQ(event1, event2);

    // Test inequality
    EXPECT_NE(event1, event3);
}