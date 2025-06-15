#include <gtest/gtest.h>
#include "betting_type/runner_id.h"

TEST(RunnerId, ConstructorAndGetter) {
    BetfairAPI::BettingType::RunnerId runner("1.234", "5678", 2.5);

    EXPECT_EQ(runner.getMarketId(), "1.234");
    EXPECT_EQ(runner.getSelectionId(), "5678");
    EXPECT_DOUBLE_EQ(runner.getHandicap(), 2.5);
}
TEST(RunnerId, EqualityOperator) {
    BetfairAPI::BettingType::RunnerId runner1("1.234", "5678", 2.5);
    BetfairAPI::BettingType::RunnerId runner2("1.234", "5678", 3.0); // Different handicap

    EXPECT_TRUE(runner1 == runner2); // Should be equal since market_id and selection_id are the same
}

TEST(RunnerId, InequalityOperator) {
    BetfairAPI::BettingType::RunnerId runner1("1.234", "5678", 2.5);
    BetfairAPI::BettingType::RunnerId runner2("1.234", "9999", 2.5); // Different selection_id

    EXPECT_TRUE(runner1 != runner2); // Should not be equal
}
