#include <gtest/gtest.h>
#include "BetfairAPI/betting_type/event_type.h"

TEST(EventType, Equality) {
    std::string id = "123234";
    std::string name = "sdjkh";

    BetfairAPI::BettingType::EventType e_type1;
    BetfairAPI::BettingType::EventType e_type2;
    e_type1.id = id;
    e_type1.name = name;
    e_type2.id = id;
    e_type2.name = name;

    EXPECT_TRUE(e_type1 == e_type2);
}

TEST(EventType, Inequality) {
    BetfairAPI::BettingType::EventType e_type1;
    BetfairAPI::BettingType::EventType e_type2;
    e_type1.id = "id1";
    e_type1.name = "name1";
    e_type2.id = "id2";
    e_type2.name = "name2";

    EXPECT_TRUE(e_type1 != e_type2);
}