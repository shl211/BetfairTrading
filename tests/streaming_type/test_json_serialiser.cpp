#include <gtest/gtest.h>

#include "BetfairAPI/streaming_type/json_serialiser.hpp"

TEST(MarketFilterJson,Json) {
    BetfairAPI::StreamingType::MarketFilter mf;
    mf.bettingTypes.insert(BetfairAPI::StreamingEnum::BettingType::ODDS);
    mf.bspMarket = true;
    mf.turnInPlayEnabled = true;

    nlohmann::json j = mf;
    BetfairAPI::StreamingType::MarketFilter mf_new = j;

    EXPECT_EQ(mf,mf_new);
}

TEST(MarketDataFilterJson,Json) {
    BetfairAPI::StreamingType::MarketDataFilter mdf;
    mdf.ladderLevels = BetfairAPI::StreamingType::MarketDataFilter::LadderLevel::THREE;
    mdf.fields.insert(BetfairAPI::StreamingEnum::TradeField::EX_BEST_OFFERS_DISP);

    nlohmann::json j = mdf;
    BetfairAPI::StreamingType::MarketDataFilter mdf_new = j;

    EXPECT_EQ(mdf, mdf_new);
}

TEST(ChangeMessageJson,Json) {
        BetfairAPI::StreamingType::ChangeMessage msg;
        msg.changeType = BetfairAPI::StreamingEnum::ChangeType::SUB_IMAGE;
        msg.segmentType = BetfairAPI::StreamingEnum::SegmentType::SEG_START;
        msg.conflateMs = 100;
        msg.status = 1;
        msg.heartbeatMs = 5000;
        msg.publishTime = BetfairAPI::Date("2024-06-01T12:00:00Z");
        msg.initialClk = "abc123";
        msg.clk = "def456";

        nlohmann::json j = msg;
        BetfairAPI::StreamingType::ChangeMessage msg_new = j;

        EXPECT_EQ(msg, msg_new);
}

TEST(MarketDefinitionJson,Json) {
        BetfairAPI::StreamingType::MarketDefinition md;
        md.id = "1.23456789";
        md.venue = "Ascot";
        md.raceType = "FLAT";
        md.settledTime = BetfairAPI::Date("2024-06-01T13:00:00Z");
        md.timeZone = "Europe/London";
        md.eachWayDivisor = 1.5;
        md.bspMarket = true;
        md.turnInPlayEnabled = true;
        md.priceLadderDefinition = "CLASSIC";
        md.keyLineDefinition = 123456;
        md.persistenceEnabled = true;
        md.marketBaseRate = 5.0;
        md.eventId = "evt123";
        md.eventTypeId = "evttype456";
        md.numberOfWinners = 1;
        md.countryCode = "GB";
        md.lineMaxUnit = 100.0;
        md.bettingType = "ODDS";
        md.marketType = "WIN";
        md.marketTime = "2024-06-01T12:00:00Z";
        md.suspendTime = "2024-06-01T12:30:00Z";
        md.bspReconciled = false;
        md.complete = false;
        md.inPlay = false;
        md.crossMatching = true;
        md.runnersVoidable = false;
        md.numberOfActiveRunners = 10;
        md.lineMinUnit = 1.0;
        md.betDelay = true;
        md.status = "OPEN";
        md.regulators = "UKGC";
        md.discountAllowed = false;
        md.openDate = BetfairAPI::Date("2024-06-01T11:00:00Z");
        md.version = 1L;

        nlohmann::json j = md;
        BetfairAPI::StreamingType::MarketDefinition md_new = j;

        EXPECT_EQ(md, md_new);
}

TEST(RunnerValuesJson,Json) {
    BetfairAPI::StreamingType::RunnerValues rv;

    rv.tradedVolume = 1500.0;
    rv.lastTradedPrice = 2.8;
    rv.startingPriceNear = 2.6;
    rv.startingPriceFar = 2.7;
    rv.runnerId = std::make_optional<std::string>("runner_001");

    nlohmann::json j = rv;
    BetfairAPI::StreamingType::RunnerValues rv_new = j;

    EXPECT_EQ(rv, rv_new);
}

