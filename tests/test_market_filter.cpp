#include <gtest/gtest.h>
#include "MarketFilter.h"
#include <nlohmann/json.hpp>

TEST(MarketFilter,Default) {
    BetfairAPI::MarketFilter market_filter = BetfairAPI::MarketFilter();

    nlohmann::json j = market_filter.getFilterJson();

    EXPECT_EQ(j[""],"");
    EXPECT_EQ(j.size(),1);
}

TEST(MarketFilter,setInPlayOnlyTrue) {
    BetfairAPI::MarketFilter market_filter = BetfairAPI::MarketFilter();
    bool inPlayOnly = true;
    market_filter.setInPlayOnly(inPlayOnly);

    nlohmann::json j = market_filter.getFilterJson();

    EXPECT_TRUE(j.contains("inPlayOnly"));
    EXPECT_EQ(j["inPlayOnly"],inPlayOnly);
    EXPECT_EQ(j.size(),1);
}

TEST(MarketFilter,setInPlayOnlyFalse) {
    BetfairAPI::MarketFilter market_filter = BetfairAPI::MarketFilter();
    bool inPlayOnly = false;
    market_filter.setInPlayOnly(inPlayOnly);

    nlohmann::json j = market_filter.getFilterJson();

    EXPECT_TRUE(j.contains("inPlayOnly"));
    EXPECT_EQ(j["inPlayOnly"],inPlayOnly);
    EXPECT_EQ(j.size(),1);
}

TEST(MarketFilter,setTurnInPlayEnabledTrue) {
    BetfairAPI::MarketFilter market_filter = BetfairAPI::MarketFilter();
    bool setTurnInPlayEnabled = true;
    market_filter.setTurnInPlayEnabled(setTurnInPlayEnabled);

    nlohmann::json j = market_filter.getFilterJson();

    EXPECT_TRUE(j.contains("turnInPlayEnabled"));
    EXPECT_EQ(j["turnInPlayEnabled"],setTurnInPlayEnabled);
    EXPECT_EQ(j.size(),1);
}

TEST(MarketFilter,setTurnInPlayEnabledFalse) {
    BetfairAPI::MarketFilter market_filter = BetfairAPI::MarketFilter();
    bool setTurnInPlayEnabled = false;
    market_filter.setTurnInPlayEnabled(setTurnInPlayEnabled);

    nlohmann::json j = market_filter.getFilterJson();

    EXPECT_TRUE(j.contains("turnInPlayEnabled"));
    EXPECT_EQ(j["turnInPlayEnabled"],setTurnInPlayEnabled);
    EXPECT_EQ(j.size(),1);
}
