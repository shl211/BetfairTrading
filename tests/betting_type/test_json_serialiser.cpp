#include <gtest/gtest.h>

#include "BetfairAPI/betting_type/json_serialiser.hpp"

TEST(TimeRangeJson, BothDatesPresent) {
    BetfairAPI::BettingType::TimeRange tr{
        BetfairAPI::Date{"2024-06-11T12:34:56Z"}, 
        BetfairAPI::Date{"2024-06-13T12:34:56Z"}
    };
    
    nlohmann::json json = tr;
    BetfairAPI::BettingType::TimeRange result = json;
    EXPECT_EQ(result, tr);
}

TEST(TimeRangeJson, OneDatePresent) {
    BetfairAPI::BettingType::TimeRange tr{
        std::nullopt, 
        BetfairAPI::Date{"2024-06-13T12:34:56Z"}
    };
    
    nlohmann::json json = tr;
    BetfairAPI::BettingType::TimeRange result = json;
    EXPECT_EQ(result, tr);
}

TEST(TimeRangeJson, OneDatePresnet2) {
    BetfairAPI::BettingType::TimeRange tr{
        BetfairAPI::Date{"2024-06-13T12:34:56Z"},
        std::nullopt
    };
    
    nlohmann::json json = tr;
    BetfairAPI::BettingType::TimeRange result = json;
    EXPECT_EQ(result, tr);
}

TEST(TimeRangeJson, NonePresent) {
    BetfairAPI::BettingType::TimeRange tr{std::nullopt,std::nullopt};
    
    nlohmann::json json = tr;
    BetfairAPI::BettingType::TimeRange result = json;
    EXPECT_EQ(result, tr);
}

TEST(MarketFilterJson, Basic) {
    BetfairAPI::BettingType::MarketFilter mf;
    mf.eventIds = {"1234","34566"};
    mf.bspOnly = true;

    nlohmann::json json = mf;
    BetfairAPI::BettingType::MarketFilter result = json;

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

    nlohmann::json json = et;
    BetfairAPI::BettingType::EventType result =json;

    EXPECT_EQ(et, result);
}

TEST(EventTypeResultJson, Basic) {
    BetfairAPI::BettingType::EventTypeResult et;
    et.eventType = BetfairAPI::BettingType::EventType{"name","12312"};
    et.marketCount = 100;

    nlohmann::json json = et;
    BetfairAPI::BettingType::EventTypeResult result = json;

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

    nlohmann::json json = trr;
    BetfairAPI::BettingType::TimeRangeResult result = json;

    EXPECT_EQ(trr, result);
}

TEST(CompetitionJson, Basic) {
    // Basic test for Competition
    BetfairAPI::BettingType::Competition comp;
    comp.id = "comp123";
    comp.name = "Premier League";

    nlohmann::json json = comp;
    BetfairAPI::BettingType::Competition result = json;

    EXPECT_EQ(comp, result);
}

TEST(CompetitionResultJson, Basic) {
    BetfairAPI::BettingType::CompetitionResult comp_res;
    comp_res.competition.id = "comp456";
    comp_res.competition.name = "Champions League";
    comp_res.marketCount = 77;
    comp_res.competitionRegion = "EU";

    nlohmann::json json = comp_res;
    BetfairAPI::BettingType::CompetitionResult result = json;

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

    nlohmann::json json = event;
    BetfairAPI::BettingType::Event result = json;

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

    nlohmann::json json = event_res;
    BetfairAPI::BettingType::EventResult result = json;

    EXPECT_EQ(event_res, result);
}

TEST(MarketTypeResultJson,Basic) {
    BetfairAPI::BettingType::MarketTypeResult mtr;
    mtr.marketType = "MATCH_ODDS";
    mtr.marketCount = 123;

    nlohmann::json json = mtr;
    BetfairAPI::BettingType::MarketTypeResult result = json;

    EXPECT_EQ(mtr, result);
}

