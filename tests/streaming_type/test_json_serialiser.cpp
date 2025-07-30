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