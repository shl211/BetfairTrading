#include <gtest/gtest.h>

#include "BetfairAPI/betting_type/json_serialiser.hpp"
#include "BetfairAPI/betting_type/time_range.h"
#include "BetfairAPI/betting_type/market_filter.h"

TEST(TimeRangeJson, BothDatesPresent) {
    BetfairAPI::BettingType::TimeRange tr{
        BetfairAPI::Date{"2024-06-11T12:34:56Z"}, 
        BetfairAPI::Date{"2024-06-13T12:34:56Z"}
    };
    
    auto json = BetfairAPI::BettingType::toJson(tr);
    auto result = BetfairAPI::BettingType::fromJson<BetfairAPI::BettingType::TimeRange>(json);
    EXPECT_EQ(result.from, tr.from);
    EXPECT_EQ(result.to, tr.to);
}

TEST(TimeRangeJson, OneDatePresnet) {
    BetfairAPI::BettingType::TimeRange tr{
        std::nullopt, 
        BetfairAPI::Date{"2024-06-13T12:34:56Z"}
    };
    
    auto json = BetfairAPI::BettingType::toJson(tr);
    auto result = BetfairAPI::BettingType::fromJson<BetfairAPI::BettingType::TimeRange>(json);
    EXPECT_EQ(result.from, tr.from);
    EXPECT_EQ(result.to, tr.to);
}

TEST(TimeRangeJson, OneDatePresnet2) {
    BetfairAPI::BettingType::TimeRange tr{
        BetfairAPI::Date{"2024-06-13T12:34:56Z"},
        std::nullopt
    };
    
    auto json = BetfairAPI::BettingType::toJson(tr);
    auto result = BetfairAPI::BettingType::fromJson<BetfairAPI::BettingType::TimeRange>(json);
    EXPECT_EQ(result.from, tr.from);
    EXPECT_EQ(result.to, tr.to);
}

TEST(TimeRangeJson, NonePresent) {
    BetfairAPI::BettingType::TimeRange tr{std::nullopt,std::nullopt};
    
    auto json = BetfairAPI::BettingType::toJson(tr);
    auto result = BetfairAPI::BettingType::fromJson<BetfairAPI::BettingType::TimeRange>(json);
    EXPECT_EQ(result.from, tr.from);
    EXPECT_EQ(result.to, tr.to);
}

TEST(MarketFilterJson, Basic) {
    BetfairAPI::BettingType::MarketFilter mf;
    mf.eventIds = {"1234","34566"};
    mf.bspOnly = true;

    auto json = BetfairAPI::BettingType::toJson(mf);
    auto result = BetfairAPI::BettingType::fromJson<BetfairAPI::BettingType::MarketFilter>(json);

    // These are necessary to ensure no unexpected fields and correct performance
    ASSERT_EQ(json.size(), 2);
    ASSERT_TRUE(json.contains("eventIds"));
    ASSERT_TRUE(json.contains("bspOnly"));

    // Check that values round-trip correctly
    EXPECT_EQ(mf.eventIds, result.eventIds);
    EXPECT_EQ(mf.bspOnly, result.bspOnly);
}