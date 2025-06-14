#include <gtest/gtest.h>

#include "betting_type/event_result.h"

TEST (EventResult, ConstructorAndGetter) {
    BetfairAPI::BettingType::Event dummy_event("123","event_name","GB","UTC","",
        BetfairAPI::Utils::Date("2025-06-14T15:04:05.123+02:00"));
    int market_count = 5;

    BetfairAPI::BettingType::EventResult result(dummy_event, market_count);

    // Test getters
    EXPECT_EQ(result.getMarketCount(), market_count);
    EXPECT_EQ(result.getEvent(), dummy_event);
}