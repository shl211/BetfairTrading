#include <gtest/gtest.h>
#include "BetfairAPI/betting_type/competition.h"

TEST(Competition, Equality) {
    std::string id = "123234";
    std::string name = "sdjkh";

    BetfairAPI::BettingType::Competition comp1;
    BetfairAPI::BettingType::Competition comp2;
    comp1.id = id;
    comp1.name = name;
    comp2.id = id;
    comp2.name = name;

    EXPECT_TRUE(comp1 == comp2);
}

TEST(Competition, Inequality) {
    BetfairAPI::BettingType::Competition comp1;
    BetfairAPI::BettingType::Competition comp2;
    comp1.id = "id1";
    comp1.name = "name1";
    comp2.id = "id2";
    comp2.name = "name2";

    EXPECT_TRUE(comp1 != comp2);
}