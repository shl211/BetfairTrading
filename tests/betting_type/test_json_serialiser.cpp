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
#include "BetfairAPI/betting_type/runner_id.h"
#include "BetfairAPI/betting_type/item_description.h"
#include "BetfairAPI/betting_type/cleared_order_summary.h"
#include "BetfairAPI/betting_type/cleared_order_summary_report.h"
#include "BetfairAPI/betting_type/limit_order.h"
#include "BetfairAPI/betting_type/limit_on_close_order.h"
#include "BetfairAPI/betting_type/market_on_close_order.h"
#include "BetfairAPI/betting_type/place_instruction.h"
#include "BetfairAPI/betting_type/place_instruction_report.h"
#include "BetfairAPI/betting_type/place_execution_report.h"
#include "BetfairAPI/betting_type/cancel_instruction.h"
#include "BetfairAPI/betting_type/cancel_instruction_report.h"
#include "BetfairAPI/betting_type/cancel_execution_report.h"
#include "BetfairAPI/betting_type/replace_instruction.h"
#include "BetfairAPI/betting_type/replace_instruction_report.h"
#include "BetfairAPI/betting_type/replace_execution_report.h"
#include "BetfairAPI/betting_type/update_instruction.h"
#include "BetfairAPI/betting_type/update_instruction_report.h"
#include "BetfairAPI/betting_type/update_execution_report.h"

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

TEST(RunnerIdJson,Basic) {
    BetfairAPI::BettingType::RunnerId rid;
    rid.selectionId = 12345;
    rid.handicap = 0.0;

    auto json = BetfairAPI::BettingType::toJson(rid);
    auto result = BetfairAPI::BettingType::fromJson<BetfairAPI::BettingType::RunnerId>(json);

    EXPECT_EQ(rid, result);
}

TEST(ItemDescriptionJson,Basic) {
    BetfairAPI::BettingType::ItemDescription idesc;
    idesc.eventTypeDesc = "Soccer";
    idesc.marketType = "MATCH_ODDS";
    idesc.marketDesc = "OPEN";
    idesc.runnerDesc = "Team A";

    auto json = BetfairAPI::BettingType::toJson(idesc);
    auto result = BetfairAPI::BettingType::fromJson<BetfairAPI::BettingType::ItemDescription>(json);

    EXPECT_EQ(idesc, result);
}

TEST(ClearedOrderSummaryJson,Basic) {
    BetfairAPI::BettingType::ClearedOrderSummary cos;
    cos.eventTypeId = "1";
    cos.eventId = "2";
    cos.marketId = "3";
    cos.selectionId = 4;
    cos.handicap = 0.0;
    cos.betId = "bet567";
    cos.placedDate = BetfairAPI::Date{"2024-06-12T12:00:00Z"};
    cos.persistenceType = BetfairAPI::BettingEnum::PersistenceType::LAPSE;
    cos.orderType = BetfairAPI::BettingEnum::OrderType::LIMIT;
    cos.side = BetfairAPI::BettingEnum::Side::BACK;
    BetfairAPI::BettingType::ItemDescription idesc;
    idesc.eventTypeDesc = "Soccer";
    idesc.marketType = "MATCH_ODDS";
    idesc.marketDesc = "OPEN";
    idesc.runnerDesc = "Team B";
    cos.itemDescription = idesc;
    cos.betOutcome = "WIN";
    cos.priceRequested = 2.5;
    cos.settledDate = BetfairAPI::Date{"2024-06-13T12:00:00Z"};
    cos.lastMatchedDate = BetfairAPI::Date{"2024-06-12T13:00:00Z"};
    cos.betCount = 1;
    cos.commission = 5.0;
    cos.priceMatched = 2.5;
    cos.priceReduced = false;
    cos.sizeSettled = 100.0;
    cos.profit = 195.0;
    cos.sizeCancelled = 0.0;
    cos.customerOrderRef = "orderRef";
    cos.customerStrategyRef = "strategyRef";
    cos.sourceIdKey = "srcKey";
    cos.sourceIdDescription = "srcDesc";

    auto json = BetfairAPI::BettingType::toJson(cos);
    auto result = BetfairAPI::BettingType::fromJson<BetfairAPI::BettingType::ClearedOrderSummary>(json);

    EXPECT_EQ(cos, result);
}

