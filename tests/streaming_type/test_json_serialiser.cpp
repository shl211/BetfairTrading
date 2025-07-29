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