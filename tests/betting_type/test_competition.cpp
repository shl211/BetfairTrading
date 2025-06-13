#include <gtest/gtest.h>

#include "betting_type/competition.h"

TEST(Competition, ConstructorAndGetter) {
    std::string id {"12345"};
    std::string name {"UEFA Champions League"};
    
    BetfairAPI::BettingType::Competition comp(id,name);

    EXPECT_EQ(comp.getId(),id);
    EXPECT_EQ(comp.getName(),name);
}