TEST(CountryCodeResultJson,Basic) {
    BetfairAPI::BettingType::CountryCodeResult ccr;
    ccr.countryCode = "GB";
    ccr.marketCount = 123;

    nlohmann::json json = ccr;
    BetfairAPI::BettingType::CountryCodeResult result = json;

    EXPECT_EQ(ccr, result);
}

TEST(VenueResultJson,Basic) {
    BetfairAPI::BettingType::VenueResult vr;
    vr.venue = "Cheltenham";
    vr.marketCount = 456;

    nlohmann::json json = vr;
    BetfairAPI::BettingType::VenueResult result = json;

    EXPECT_EQ(vr, result);
}

TEST(MarketLineRangeInfoJson,Basic) {
    BetfairAPI::BettingType::MarketLineRangeInfo mlri;
    mlri.marketUnit = "GOALS";
    mlri.minUnitValue = 0.5;
    mlri.maxUnitValue = 5.5;
    mlri.interval = 0.5;

    nlohmann::json json = mlri;
    BetfairAPI::BettingType::MarketLineRangeInfo result = json;

    EXPECT_EQ(mlri, result);
}

TEST(PriceLadderDescriptionJson,Basic) {
    BetfairAPI::BettingType::PriceLadderDescription pld;
    pld.type = BetfairAPI::BettingEnum::PriceLadderType::CLASSIC;

    nlohmann::json json = pld;
    BetfairAPI::BettingType::PriceLadderDescription result = json;

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
        
    nlohmann::json json = md;
    BetfairAPI::BettingType::MarketDescription result = json;

    EXPECT_EQ(md, result);
}

TEST(RunnerCatalogJson,Basic) {
    BetfairAPI::BettingType::RunnerCatalog rc;
    rc.selectionId = 123456;
    rc.runnerName = "Runner One";
    rc.handicap = 0.0;
    rc.sortPriority = 1;
    rc.metadata = {{"JOCKEY", "John Doe"}, {"TRAINER", "Jane Smith"}};

    nlohmann::json json = rc;
    BetfairAPI::BettingType::RunnerCatalog result = json;

    EXPECT_EQ(rc, result);
}

TEST(MarketVersionJson,Basic) {
    BetfairAPI::BettingType::MarketVersion mv;
    mv.version = 987654321;

    nlohmann::json json = mv;
    BetfairAPI::BettingType::MarketVersion result = json;

    EXPECT_EQ(mv, result);
}

TEST(CurrentItemDescriptionJson,Basic) {
    BetfairAPI::BettingType::CurrentItemDescription cid;
    cid.marketVersion = BetfairAPI::BettingType::MarketVersion{1234};

    nlohmann::json json = cid;
    BetfairAPI::BettingType::CurrentItemDescription result = json;

    EXPECT_EQ(cid, result);
}

TEST(PriceSizeJson,Basic) {
    BetfairAPI::BettingType::PriceSize ps;
    ps.price = 2.5;
    ps.size = 100.0;

    nlohmann::json json = ps;
    BetfairAPI::BettingType::PriceSize result = json;

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

    nlohmann::json json = cos;
    BetfairAPI::BettingType::CurrentOrderSummary result = json;

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
    nlohmann::json json = report;
    BetfairAPI::BettingType::CurrentOrderSummaryReport result = json;

    EXPECT_EQ(report, result);
}

TEST(RunnerIdJson,Basic) {
    BetfairAPI::BettingType::RunnerId rid;
    rid.selectionId = 12345;
    rid.handicap = 0.0;

    nlohmann::json json = rid;
    BetfairAPI::BettingType::RunnerId result = json;

    EXPECT_EQ(rid, result);
}

TEST(ItemDescriptionJson,Basic) {
    BetfairAPI::BettingType::ItemDescription idesc;
    idesc.eventTypeDesc = "Soccer";
    idesc.marketType = "MATCH_ODDS";
    idesc.marketDesc = "OPEN";
    idesc.runnerDesc = "Team A";

    nlohmann::json json = idesc;
    BetfairAPI::BettingType::ItemDescription result = json;

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

    nlohmann::json json = cos;
    BetfairAPI::BettingType::ClearedOrderSummary result = json;

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

    nlohmann::json json = report;
    BetfairAPI::BettingType::ClearedOrderSummaryReport result = json;

    EXPECT_EQ(report, result);
}

