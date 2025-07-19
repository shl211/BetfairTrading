#include <gtest/gtest.h>

#include "BetfairAPI/betting_type/json_serialiser.hpp"
#include "BetfairAPI/betting_type/time_range.h"
#include "BetfairAPI/betting_type/market_filter.h"
#include "BetfairAPI/betting_type/event_type_result.h"
#include "BetfairAPI/betting_type/event_type.h"
#include "BetfairAPI/betting_type/time_range_result.h"
#include "BetfairAPI/betting_type/competition.h"
#include "BetfairAPI/betting_type/competition_result.h"
#include "BetfairAPI/betting_type/event.h"
#include "BetfairAPI/betting_type/event_result.h"
#include "BetfairAPI/betting_type/market_type_result.h"
#include "BetfairAPI/betting_type/country_code_result.h"
#include "BetfairAPI/betting_type/venue_result.h"
#include "BetfairAPI/betting_type/market_line_range_info.h"
#include "BetfairAPI/betting_type/price_ladder_description.h"
#include "BetfairAPI/betting_type/market_description.h"
#include "BetfairAPI/betting_type/runner_catalog.h"
#include "BetfairAPI/betting_type/market_version.h"
#include "BetfairAPI/betting_type/current_item_description.h"
#include "BetfairAPI/betting_type/price_size.h"
#include "BetfairAPI/betting_type/current_order_summary.h"
#include "BetfairAPI/betting_type/current_order_summary_report.h"

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

TEST(CompetitionJson, Basic) {
    // Basic test for Competition
    BetfairAPI::BettingType::Competition comp;
    comp.id = "comp123";
    comp.name = "Premier League";

    auto json = BetfairAPI::BettingType::toJson(comp);
    auto result = BetfairAPI::BettingType::fromJson<BetfairAPI::BettingType::Competition>(json);

    EXPECT_EQ(comp, result);
}

TEST(CompetitionResultJson, Basic) {
    BetfairAPI::BettingType::CompetitionResult comp_res;
    comp_res.competition.id = "comp456";
    comp_res.competition.name = "Champions League";
    comp_res.marketCount = 77;
    comp_res.competitionRegion = "EU";

    auto json = BetfairAPI::BettingType::toJson(comp_res);
    auto result = BetfairAPI::BettingType::fromJson<BetfairAPI::BettingType::CompetitionResult>(json);

    EXPECT_EQ(comp_res, result);
}

TEST(EventJson,Basic) {
    BetfairAPI::BettingType::Event event;
    event.id = "event789";
    event.name = "FA Cup Final";
    event.countryCode = "GB";
    event.timezone = "Europe/London";
    event.openDate = BetfairAPI::Date{"2024-06-15T17:00:00Z"};
    event.venue = "Wembley Stadium";

    auto json = BetfairAPI::BettingType::toJson(event);
    auto result = BetfairAPI::BettingType::fromJson<BetfairAPI::BettingType::Event>(json);

    EXPECT_EQ(event, result);
}

TEST(EventResultJson,Basic) {
    BetfairAPI::BettingType::EventResult event_res;
    event_res.event.id = "event101";
    event_res.event.name = "World Cup Final";
    event_res.event.countryCode = "FR";
    event_res.event.timezone = "Europe/Paris";
    event_res.event.openDate = BetfairAPI::Date{"2024-07-14T18:00:00Z"};
    event_res.event.venue = "Stade de France";
    event_res.marketCount = 99;

    auto json = BetfairAPI::BettingType::toJson(event_res);
    auto result = BetfairAPI::BettingType::fromJson<BetfairAPI::BettingType::EventResult>(json);

    EXPECT_EQ(event_res, result);
}

TEST(MarketTypeResultJson,Basic) {
    BetfairAPI::BettingType::MarketTypeResult mtr;
    mtr.marketType = "MATCH_ODDS";
    mtr.marketCount = 123;

    auto json = BetfairAPI::BettingType::toJson(mtr);
    auto result = BetfairAPI::BettingType::fromJson<BetfairAPI::BettingType::MarketTypeResult>(json);

    EXPECT_EQ(mtr, result);
}

TEST(CountryCodeResultJson,Basic) {
    BetfairAPI::BettingType::CountryCodeResult ccr;
    ccr.countryCode = "GB";
    ccr.marketCount = 123;

    auto json = BetfairAPI::BettingType::toJson(ccr);
    auto result = BetfairAPI::BettingType::fromJson<BetfairAPI::BettingType::CountryCodeResult>(json);

    EXPECT_EQ(ccr, result);
}

TEST(VenueResultJson,Basic) {
    BetfairAPI::BettingType::VenueResult vr;
    vr.venue = "Cheltenham";
    vr.marketCount = 456;

    auto json = BetfairAPI::BettingType::toJson(vr);
    auto result = BetfairAPI::BettingType::fromJson<BetfairAPI::BettingType::VenueResult>(json);

    EXPECT_EQ(vr, result);
}

TEST(MarketLineRangeInfoJson,Basic) {
    BetfairAPI::BettingType::MarketLineRangeInfo mlri;
    mlri.marketUnit = "GOALS";
    mlri.minUnitValue = 0.5;
    mlri.maxUnitValue = 5.5;
    mlri.interval = 0.5;

    auto json = BetfairAPI::BettingType::toJson(mlri);
    auto result = BetfairAPI::BettingType::fromJson<BetfairAPI::BettingType::MarketLineRangeInfo>(json);

    EXPECT_EQ(mlri, result);
}

TEST(PriceLadderDescriptionJson,Basic) {
    BetfairAPI::BettingType::PriceLadderDescription pld;
    pld.type = BetfairAPI::BettingEnum::PriceLadderType::CLASSIC;

    auto json = BetfairAPI::BettingType::toJson(pld);
    auto result = BetfairAPI::BettingType::fromJson<BetfairAPI::BettingType::PriceLadderDescription>(json);

    EXPECT_EQ(pld, result);
}