TEST(ClearedOrderSummaryReportJson,Basic) {
    BetfairAPI::BettingType::ClearedOrderSummary cos1;
    cos1.eventTypeId = "1";
    cos1.marketId = "2";
    
    BetfairAPI::BettingType::ClearedOrderSummary cos2;
    cos2.sourceIdDescription = "12asfsadfsd";

    BetfairAPI::BettingType::ClearedOrderSummaryReport report;
    report.clearedOrders = {cos1,cos2};

    auto json = BetfairAPI::BettingType::toJson(report);
    auto result = BetfairAPI::BettingType::fromJson<BetfairAPI::BettingType::ClearedOrderSummaryReport>(json);

    EXPECT_EQ(report, result);
}

TEST(LimitOrderJson,Basic) {
    BetfairAPI::BettingType::LimitOrder lo;
    lo.size = 100.0;
    lo.price = 2.5;
    lo.persistenceType = BetfairAPI::BettingEnum::PersistenceType::LAPSE;
    lo.minFillSize = 10.0;
    lo.timeInForce = BetfairAPI::BettingEnum::TimeInForce::FILL_OR_KILL;

    auto json = BetfairAPI::BettingType::toJson(lo);
    auto result = BetfairAPI::BettingType::fromJson<BetfairAPI::BettingType::LimitOrder>(json);

    EXPECT_EQ(lo, result);
}

TEST(LimitOnCloseOrderJson,Basic) {
    BetfairAPI::BettingType::LimitOnCloseOrder loco;
    loco.liability = 50.0;
    loco.price = 1.8;

    auto json = BetfairAPI::BettingType::toJson(loco);
    auto result = BetfairAPI::BettingType::fromJson<BetfairAPI::BettingType::LimitOnCloseOrder>(json);

    EXPECT_EQ(loco, result);
}

TEST(MarketOnCloseOrderJson,Basic) {
    BetfairAPI::BettingType::MarketOnCloseOrder loco;
    loco.liability = 50.0;

    auto json = BetfairAPI::BettingType::toJson(loco);
    auto result = BetfairAPI::BettingType::fromJson<BetfairAPI::BettingType::MarketOnCloseOrder>(json);

    EXPECT_EQ(loco, result);
}

TEST(PlaceInstructionJson,Basic) {
    BetfairAPI::BettingType::PlaceInstruction pi;
    pi.selectionId = 12345;
    pi.handicap = 0.0;
    pi.side = BetfairAPI::BettingEnum::Side::BACK;
    pi.orderType = BetfairAPI::BettingEnum::OrderType::LIMIT;
    BetfairAPI::BettingType::LimitOrder lo;
    lo.size = 100.0;
    lo.price = 2.5;
    lo.persistenceType = BetfairAPI::BettingEnum::PersistenceType::LAPSE;
    pi.limitOrder = lo;
    pi.customerOrderRef = "orderRef123";

    auto json = BetfairAPI::BettingType::toJson(pi);
    auto result = BetfairAPI::BettingType::fromJson<BetfairAPI::BettingType::PlaceInstruction>(json);

    EXPECT_EQ(pi, result);
}

