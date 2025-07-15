#include <gtest/gtest.h>

#include "BetfairAPI/betting_type/json_serialiser.hpp"
#include "BetfairAPI/betting_type/time_range.h"
#include "BetfairAPI/betting_type/market_filter.h"
#include "BetfairAPI/betting_type/event_type_result.h"
#include "BetfairAPI/betting_type/event_type.h"
#include "BetfairAPI/betting_type/time_range_result.h"

TEST(TimeRangeJson, BothDatesPresent) {
    BetfairAPI::BettingType::TimeRange tr{
        BetfairAPI::Date{"2024-06-11T12:34:56Z"}, 
        BetfairAPI::Date{"2024-06-13T12:34:56Z"}
    };
    
    auto json = BetfairAPI::BettingType::toJson(tr);
    auto result = BetfairAPI::BettingType::fromJson<BetfairAPI::BettingType::TimeRange>(json);
    EXPECT_EQ(result, tr);
}

TEST(TimeRangeJson, OneDatePresnet) {
    BetfairAPI::BettingType::TimeRange tr{
        std::nullopt, 
        BetfairAPI::Date{"2024-06-13T12:34:56Z"}
    };
    
    auto json = BetfairAPI::BettingType::toJson(tr);
    auto result = BetfairAPI::BettingType::fromJson<BetfairAPI::BettingType::TimeRange>(json);
    EXPECT_EQ(result, tr);
}

TEST(TimeRangeJson, OneDatePresnet2) {
    BetfairAPI::BettingType::TimeRange tr{
        BetfairAPI::Date{"2024-06-13T12:34:56Z"},
        std::nullopt
    };
    
    auto json = BetfairAPI::BettingType::toJson(tr);
    auto result = BetfairAPI::BettingType::fromJson<BetfairAPI::BettingType::TimeRange>(json);
    EXPECT_EQ(result, tr);
}

TEST(TimeRangeJson, NonePresent) {
    BetfairAPI::BettingType::TimeRange tr{std::nullopt,std::nullopt};
    
    auto json = BetfairAPI::BettingType::toJson(tr);
    auto result = BetfairAPI::BettingType::fromJson<BetfairAPI::BettingType::TimeRange>(json);
    EXPECT_EQ(result, tr);
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
    EXPECT_EQ(mf, result);
}

TEST(EventTypeJson, Basic) {
    BetfairAPI::BettingType::EventType et;
    et.name = "12erwef";
    et.id = "sdf";

    auto json = BetfairAPI::BettingType::toJson(et);
    auto result = BetfairAPI::BettingType::fromJson<BetfairAPI::BettingType::EventType>(json);

    EXPECT_EQ(et, result);
}

TEST(EventTypeResultJson, Basic) {
    BetfairAPI::BettingType::EventTypeResult et;
    et.eventType = BetfairAPI::BettingType::EventType{"name","12312"};
    et.marketCount = 100;

    auto json = BetfairAPI::BettingType::toJson(et);
    auto result = BetfairAPI::BettingType::fromJson<BetfairAPI::BettingType::EventTypeResult>(json);

    // Check that values round-trip correctly
    EXPECT_EQ(et, result);
}

TEST(TimeRangeResultJson, Basic) {
    BetfairAPI::BettingType::TimeRangeResult trr;
    trr.timeRange = BetfairAPI::BettingType::TimeRange{
        BetfairAPI::Date{"2024-06-11T12:34:56Z"},
        BetfairAPI::Date{"2024-06-13T12:34:59Z"}
    };
    trr.marketCount = 42;

    auto json = BetfairAPI::BettingType::toJson(trr);
    auto result = BetfairAPI::BettingType::fromJson<BetfairAPI::BettingType::TimeRangeResult>(json);

    EXPECT_EQ(trr, result);
}