TEST(LimitOrderJson,Basic) {
    BetfairAPI::BettingType::LimitOrder lo;
    lo.size = 100.0;
    lo.price = 2.5;
    lo.persistenceType = BetfairAPI::BettingEnum::PersistenceType::LAPSE;
    lo.minFillSize = 10.0;
    lo.timeInForce = BetfairAPI::BettingEnum::TimeInForce::FILL_OR_KILL;

    nlohmann::json json = lo;
    BetfairAPI::BettingType::LimitOrder result = json;

    EXPECT_EQ(lo, result);
}

TEST(LimitOnCloseOrderJson,Basic) {
    BetfairAPI::BettingType::LimitOnCloseOrder loco;
    loco.liability = 50.0;
    loco.price = 1.8;

    nlohmann::json json = loco;
    BetfairAPI::BettingType::LimitOnCloseOrder result = json;

    EXPECT_EQ(loco, result);
}

TEST(MarketOnCloseOrderJson,Basic) {
    BetfairAPI::BettingType::MarketOnCloseOrder loco;
    loco.liability = 50.0;

    nlohmann::json json = loco;
    BetfairAPI::BettingType::MarketOnCloseOrder result = json;

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

    nlohmann::json json = pi;
    BetfairAPI::BettingType::PlaceInstruction result = json;

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

    nlohmann::json json = pir;
    BetfairAPI::BettingType::PlaceInstructionReport result = json;

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

    nlohmann::json json = report;
    BetfairAPI::BettingType::PlaceExecutionReport result = json;

    EXPECT_EQ(report, result);
}

TEST(CancelInstructionJson,Basic) {
    BetfairAPI::BettingType::CancelInstruction instr;
    instr.betId = "323423";
    instr.sizeReduction = 1.0;

    nlohmann::json json = instr;
    BetfairAPI::BettingType::CancelInstruction result = json;

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

    nlohmann::json json = cir;
    BetfairAPI::BettingType::CancelInstructionReport result = json;

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

    nlohmann::json json = report;
    BetfairAPI::BettingType::CancelExecutionReport result = json;

    EXPECT_EQ(report, result);
}

TEST(ReplaceInstructionJson,Basic) {
    BetfairAPI::BettingType::ReplaceInstruction instr;
    instr.betId = "323423";
    instr.newPrice = 1.0;

    nlohmann::json json = instr;
    BetfairAPI::BettingType::ReplaceInstruction result = json;

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
    nlohmann::json json = rir;
    BetfairAPI::BettingType::ReplaceInstructionReport result = json;

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

    nlohmann::json json = report;
    BetfairAPI::BettingType::ReplaceExecutionReport result = json;

    EXPECT_EQ(report, result);
}

TEST(UpdateInstructionJson,Basic) {
    BetfairAPI::BettingType::UpdateInstruction instr;
    instr.betId = "bet123";
    instr.newPersistenceType = BetfairAPI::BettingEnum::PersistenceType::PERSIST;

    nlohmann::json json = instr;
    BetfairAPI::BettingType::UpdateInstruction result = json;

    EXPECT_EQ(instr, result);
}

TEST(UpdateInstructionReportJson,Basic) {
    BetfairAPI::BettingType::UpdateInstructionReport uir;
    uir.status = BetfairAPI::BettingEnum::InstructionReportStatus::SUCCESS;
    uir.errorCode = std::nullopt;
    uir.instruction.betId = "bet123";
    uir.instruction.newPersistenceType = BetfairAPI::BettingEnum::PersistenceType::PERSIST;

    nlohmann::json json = uir;
    BetfairAPI::BettingType::UpdateInstructionReport result = json;

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

    nlohmann::json json = report;
    BetfairAPI::BettingType::UpdateExecutionReport result = json;

    EXPECT_EQ(report, result);
}

