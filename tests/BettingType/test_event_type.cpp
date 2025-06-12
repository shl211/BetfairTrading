#include <gtest/gtest.h>

#include "BettingType/EventType.h"

TEST(EventType, ConstructorAndGetter) {
    std::string name = "Football";
    std::string id = "123";
    
    BetfairAPI::BettingType::EventType event_type(id,name);

    EXPECT_EQ(event_type.getId(),id);
    EXPECT_EQ(event_type.getName(),name);
}

TEST(EventType, EqualityOperator) {
    BetfairAPI::BettingType::EventType e1("123", "Football");
    BetfairAPI::BettingType::EventType e2("123", "Football");
    BetfairAPI::BettingType::EventType e3("124", "Tennis");
    
    EXPECT_TRUE(e1 == e2);  // same id and name
    EXPECT_FALSE(e1 == e3); // different id
}

TEST(EventType, InequalityOperator) {
    BetfairAPI::BettingType::EventType e1("123", "Football");
    BetfairAPI::BettingType::EventType e2("123", "Football");
    BetfairAPI::BettingType::EventType e3("124", "Tennis");

    EXPECT_FALSE(e1 != e2); // same
    EXPECT_TRUE(e1 != e3);  // different id
}