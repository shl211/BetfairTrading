#include <gtest/gtest.h>

#include "betting_type/key_line_selection.h"

TEST(KeyLineSelection, ConstructorAndGetter) {
    int selectionId = 12345;
    double handicap = 1.5;
    BetfairAPI::BettingType::KeyLineSelection kld(selectionId, handicap);

    EXPECT_EQ(kld.getSelectionId(), selectionId);
    EXPECT_DOUBLE_EQ(kld.getHandicap(), handicap);
}
TEST(KeyLineSelection, EqualityOperator) {
    long selectionId = 1001;
    double handicap = 2.0;
    BetfairAPI::BettingType::KeyLineSelection kls1(selectionId, handicap);
    BetfairAPI::BettingType::KeyLineSelection kls2(selectionId, handicap);

    EXPECT_TRUE(kls1 == kls2);
    EXPECT_FALSE(kls1 != kls2);
}

TEST(KeyLineSelection, InequalityOperator_DifferentSelectionId) {
    long selectionId1 = 1001;
    long selectionId2 = 1002;
    double handicap = 2.0;
    BetfairAPI::BettingType::KeyLineSelection kls1(selectionId1, handicap);
    BetfairAPI::BettingType::KeyLineSelection kls2(selectionId2, handicap);

    EXPECT_FALSE(kls1 == kls2);
    EXPECT_TRUE(kls1 != kls2);
}

TEST(KeyLineSelection, InequalityOperator_DifferentHandicap) {
    long selectionId = 1001;
    double handicap1 = 2.0;
    double handicap2 = 2.1;
    BetfairAPI::BettingType::KeyLineSelection kls1(selectionId, handicap1);
    BetfairAPI::BettingType::KeyLineSelection kls2(selectionId, handicap2);

    EXPECT_FALSE(kls1 == kls2);
    EXPECT_TRUE(kls1 != kls2);
}
