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
    EXPECT_EQ(match.get_side(), side);
    EXPECT_DOUBLE_EQ(match.get_price(), price);
    EXPECT_DOUBLE_EQ(match.get_size(), size);
    EXPECT_EQ(match.get_bet_id(), bet_id);
    EXPECT_EQ(match.get_match_id(), match_id);
    EXPECT_EQ(match.get_match_date(), match_date);
}