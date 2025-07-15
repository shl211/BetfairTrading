#include <gtest/gtest.h>

#include "BetfairAPI/betting_type/time_range_result.h"

TEST(TimeRangeResult,Comparison) {
    BetfairAPI::BettingType::TimeRangeResult a;
    BetfairAPI::BettingType::TimeRangeResult b;
    BetfairAPI::BettingType::TimeRangeResult c;

    a.marketCount = 100;
    b.marketCount = 100;
    c.marketCount = 200;

    BetfairAPI::BettingType::TimeRange tr;
    tr.from = BetfairAPI::Date{"2024-06-01T00:00:00Z"};

    a.timeRange = tr;
    b.timeRange = tr;
    c.timeRange = BetfairAPI::BettingType::TimeRange {
        BetfairAPI::Date{"2024-06-01T00:00:00Z"},
        BetfairAPI::Date{"2024-07-01T00:00:00Z"}
    };

    // Test equality operator
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);

    // Test inequality operator
    EXPECT_FALSE(a != b);
    EXPECT_TRUE(a != c);
}