#include <gtest/gtest.h>
#include "BetfairAPI/betting_type/time_range.h"

TEST(TimeRangeTest, EqualityOperator) {
    BetfairAPI::BettingType::TimeRange t1;
    t1.from = BetfairAPI::Date("2024-06-01T12:00:00Z");
    t1.to = BetfairAPI::Date("2024-06-02T12:00:00Z");

    BetfairAPI::BettingType::TimeRange t2;
    t2.from = BetfairAPI::Date("2024-06-01T12:00:00Z");
    t2.to = BetfairAPI::Date("2024-06-02T12:00:00Z");

    EXPECT_TRUE(t1 == t2);
    EXPECT_FALSE(t1 != t2);
}

TEST(TimeRangeTest, InequalityOperator_DifferentFrom) {
    BetfairAPI::BettingType::TimeRange t1;
    t1.from = BetfairAPI::Date("2024-06-01T12:00:00Z");
    t1.to = BetfairAPI::Date("2024-06-02T12:00:00Z");

    BetfairAPI::BettingType::TimeRange t2;
    t2.from = BetfairAPI::Date("2024-06-03T12:00:00Z");
    t2.to = BetfairAPI::Date("2024-06-02T12:00:00Z");

    EXPECT_FALSE(t1 == t2);
    EXPECT_TRUE(t1 != t2);
}

TEST(TimeRangeTest, InequalityOperator_DifferentTo) {
    BetfairAPI::BettingType::TimeRange t1;
    t1.from = BetfairAPI::Date("2024-06-01T12:00:00Z");
    t1.to = BetfairAPI::Date("2024-06-02T12:00:00Z");

    BetfairAPI::BettingType::TimeRange t2;
    t2.from = BetfairAPI::Date("2024-06-01T12:00:00Z");
    t2.to = BetfairAPI::Date("2024-06-03T12:00:00Z");

    EXPECT_FALSE(t1 == t2);
    EXPECT_TRUE(t1 != t2);
}

TEST(TimeRangeTest, BothEmpty) {
    BetfairAPI::BettingType::TimeRange t1;
    BetfairAPI::BettingType::TimeRange t2;
    EXPECT_TRUE(t1 == t2);
    EXPECT_FALSE(t1 != t2);
}