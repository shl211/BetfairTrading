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
        md.marketTime = BetfairAPI::Date{"2024-06-01T12:00:00Z"};
        md.suspendTime = BetfairAPI::Date{"2024-06-01T12:30:00Z"};
        md.bspReconciled = false;
        md.complete = false;
        md.inPlay = false;
        md.crossMatching = true;
        md.runnersVoidable = false;
        md.numberOfActiveRunners = 10;
        md.lineMinUnit = 1.0;
        md.betDelay = true;
        md.status = "OPEN";
        md.regulators.push_back("UKGC");
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

    nlohmann::json j = rv;
    BetfairAPI::StreamingType::RunnerValues rv_new = j;

    EXPECT_EQ(rv, rv_new);
}

TEST(DepthLadderJson,Json) {
    BetfairAPI::StreamingType::DepthLadder lbl;
    lbl.level = 1;
    lbl.price = 0.01;
    lbl.size = 0.04;

    nlohmann::json j = lbl;
    BetfairAPI::StreamingType::DepthLadder lbl_new = j;

    EXPECT_EQ(lbl, lbl_new);
}

TEST(PriceLadderJson,Json) {
    BetfairAPI::StreamingType::PriceLadder pbl{1.1,2};


    nlohmann::json j = pbl;
    BetfairAPI::StreamingType::PriceLadder pbl_new = j;

    EXPECT_EQ(pbl, pbl_new);
}

TEST(RunnerChangeJson, Json) {
    BetfairAPI::StreamingType::RunnerChange rc;
    rc.runnerId = 123456789;
    rc.conflated = true;
    rc.runnerValues = BetfairAPI::StreamingType::RunnerValues{
        1500.0, 2.8, 2.6, 2.7
    };
    rc.bestAvailableToBack = {
        BetfairAPI::StreamingType::DepthLadder{1, 2.0, 100.0},
        BetfairAPI::StreamingType::DepthLadder{2, 2.2, 50.0}
    };
    rc.bestAvailableToLay = {
        BetfairAPI::StreamingType::DepthLadder{1, 2.4, 80.0},
        BetfairAPI::StreamingType::DepthLadder{2, 2.6, 60.0}
    };
    rc.bestAvailableToBackVirtual = {
        BetfairAPI::StreamingType::DepthLadder{1, 2.1, 30.0}
    };
    rc.bestAvailableToLayVirtual = {
        BetfairAPI::StreamingType::DepthLadder{1, 2.5, 40.0}
    };
    rc.availableToBack = {
        BetfairAPI::StreamingType::PriceLadder{2.0, 100.0},
        BetfairAPI::StreamingType::PriceLadder{2.2, 50.0}
    };
    rc.availableToLay = {
        BetfairAPI::StreamingType::PriceLadder{2.4, 80.0},
        BetfairAPI::StreamingType::PriceLadder{2.6, 60.0}
    };
    rc.startingPriceBack = {
        BetfairAPI::StreamingType::PriceLadder{2.1, 30.0}
    };
    rc.startingPriceLay = {
        BetfairAPI::StreamingType::PriceLadder{2.5, 40.0}
    };
    rc.traded = {{12345.67,1}};
    nlohmann::json j = rc;
    BetfairAPI::StreamingType::RunnerChange rc_new = j;

    EXPECT_EQ(rc, rc_new);
}

