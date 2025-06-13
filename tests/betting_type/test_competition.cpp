#include <gtest/gtest.h>

#include "betting_type/competition.h"

TEST(Competition, ConstructorAndGetter) {
    std::string id {"12345"};
    std::string name {"UEFA Champions League"};
    
    BetfairAPI::BettingType::Competition comp(id,name);

    EXPECT_EQ(comp.getId(),id);
    EXPECT_EQ(comp.getName(),name);
}

TEST(Competition, Equality) {
    std::string id {"12345"};
    std::string name {"UEFA Champions League"};
    std::string name_same {"UCL"};
    
    BetfairAPI::BettingType::Competition comp1(id,name);
    BetfairAPI::BettingType::Competition comp2(id,name);
    BetfairAPI::BettingType::Competition comp3(id,name_same);

    EXPECT_TRUE(comp1 == comp2);
    EXPECT_TRUE(comp2 == comp1);
    EXPECT_TRUE(comp1 == comp3);
    EXPECT_TRUE(comp3 == comp1);
}

TEST(Competition, Inequality) {
    std::string name {"UEFA Champions League"};
    std::string name_same {"UCL"};
    
    BetfairAPI::BettingType::Competition comp1("12345",name);
    BetfairAPI::BettingType::Competition comp2("123",name);
    BetfairAPI::BettingType::Competition comp3("9",name_same);

    EXPECT_TRUE(comp1 != comp2);
    EXPECT_TRUE(comp2 != comp1);
    EXPECT_TRUE(comp1 != comp3);
    EXPECT_TRUE(comp3 != comp1);
}