TEST(MarketDescriptionJson,Basic) {
    BetfairAPI::BettingType::MarketDescription md;
    md.persistenceEnabled = true;
    md.bspMarket = true;
    md.persistenceEnabled = true;
    md.bspMarket = true;
    md.marketTime = BetfairAPI::Date{"2024-06-20T15:00:00Z"};
    md.suspendTime = BetfairAPI::Date{"2024-06-20T14:55:00Z"};
    md.settleTime = BetfairAPI::Date{"2024-06-20T18:00:00Z"};
    md.bettingType = BetfairAPI::BettingEnum::MarketBettingType::ODDS;
    md.turnInPlay = false;
    md.marketType = "MATCH_ODDS";
    md.regulator = "UKGC";
    md.marketBaseRate = 5.0;
    md.discountAllowed = true;
        
    auto json = BetfairAPI::BettingType::toJson(md);
    auto result = BetfairAPI::BettingType::fromJson<BetfairAPI::BettingType::MarketDescription>(json);

    EXPECT_EQ(md, result);
}

TEST(RunnerCatalogJson,Basic) {
    BetfairAPI::BettingType::RunnerCatalog rc;
    rc.selectionId = 123456;
    rc.runnerName = "Runner One";
    rc.handicap = 0.0;
    rc.sortPriority = 1;
    rc.metadata = {{"JOCKEY", "John Doe"}, {"TRAINER", "Jane Smith"}};

    auto json = BetfairAPI::BettingType::toJson(rc);
    auto result = BetfairAPI::BettingType::fromJson<BetfairAPI::BettingType::RunnerCatalog>(json);

    EXPECT_EQ(rc, result);
}

TEST(MarketVersionJson,Basic) {
    BetfairAPI::BettingType::MarketVersion mv;
    mv.version = 987654321;

    auto json = BetfairAPI::BettingType::toJson(mv);
    auto result = BetfairAPI::BettingType::fromJson<BetfairAPI::BettingType::MarketVersion>(json);

    EXPECT_EQ(mv, result);
}

TEST(CurrentItemDescriptionJson,Basic) {
    BetfairAPI::BettingType::CurrentItemDescription cid;
    cid.marketVersion = BetfairAPI::BettingType::MarketVersion{1234};

    auto json = BetfairAPI::BettingType::toJson(cid);
    auto result = BetfairAPI::BettingType::fromJson<BetfairAPI::BettingType::CurrentItemDescription>(json);

    EXPECT_EQ(cid, result);
}

TEST(PriceSizeJson,Basic) {
    BetfairAPI::BettingType::PriceSize ps;
    ps.price = 2.5;
    ps.size = 100.0;

    auto json = BetfairAPI::BettingType::toJson(ps);
    auto result = BetfairAPI::BettingType::fromJson<BetfairAPI::BettingType::PriceSize>(json);

    EXPECT_EQ(ps, result);
}

TEST(CurrentOrderSummaryJson,Basic) {
    BetfairAPI::BettingType::CurrentOrderSummary cos;
    cos.betId = "bet123";
    cos.marketId = "market456";
    cos.selectionId = 789;
    cos.handicap = 0.0;
    cos.priceSize = BetfairAPI::BettingType::PriceSize{2.0, 50.0};
    cos.side = BetfairAPI::BettingEnum::Side::BACK;
    cos.status = BetfairAPI::BettingEnum::OrderStatus::EXECUTABLE;
    cos.persistenceType = BetfairAPI::BettingEnum::PersistenceType::LAPSE;
    cos.orderType = BetfairAPI::BettingEnum::OrderType::LIMIT;
    cos.placedDate = BetfairAPI::Date{"2024-06-10T12:00:00Z"};
    cos.averagePriceMatched = 2.0;
    cos.sizeMatched = 25.0;
    cos.sizeRemaining = 25.0;
    cos.sizeLapsed = 0.0;
    cos.sizeCancelled = 0.0;
    cos.sizeVoided = 0.0;
    cos.regulatorAuthCode = "authcode";
    cos.regulatorCode = "UKGC";

    auto json = BetfairAPI::BettingType::toJson(cos);
    auto result = BetfairAPI::BettingType::fromJson<BetfairAPI::BettingType::CurrentOrderSummary>(json);

    EXPECT_EQ(cos, result);
}

TEST(CurrentOrderSummaryReportJson,Basic) {
    BetfairAPI::BettingType::CurrentOrderSummary cos;
    cos.betId = "bet123";
    cos.marketId = "market456";
    cos.selectionId = 789;
    cos.handicap = 0.0;
    cos.priceSize = BetfairAPI::BettingType::PriceSize{2.0, 50.0};
    cos.side = BetfairAPI::BettingEnum::Side::BACK;
    cos.status = BetfairAPI::BettingEnum::OrderStatus::EXECUTABLE;
    cos.persistenceType = BetfairAPI::BettingEnum::PersistenceType::LAPSE;
    cos.orderType = BetfairAPI::BettingEnum::OrderType::LIMIT;
    cos.placedDate = BetfairAPI::Date{"2024-06-10T12:00:00Z"};
    cos.averagePriceMatched = 2.0;
    

    BetfairAPI::BettingType::CurrentOrderSummaryReport report;
    report.currentOrders.push_back(std::move(cos));
    auto json = BetfairAPI::BettingType::toJson(report);
    auto result = BetfairAPI::BettingType::fromJson<BetfairAPI::BettingType::CurrentOrderSummaryReport>(json);

    EXPECT_EQ(report, result);
}