TEST(LevelBasedLadderJson,Json) {
    BetfairAPI::StreamingType::LevelBasedLadder lbl;

    BetfairAPI::StreamingType::LadderInfo back1{1,2.0, 100.0};
    BetfairAPI::StreamingType::LadderInfo back2{2,2.2, 50.0};
    BetfairAPI::StreamingType::LadderInfo lay1{1,2.4, 80.0};
    BetfairAPI::StreamingType::LadderInfo lay2{2,2.6, 60.0};
    BetfairAPI::StreamingType::LadderInfo backVirtual{1,2.1, 30.0};
    BetfairAPI::StreamingType::LadderInfo layVirtual{1,2.5, 40.0};

    lbl.bestAvailableToBack = {back1, back2};
    lbl.bestAvailableToLay = {lay1, lay2};
    lbl.bestAvailableToBackVirtual = {backVirtual};
    lbl.bestAvailableToLayVirtual = {layVirtual};

    nlohmann::json j = lbl;
    BetfairAPI::StreamingType::LevelBasedLadder lbl_new = j;

    EXPECT_EQ(lbl, lbl_new);
}


TEST(PriceBasedLadderJson,Json) {
    BetfairAPI::StreamingType::PriceBasedLadder pbl;
    std::vector<BetfairAPI::StreamingType::PriceSize> availableToBack = {
        {2.0, 100.0}, {2.2, 50.0}
    };
    std::vector<BetfairAPI::StreamingType::PriceSize> availableToLay = {
        {2.4, 80.0}, {2.6, 60.0}
    };
    std::vector<BetfairAPI::StreamingType::PriceSize> startingPriceAvailableToBack = {
        {2.1, 30.0}
    };
    std::vector<BetfairAPI::StreamingType::PriceSize> startingPriceAvailableToLay = {
        {2.5, 40.0}
    };
    std::vector<BetfairAPI::StreamingType::PriceSize> traded = {
        {2.3, 120.0}
    };

    pbl.availableToBack = availableToBack;
    pbl.availableToLay = availableToLay;
    pbl.startingPriceAvailableToBack = startingPriceAvailableToBack;
    pbl.startingPriceAvailableToLay = startingPriceAvailableToLay;
    pbl.traded = traded;

    nlohmann::json j = pbl;
    BetfairAPI::StreamingType::PriceBasedLadder pbl_new = j;

    EXPECT_EQ(pbl, pbl_new);
}

TEST(RunnerChangeJson, Json) {
    BetfairAPI::StreamingType::RunnerChange rc;

    rc.replaceImage = false;
    rc.totalMatchedVolume = 0;
    rc.values = {
        BetfairAPI::StreamingType::RunnerValues{
            1500.0, 2.8, 2.6, 2.7, std::make_optional<std::string>("runner_001")
        }
    };
    rc.lvlLadder = {
        BetfairAPI::StreamingType::LevelBasedLadder{
            {
                BetfairAPI::StreamingType::LadderInfo{1, 2.0, 100.0},
                BetfairAPI::StreamingType::LadderInfo{2, 2.2, 50.0}
            },
            {
                BetfairAPI::StreamingType::LadderInfo{1, 2.4, 80.0},
                BetfairAPI::StreamingType::LadderInfo{2, 2.6, 60.0}
            },
            {
                BetfairAPI::StreamingType::LadderInfo{1, 2.1, 30.0}
            },
            {
                BetfairAPI::StreamingType::LadderInfo{1, 2.5, 40.0}
            }
        }
    };
    rc.priceLadder = {
        BetfairAPI::StreamingType::PriceBasedLadder{
            {
                {2.0, 100.0}, {2.2, 50.0}
            },
            {
                {2.4, 80.0}, {2.6, 60.0}
            },
            {
                {2.1, 30.0}
            },
            {
                {2.5, 40.0}
            },
            {
                {2.3, 120.0}
            }
        }
    };

    nlohmann::json j = rc;
    BetfairAPI::StreamingType::RunnerChange rc_new = j;

    EXPECT_EQ(rc, rc_new);
}