TEST(MarketChangeJson,Json) {
    BetfairAPI::StreamingType::MarketChange mc;
    mc.marketId = "1.23456789";
    mc.marketDefinition = std::make_unique<BetfairAPI::StreamingType::MarketDefinition>();
    mc.marketDefinition->id = "1.23456789";
    mc.marketDefinition->venue = "Ascot";
    mc.marketDefinition->raceType = "FLAT";
    mc.marketDefinition->settledTime = BetfairAPI::Date("2024-06-01T13:00:00Z");
    mc.marketDefinition->timeZone = "Europe/London";
    mc.marketDefinition->eachWayDivisor = 1.5;
    mc.marketDefinition->bspMarket = true;
    mc.marketDefinition->turnInPlayEnabled = true;
    mc.marketDefinition->priceLadderDefinition = "CLASSIC";
    mc.marketDefinition->keyLineDefinition = 123456;
    mc.marketDefinition->persistenceEnabled = true;
    mc.marketDefinition->marketBaseRate = 5.0;
    mc.marketDefinition->eventId = "evt123";
    mc.marketDefinition->eventTypeId = "evttype456";
    mc.marketDefinition->numberOfWinners = 1;
    mc.marketDefinition->countryCode = "GB";
    mc.marketDefinition->lineMaxUnit = 100.0;
    mc.marketDefinition->bettingType = "ODDS";
    mc.marketDefinition->marketType = "WIN";
    mc.marketDefinition->marketTime = BetfairAPI::Date{"2024-06-01T12:00:00Z"};
    mc.marketDefinition->suspendTime = BetfairAPI::Date{"2024-06-01T12:30:00Z"};
    mc.marketDefinition->bspReconciled = false;
    mc.marketDefinition->complete = false;
    mc.marketDefinition->inPlay = false;
    mc.marketDefinition->crossMatching = true;
    mc.marketDefinition->runnersVoidable = false;
    mc.marketDefinition->numberOfActiveRunners = 10;
    mc.marketDefinition->lineMinUnit = 1.0;
    mc.marketDefinition->betDelay = true;
    mc.marketDefinition->status = "OPEN";
    mc.marketDefinition->regulators.push_back("UKGC");
    mc.marketDefinition->discountAllowed = false;
    mc.marketDefinition->openDate = BetfairAPI::Date("2024-06-01T11:00:00Z");
    mc.marketDefinition->version = 1L;
    mc.runnerChange = {
        BetfairAPI::StreamingType::RunnerChange{
            123456789, true,
            BetfairAPI::StreamingType::RunnerValues{1500.0, 2.8, 2.6, 2.7},
            {
                BetfairAPI::StreamingType::DepthLadder{1, 2.0, 100.0},
                BetfairAPI::StreamingType::DepthLadder{2, 2.2, 50.0}
            },
            {
                BetfairAPI::StreamingType::DepthLadder{1, 2.4, 80.0},
                BetfairAPI::StreamingType::DepthLadder{2, 2.6, 60.0}
            },
            {
                BetfairAPI::StreamingType::DepthLadder{1, 2.1, 30.0}
            },
            {
                BetfairAPI::StreamingType::DepthLadder{1, 2.5, 40.0}
            },
            {
                BetfairAPI::StreamingType::PriceLadder{2.0, 100.0},
                BetfairAPI::StreamingType::PriceLadder{2.2, 50.0}
            },
            {
                BetfairAPI::StreamingType::PriceLadder{2.4, 80.0},
                BetfairAPI::StreamingType::PriceLadder{2.6, 60.0}
            },
            {
                BetfairAPI::StreamingType::PriceLadder{2.1, 30.0}
            },
            {
                BetfairAPI::StreamingType::PriceLadder{2.5, 40.0}
            },
            {BetfairAPI::StreamingType::PriceLadder{25, 40.0}}
        }
    };

    nlohmann::json j = mc;
    BetfairAPI::StreamingType::MarketChange mc_new = j;

    EXPECT_EQ(mc, mc_new);
}

TEST(MarketChangeMessageJson,Json) {
    BetfairAPI::StreamingType::MarketChangeMessage mcm;
    mcm.changeType = BetfairAPI::StreamingEnum::ChangeType::SUB_IMAGE;
    mcm.clk = "abc123";
    mcm.initialClk = "def456";
    mcm.publishTime = BetfairAPI::Date("2024-06-01T12:00:00Z");

    BetfairAPI::StreamingType::MarketChange mc;
    mc.marketId = "12.1234";
    mc.tradedVolume = 1000;
    mcm.marketChange.push_back(std::move(mc));

    nlohmann::json j = mcm;
    BetfairAPI::StreamingType::MarketChangeMessage mcm_new = j;

    EXPECT_EQ(mcm, mcm_new);
}