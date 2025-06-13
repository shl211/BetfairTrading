#include <gtest/gtest.h>

#include "utils/math_utils.hpp"

TEST(AlmostEqualTest, ExactEquality) {
    EXPECT_TRUE(BetfairAPI::Utils::almostEqual(1.0, 1.0));
}

TEST(AlmostEqualTest, LargeNumbersRelativeComparison) {
    EXPECT_TRUE(BetfairAPI::Utils::almostEqual(1e6, 1e6 + 0.0001));
}

TEST(AlmostEqualTest, SmallNumbersAbsoluteComparison) {
    EXPECT_TRUE(BetfairAPI::Utils::almostEqual(1e-13, 0.0));
}

TEST(AlmostEqualTest, ObviousDifference) {
    EXPECT_FALSE(BetfairAPI::Utils::almostEqual(1.0, 2.0));
}

TEST(AlmostEqualTest, NegativeValues) {
    EXPECT_TRUE(BetfairAPI::Utils::almostEqual(-1.0, -1.0000000001));
}

TEST(AlmostEqualTest, Symmetry) {
    EXPECT_EQ(BetfairAPI::Utils::almostEqual(0.99, 1.0), BetfairAPI::Utils::almostEqual(1.0, 0.99));
}

TEST(AlmostEqualTest, CustomRelativeTolerance) {
    EXPECT_TRUE(BetfairAPI::Utils::almostEqual(1.0, 1.0005, 1e-3));  // Within custom tolerance
}

TEST(AlmostEqualTest, ZeroComparison) {
    EXPECT_TRUE(BetfairAPI::Utils::almostEqual(0.0, -0.0));
}
