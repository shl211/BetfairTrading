#include <gtest/gtest.h>

#include "betting_type/competition_result.h"

TEST(CompetitionResults, ConstructorAndGetter) {
    std::string id {"12345"};
    std::string name {"UEFA Champions League"};
    BetfairAPI::BettingType::Competition comp(id,name);

    int market_count{100};
    std::string competition_region{"GB"};

    BetfairAPI::BettingType::CompetitionResult comp_result(comp,market_count,competition_region);

    EXPECT_EQ(comp_result.getCompetition(),comp);
    EXPECT_EQ(comp_result.getCompetitionRegion(),competition_region);
    EXPECT_EQ(comp_result.getMarketCount(),market_count);
}