#include <gtest/gtest.h>
#include "MarketFilter.h"
#include <nlohmann/json.hpp>

TEST(MarketFilter,Default) {
    BetfairAPI::MarketFilter market_filter = BetfairAPI::MarketFilter();

    nlohmann::json j = market_filter.getFilterJson();

    EXPECT_EQ(j[""],"");
    EXPECT_EQ(j.size(),1);
}

TEST(MarketFilter,setInPlayOnly) {
    BetfairAPI::MarketFilter market_filter = BetfairAPI::MarketFilter();
    bool inPlayOnly = true;
    market_filter.setInPlayOnly(inPlayOnly);

    nlohmann::json j = market_filter.getFilterJson();

    EXPECT_TRUE(j.contains("inPlayOnly"));
    EXPECT_EQ(j["inPlayOnly"],inPlayOnly);
    EXPECT_EQ(j.size(),1);
}