TEST(ExBestOffersOverridesJson,Basic) {
    BetfairAPI::BettingType::ExBestOffersOverrides exbo;
    exbo.bestPricesDepth = 3;
    exbo.rollupModel = BetfairAPI::BettingEnum::RollupModel::STAKE;
    exbo.rollupLimit = 10;
    exbo.rollupLiabilityThreshold = 100.0;
    exbo.rollupLiabilityFactor = 2.0;

    nlohmann::json json = exbo;
    BetfairAPI::BettingType::ExBestOffersOverrides result = json;

    EXPECT_EQ(exbo, result);
}

TEST(PriceProjectionJson,Basic) {
    BetfairAPI::BettingType::PriceProjection pp;
    pp.priceData = {BetfairAPI::BettingEnum::PriceData::EX_BEST_OFFERS, BetfairAPI::BettingEnum::PriceData::EX_TRADED};
    pp.virtualise = true;
    pp.rolloverStakes = false;

    nlohmann::json json = pp;
    BetfairAPI::BettingType::PriceProjection result = json;

    EXPECT_EQ(pp, result);
}

TEST(KeyLineSelectionJson,Basic) {
    BetfairAPI::BettingType::KeyLineSelection kls;
    kls.selectionId = 123456;
    kls.handicap = 0.0;

    nlohmann::json json = kls;
    BetfairAPI::BettingType::KeyLineSelection result = json;

    EXPECT_EQ(kls, result);
}

TEST(KeyLineDescriptionJson,Basic) {
    BetfairAPI::BettingType::KeyLineDescription kld;
    BetfairAPI::BettingType::KeyLineSelection kls1;
    kls1.selectionId = 111;
    kls1.handicap = 0.0;
    BetfairAPI::BettingType::KeyLineSelection kls2;
    kls2.selectionId = 222;
    kls2.handicap = 1.5;
    kld.keyLine = {kls1, kls2};

    nlohmann::json json = kld;
    BetfairAPI::BettingType::KeyLineDescription result = json;

    EXPECT_EQ(kld, result);
}

TEST(StartingPricesJson,Basic) {
    BetfairAPI::BettingType::StartingPrices sp;
    sp.nearPrice = 1.95;
    sp.farPrice = 2.05;
    sp.actualSP = 2.00;

    nlohmann::json json = sp;
    BetfairAPI::BettingType::StartingPrices result = json;

    EXPECT_EQ(sp, result);
}

TEST(ExchangePricesJson,Basic) {
    BetfairAPI::BettingType::ExchangePrices ep;
    ep.availableToBack = {
        BetfairAPI::BettingType::PriceSize{2.0, 100.0},
        BetfairAPI::BettingType::PriceSize{1.9, 50.0}
    };
    ep.availableToLay = {
        BetfairAPI::BettingType::PriceSize{2.2, 80.0},
        BetfairAPI::BettingType::PriceSize{2.3, 40.0}
    };
    ep.tradedVolume = {
        BetfairAPI::BettingType::PriceSize{2.0, 200.0},
        BetfairAPI::BettingType::PriceSize{2.2, 150.0}
    };

    nlohmann::json json = ep;
    BetfairAPI::BettingType::ExchangePrices result = json;

    EXPECT_EQ(ep, result);
}

TEST(OrderJson,Basic) {
    BetfairAPI::BettingType::Order order;
    order.betId = "bet001";
    order.orderType = BetfairAPI::BettingEnum::OrderType::LIMIT;
    order.status = BetfairAPI::BettingEnum::OrderStatus::EXECUTABLE;
    order.persistenceType = BetfairAPI::BettingEnum::PersistenceType::LAPSE;
    order.side = BetfairAPI::BettingEnum::Side::BACK;
    order.price = 3.0;
    order.size = 50.0;
    order.bspLiability = 0.0;
    order.placedDate = BetfairAPI::Date{"2024-06-12T10:00:00Z"};
    order.avgPriceMatched = 2.8;
    order.sizeMatched = 10.0;
    order.sizeRemaining = 40.0;
    order.sizeLapsed = 0.0;
    order.sizeCancelled = 0.0;
    order.sizeVoided = 0.0;

    nlohmann::json json = order;
    BetfairAPI::BettingType::Order result = json;

    EXPECT_EQ(order, result);
}