TEST(PlaceInstructionReportJson,Basic) {
    BetfairAPI::BettingType::PlaceInstructionReport pir;
    pir.status = BetfairAPI::BettingEnum::InstructionReportStatus::SUCCESS;
    pir.errorCode = std::nullopt;
    pir.betId = "bet123";
    pir.orderStatus = BetfairAPI::BettingEnum::OrderStatus::EXECUTION_COMPLETE;
    pir.instruction.selectionId = 12345;
    pir.instruction.handicap = 0.0;
    pir.instruction.side = BetfairAPI::BettingEnum::Side::BACK;
    pir.instruction.orderType = BetfairAPI::BettingEnum::OrderType::LIMIT;
    BetfairAPI::BettingType::LimitOrder lo;
    lo.size = 100.0;
    lo.price = 2.5;
    lo.persistenceType = BetfairAPI::BettingEnum::PersistenceType::LAPSE;
    pir.instruction.limitOrder = lo;
    pir.instruction.customerOrderRef = "orderRef123";

    auto json = BetfairAPI::BettingType::toJson(pir);
    auto result = BetfairAPI::BettingType::fromJson<BetfairAPI::BettingType::PlaceInstructionReport>(json);

    EXPECT_EQ(pir, result);
}

TEST(PlaceExecutionReportJson,Basic) {
    BetfairAPI::BettingType::PlaceInstructionReport pir;
    pir.status = BetfairAPI::BettingEnum::InstructionReportStatus::SUCCESS;
    pir.errorCode = std::nullopt;
    pir.betId = "bet123";
    pir.orderStatus = BetfairAPI::BettingEnum::OrderStatus::EXECUTION_COMPLETE;
    pir.instruction.selectionId = 12345;
    pir.instruction.handicap = 0.0;
    pir.instruction.side = BetfairAPI::BettingEnum::Side::BACK;
    pir.instruction.orderType = BetfairAPI::BettingEnum::OrderType::LIMIT;
    BetfairAPI::BettingType::LimitOrder lo;
    lo.size = 100.0;
    lo.price = 2.5;
    lo.persistenceType = BetfairAPI::BettingEnum::PersistenceType::LAPSE;
    pir.instruction.limitOrder = lo;
    pir.instruction.customerOrderRef = "orderRef123";

    BetfairAPI::BettingType::PlaceExecutionReport report;
    report.status = BetfairAPI::BettingEnum::ExecutionReportStatus::SUCCESS;
    report.errorCode = std::nullopt;
    report.marketId = "market123";
    report.instructionReports.push_back(pir);

    auto json = BetfairAPI::BettingType::toJson(report);
    auto result = BetfairAPI::BettingType::fromJson<BetfairAPI::BettingType::PlaceExecutionReport>(json);

    EXPECT_EQ(report, result);
}

TEST(CancelInstructionJson,Basic) {
    BetfairAPI::BettingType::CancelInstruction instr;
    instr.betId = "323423";
    instr.sizeReduction = 1.0;

    auto json = BetfairAPI::BettingType::toJson(instr);
    auto result = BetfairAPI::BettingType::fromJson<BetfairAPI::BettingType::CancelInstruction>(json);

    EXPECT_EQ(instr, result);
}

TEST(CancelInstructionReportJson,Basic) {
    BetfairAPI::BettingType::CancelInstructionReport cir;
    cir.status = BetfairAPI::BettingEnum::InstructionReportStatus::SUCCESS;
    cir.errorCode = std::nullopt;
    cir.instruction.betId = "323423";
    cir.instruction.sizeReduction = 1.0;
    cir.sizeCancelled = 1.0;
    cir.cancelledDate = BetfairAPI::Date{"2024-06-12T12:00:00Z"};

    auto json = BetfairAPI::BettingType::toJson(cir);
    auto result = BetfairAPI::BettingType::fromJson<BetfairAPI::BettingType::CancelInstructionReport>(json);

    EXPECT_EQ(cir, result);
}

