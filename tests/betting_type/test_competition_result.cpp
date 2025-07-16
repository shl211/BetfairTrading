#include <gtest/gtest.h>
#include "BetfairAPI/betting_type/competition_result.h"

TEST(CompetitionResult,Comparison) {
    BetfairAPI::BettingType::CompetitionResult a;
    a.competition.id = "100";
    a.competition.name = "Premier League";
    a.marketCount = 25;
    a.competitionRegion = "GB";

    BetfairAPI::BettingType::CompetitionResult b;
    b.competition.id = "100";
    b.competition.name = "Premier League";
    b.marketCount = 25;
    b.competitionRegion = "GB";

    BetfairAPI::BettingType::CompetitionResult c;
    c.competition.id = "101";
    c.competition.name = "La Liga";
    c.marketCount = 30;
    c.competitionRegion = "ES";

    // Test equality
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);

    // Test inequality
    EXPECT_FALSE(a == c);
    EXPECT_TRUE(a != c);

    // Change one field at a time and test inequality
    BetfairAPI::BettingType::CompetitionResult d = a;
    d.competition.id = "999";
    EXPECT_FALSE(a == d);

    d = a;
    d.competition.name = "Serie A";
    EXPECT_FALSE(a == d);

    d = a;
    d.marketCount = 99;
    EXPECT_FALSE(a == d);

    d = a;
    d.competitionRegion = "IT";
    EXPECT_FALSE(a == d);
}