TEST(MatchJson,Basic) {
    BetfairAPI::BettingType::Match match;
    match.betId = "bet002";
    match.matchId = "match001";
    match.side = BetfairAPI::BettingEnum::Side::LAY;
    match.price = 2.5;
    match.size = 20.0;
    match.matchDate = BetfairAPI::Date{"2024-06-12T11:00:00Z"};

    nlohmann::json json = match;
    BetfairAPI::BettingType::Match result = json;

    EXPECT_EQ(match, result);
}

TEST(RunnerJson,Basic) {
    BetfairAPI::BettingType::Runner runner;
    runner.selectionId = 123456;
    runner.handicap = 0.0;
    runner.status = BetfairAPI::BettingEnum::RunnerStatus::ACTIVE;
    runner.lastPriceTraded = 2.5;
    runner.totalMatched = 100.0;
    runner.matches = {
        BetfairAPI::BettingType::Match{
            "bet003", "match002", BetfairAPI::BettingEnum::Side::BACK, 2.6, 10.0, BetfairAPI::Date{"2024-06-12T12:00:00Z"}
        },
        BetfairAPI::BettingType::Match{
            "bet004", "match003", BetfairAPI::BettingEnum::Side::LAY, 2.7, 5.0, BetfairAPI::Date{"2024-06-12T13:00:00Z"}
        }
    };
    runner.matchesByStrategy = {
        {"strategyA", {
            BetfairAPI::BettingType::Match{
                "bet005", "match004", BetfairAPI::BettingEnum::Side::BACK, 2.8, 15.0, BetfairAPI::Date{"2024-06-12T14:00:00Z"}
            }
        }},
        {"strategyB", {
            BetfairAPI::BettingType::Match{
                "bet006", "match005", BetfairAPI::BettingEnum::Side::LAY, 2.9, 20.0, BetfairAPI::Date{"2024-06-12T15:00:00Z"}
            }
        }}
    };
    nlohmann::json json = runner;
    BetfairAPI::BettingType::Runner result = json;

    EXPECT_EQ(runner, result);
}

TEST(MarketBook,Basic) {
    BetfairAPI::BettingType::MarketBook mb;
    mb.marketId = "market123";
    mb.isMarketDataDelayed = false;
    mb.status = BetfairAPI::BettingEnum::MarketStatus::OPEN;
    mb.betDelay = 0;
    mb.bspReconciled = true;
    mb.complete = true;
    mb.inplay = false;
    mb.numberOfWinners = 1;
    mb.numberOfRunners = 2;
    mb.numberOfActiveRunners = 2;
    mb.lastMatchTime = BetfairAPI::Date{"2024-06-12T16:00:00Z"};
    mb.totalMatched = 1000.0;
    mb.totalAvailable = 500.0;
    mb.crossMatching = true;
    mb.runnersVoidable = false;
    mb.version = 123456789;
    BetfairAPI::BettingType::Runner runner1;
    runner1.selectionId = 1;
    runner1.handicap = 0.0;
    runner1.status = BetfairAPI::BettingEnum::RunnerStatus::ACTIVE;
    runner1.lastPriceTraded = 2.0;
    runner1.totalMatched = 500.0;
    BetfairAPI::BettingType::Runner runner2;
    runner2.selectionId = 2;
    runner2.handicap = 0.0;
    runner2.status = BetfairAPI::BettingEnum::RunnerStatus::ACTIVE;
    runner2.lastPriceTraded = 3.0;
    runner2.totalMatched = 500.0;
    mb.runners = {runner1, runner2};

    nlohmann::json json = mb;
    BetfairAPI::BettingType::MarketBook result = json;

    EXPECT_EQ(mb, result);
}

