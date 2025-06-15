#include <gtest/gtest.h>

#include "betting_type/time_range_result.h"

TEST(TimeRangeResult,ConstructorAndGetter) {

    BetfairAPI::Utils::Date from("2024-06-01T00:00:00Z");
    BetfairAPI::Utils::Date to("2025-06-01T00:00:00Z");
    BetfairAPI::BettingType::TimeRange tr(from,to);
    int market_count = 42;

    BetfairAPI::BettingType::TimeRangeResult result(tr, market_count);

    EXPECT_EQ(result.getTimeRange(), tr);
    EXPECT_EQ(result.getMarketCount(), market_count);
}