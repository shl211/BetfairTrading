#include <gtest/gtest.h>

#include "BettingType/EventType.h"
#include "BettingType/EventTypeResults.h"

TEST(EventTypeResults, ConstructorAndGetter) {
    std::string name = "Football";
    std::string id = "123";
    int market_count = 1000;

    BetfairAPI::BettingType::EventType event_type(id,name);
    BetfairAPI::BettingType::EventTypeResults event_type_results(event_type,market_count);

    EXPECT_EQ(event_type_results.getEventType(), event_type);
    EXPECT_EQ(event_type_results.getMarketCount(), market_count);
}
