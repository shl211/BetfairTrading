#include <gtest/gtest.h>

#include "BettingType/EventType.h"

TEST(EventType, ConstructorAndGetter) {
    std::string name = "Football";
    std::string id = "123";
    
    BetfairAPI::BettingType::EventType event_type(id,name);

    EXPECT_EQ(event_type.getId(),id);
    EXPECT_EQ(event_type.getName(),name);
}
