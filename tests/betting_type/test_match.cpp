#include <gtest/gtest.h>

#include "betting_type/match.h"

TEST(Match, ConstructorAndGetter) {
    BetfairAPI::BettingEnum::Side side = BetfairAPI::BettingEnum::Side::BACK;
    double price = 2.5;
    double size = 100.0;
    std::string bet_id = "bet123";
    std::string match_id = "match456";
    BetfairAPI::Utils::Date match_date("2024-06-01T12:34:56Z");

    BetfairAPI::BettingType::Match match(side, price, size, bet_id, match_id, match_date);

    // Test getters
    EXPECT_EQ(match.getSide(), side);
    EXPECT_DOUBLE_EQ(match.getPrice(), price);
    EXPECT_DOUBLE_EQ(match.getSize(), size);
    EXPECT_EQ(match.getBetId(), bet_id);
    EXPECT_EQ(match.getMatchId(), match_id);
    EXPECT_EQ(match.getMatchDate(), match_date);
}