TEST(CancelExecutionReportJson,Basic) {
    BetfairAPI::BettingType::CancelInstructionReport cir;
    cir.status = BetfairAPI::BettingEnum::InstructionReportStatus::SUCCESS;
    cir.errorCode = std::nullopt;
    cir.instruction.betId = "bet999";
    cir.instruction.sizeReduction = 2.0;
    cir.sizeCancelled = 2.0;
    cir.cancelledDate = BetfairAPI::Date{"2024-06-12T13:00:00Z"};

    BetfairAPI::BettingType::CancelExecutionReport report;
    report.status = BetfairAPI::BettingEnum::ExecutionReportStatus::SUCCESS;
    report.errorCode = std::nullopt;
    report.marketId = "market999";
    report.instructionReports.push_back(cir);

    auto json = BetfairAPI::BettingType::toJson(report);
    auto result = BetfairAPI::BettingType::fromJson<BetfairAPI::BettingType::CancelExecutionReport>(json);

    EXPECT_EQ(report, result);
}

TEST(ReplaceInstructionJson,Basic) {
    BetfairAPI::BettingType::ReplaceInstruction instr;
    instr.betId = "323423";
    instr.newPrice = 1.0;

    auto json = BetfairAPI::BettingType::toJson(instr);
    auto result = BetfairAPI::BettingType::fromJson<BetfairAPI::BettingType::ReplaceInstruction>(json);

    EXPECT_EQ(instr, result);
}

TEST(ReplaceInstructionReportJson,Basic) {
    BetfairAPI::BettingType::ReplaceInstructionReport rir;
    rir.status = BetfairAPI::BettingEnum::InstructionReportStatus::SUCCESS;
    rir.errorCode = std::nullopt;

    BetfairAPI::BettingType::CancelInstructionReport cancel_report;
    cancel_report.status = BetfairAPI::BettingEnum::InstructionReportStatus::SUCCESS;
    cancel_report.errorCode = std::nullopt;
    cancel_report.instruction.betId = "bet888";
    cancel_report.instruction.sizeReduction = 1.5;
    cancel_report.sizeCancelled = 1.5;
    cancel_report.cancelledDate = BetfairAPI::Date{"2024-06-12T14:00:00Z"};

    BetfairAPI::BettingType::PlaceInstructionReport place_report;
    place_report.status = BetfairAPI::BettingEnum::InstructionReportStatus::SUCCESS;
    place_report.errorCode = std::nullopt;
    place_report.betId = "bet889";
    place_report.orderStatus = BetfairAPI::BettingEnum::OrderStatus::EXECUTION_COMPLETE;
    place_report.instruction.selectionId = 12345;
    place_report.instruction.handicap = 0.0;
    place_report.instruction.side = BetfairAPI::BettingEnum::Side::BACK;
    place_report.instruction.orderType = BetfairAPI::BettingEnum::OrderType::LIMIT;
    
    BetfairAPI::BettingType::LimitOrder lo;
    lo.size = 100.0;
    lo.price = 2.5;
    lo.persistenceType = BetfairAPI::BettingEnum::PersistenceType::LAPSE;
    place_report.instruction.limitOrder = lo;
    place_report.instruction.customerOrderRef = "orderRef456";

    rir.cancelInstructionReport = std::move(cancel_report);
    rir.placeInstructionReport = std::move(place_report);
    auto json = BetfairAPI::BettingType::toJson(rir);
    auto result = BetfairAPI::BettingType::fromJson<BetfairAPI::BettingType::ReplaceInstructionReport>(json);

    EXPECT_EQ(rir, result);
}

TEST(ReplaceExecutionReportJson,Basic) {
    BetfairAPI::BettingType::ReplaceInstructionReport rir;
    rir.status = BetfairAPI::BettingEnum::InstructionReportStatus::SUCCESS;
    rir.errorCode = std::nullopt;

    BetfairAPI::BettingType::CancelInstructionReport cancel_report;
    cancel_report.status = BetfairAPI::BettingEnum::InstructionReportStatus::SUCCESS;
    cancel_report.errorCode = std::nullopt;
    cancel_report.instruction.betId = "bet777";
    cancel_report.instruction.sizeReduction = 2.0;
    cancel_report.sizeCancelled = 2.0;
    cancel_report.cancelledDate = BetfairAPI::Date{"2024-06-12T15:00:00Z"};

    BetfairAPI::BettingType::PlaceInstructionReport place_report;
    place_report.status = BetfairAPI::BettingEnum::InstructionReportStatus::SUCCESS;
    place_report.errorCode = std::nullopt;
    place_report.betId = "bet778";
    place_report.orderStatus = BetfairAPI::BettingEnum::OrderStatus::EXECUTION_COMPLETE;
    place_report.instruction.selectionId = 54321;
    place_report.instruction.handicap = 0.0;
    place_report.instruction.side = BetfairAPI::BettingEnum::Side::LAY;
    place_report.instruction.orderType = BetfairAPI::BettingEnum::OrderType::LIMIT;

    BetfairAPI::BettingType::LimitOrder lo;
    lo.size = 200.0;
    lo.price = 3.5;
    lo.persistenceType = BetfairAPI::BettingEnum::PersistenceType::LAPSE;
    place_report.instruction.limitOrder = lo;
    place_report.instruction.customerOrderRef = "orderRef789";

    rir.cancelInstructionReport = std::move(cancel_report);
    rir.placeInstructionReport = std::move(place_report);

    BetfairAPI::BettingType::ReplaceExecutionReport report;
    report.status = BetfairAPI::BettingEnum::ExecutionReportStatus::SUCCESS;
    report.errorCode = std::nullopt;
    report.marketId = "market777";
    report.instructionReports.push_back(rir);

    auto json = BetfairAPI::BettingType::toJson(report);
    auto result = BetfairAPI::BettingType::fromJson<BetfairAPI::BettingType::ReplaceExecutionReport>(json);

    EXPECT_EQ(report, result);
}

TEST(UpdateInstructionJson,Basic) {
    BetfairAPI::BettingType::UpdateInstruction instr;
    instr.betId = "bet123";
    instr.newPersistenceType = BetfairAPI::BettingEnum::PersistenceType::PERSIST;

    auto json = BetfairAPI::BettingType::toJson(instr);
    auto result = BetfairAPI::BettingType::fromJson<BetfairAPI::BettingType::UpdateInstruction>(json);

    EXPECT_EQ(instr, result);
}

TEST(UpdateInstructionReportJson,Basic) {
    BetfairAPI::BettingType::UpdateInstructionReport uir;
    uir.status = BetfairAPI::BettingEnum::InstructionReportStatus::SUCCESS;
    uir.errorCode = std::nullopt;
    uir.instruction.betId = "bet123";
    uir.instruction.newPersistenceType = BetfairAPI::BettingEnum::PersistenceType::PERSIST;

    auto json = BetfairAPI::BettingType::toJson(uir);
    auto result = BetfairAPI::BettingType::fromJson<BetfairAPI::BettingType::UpdateInstructionReport>(json);

    EXPECT_EQ(uir, result);
}

TEST(UpdateExecutionReportJson,Basic) {
    BetfairAPI::BettingType::UpdateInstructionReport uir;
    uir.status = BetfairAPI::BettingEnum::InstructionReportStatus::SUCCESS;
    uir.errorCode = std::nullopt;
    uir.instruction.betId = "bet123";
    uir.instruction.newPersistenceType = BetfairAPI::BettingEnum::PersistenceType::PERSIST;

    BetfairAPI::BettingType::UpdateExecutionReport report;
    report.status = BetfairAPI::BettingEnum::ExecutionReportStatus::SUCCESS;
    report.errorCode = std::nullopt;
    report.marketId = "market123";
    report.instructionReports.push_back(uir);

    auto json = BetfairAPI::BettingType::toJson(report);
    auto result = BetfairAPI::BettingType::fromJson<BetfairAPI::BettingType::UpdateExecutionReport>(json);

    EXPECT_EQ(report, result);
}
