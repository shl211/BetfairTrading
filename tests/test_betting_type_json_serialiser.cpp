#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

#include "betting_type/market_filter.h"
#include "betting_type_json_serialiser.h"

TEST(BettingTypeSerialiser,MarketFilterInPlayOnlyTrueToJson) {
    BetfairAPI::BettingType::MarketFilter market_filter;
    bool inPlayOnly = true;
    market_filter.setInPlayOnly(inPlayOnly);

    nlohmann::json j = market_filter;
    
    EXPECT_TRUE(j.contains("inPlayOnly"));
    EXPECT_EQ(j["inPlayOnly"],inPlayOnly);
}
    
TEST(BettingTypeSerialiser,MarketFilterInPlayOnlyFalseToJson) {
    BetfairAPI::BettingType::MarketFilter market_filter;
    bool inPlayOnly = false;
    market_filter.setInPlayOnly(inPlayOnly);
    
    nlohmann::json j = market_filter;
    
    EXPECT_TRUE(j.contains("inPlayOnly"));
    EXPECT_EQ(j["inPlayOnly"],inPlayOnly);
}
        
TEST(BettingTypeSerialiser,MarketFilterTurnInPlayEnabledTrueToJson) {
    BetfairAPI::BettingType::MarketFilter market_filter;
    bool setTurnInPlayEnabled = true;
    market_filter.setTurnInPlayEnabled(setTurnInPlayEnabled);
    
    nlohmann::json j = market_filter;
    
    EXPECT_TRUE(j.contains("turnInPlayEnabled"));
    EXPECT_EQ(j["turnInPlayEnabled"],setTurnInPlayEnabled);
}

TEST(BettingTypeSerialiser,MarketFilterTurnInPlayEnabledFalseToJson) {
    BetfairAPI::BettingType::MarketFilter market_filter;
    bool setTurnInPlayEnabled = false;
    market_filter.setTurnInPlayEnabled(setTurnInPlayEnabled);
    
    nlohmann::json j = market_filter;
    
    EXPECT_TRUE(j.contains("turnInPlayEnabled"));
    EXPECT_EQ(j["turnInPlayEnabled"],setTurnInPlayEnabled);
}

TEST(BettingTypeSerialiser,MarketFilterTextQueryToJson) {
    BetfairAPI::BettingType::MarketFilter market_filter;
    std::string query = "HelloWorld";
    market_filter.setQuery(query);
    
    nlohmann::json j = market_filter;
    
    EXPECT_TRUE(j.contains("textQuery"));
    EXPECT_EQ(j["textQuery"],query);
}

TEST(BettingTypeSerialiser,MarketFilterEventTypeIdsOneToJson) {
    BetfairAPI::BettingType::MarketFilter market_filter;
    market_filter.addEventTypeId("1");
    
    nlohmann::json j = market_filter;
    
    EXPECT_TRUE(j.contains("eventTypeIds"));
    EXPECT_EQ(j["eventTypeIds"], nlohmann::json::array({"1"}));
}

TEST(BettingTypeSerialiser,MarketFilterEventTypeIdsMultipleToJson) {
    BetfairAPI::BettingType::MarketFilter market_filter;
    market_filter.addEventTypeId("1");
    market_filter.addEventTypeId("2");
    market_filter.addEventTypeId("3");
    
    nlohmann::json j = market_filter;
    
    EXPECT_TRUE(j.contains("eventTypeIds"));
    EXPECT_EQ(j["eventTypeIds"], nlohmann::json::array({"1","2","3"}));
}

TEST(BettingTypeSerialiser,MarketFilterMarketBettingTypes) {
    BetfairAPI::BettingType::MarketFilter market_filter;
    market_filter.addMarketBettingType(BetfairAPI::BettingEnum::MarketBettingType::FIXED_ODDS);
    
    //test for a single one
    nlohmann::json j = market_filter;
    EXPECT_TRUE(j.contains("marketBettingTypes"));
    EXPECT_EQ(j["marketBettingTypes"], nlohmann::json::array({"FIXED_ODDS"}));
    
    
    //test for multiple
    market_filter.addMarketBettingType(BetfairAPI::BettingEnum::MarketBettingType::ASIAN_HANDICAP_SINGLE_LINE);
    j = market_filter;
    EXPECT_TRUE(j.contains("marketBettingTypes"));
    EXPECT_EQ(j["marketBettingTypes"], nlohmann::json::array({"FIXED_ODDS","ASIAN_HANDICAP_SINGLE_LINE"}));
}

TEST(BettingTypeSerialiser,MarketFilterCompetitionIds) {
    BetfairAPI::BettingType::MarketFilter market_filter;
    market_filter.addCompetitionId("123456");
    
    //test for a single one
    nlohmann::json j = market_filter;
    EXPECT_TRUE(j.contains("competitionIds"));
    EXPECT_EQ(j["competitionIds"], nlohmann::json::array({"123456"}));
    
    //test for multiple
    market_filter.addCompetitionId("98765");
    j = market_filter;
    EXPECT_TRUE(j.contains("competitionIds"));
    EXPECT_EQ(j["competitionIds"], nlohmann::json::array({"123456","98765"}));
}

TEST(BettingTypeSerialiser,EventTypeConstruction) {
    BetfairAPI::BettingType::EventType e("123","name");
    nlohmann::json j {{"id","123"},{"name","name"}};
    auto eventType = j.get<BetfairAPI::BettingType::EventType>();
    
    EXPECT_EQ(eventType,e);
}

TEST(BettingTypeSerialiser,EventTypeResultsConstruction) {
    BetfairAPI::BettingType::EventType e("123","name");
    BetfairAPI::BettingType::EventTypeResults e_res(e,110);
    
    nlohmann::json j {{"eventType",{{"id","123"},{"name","name"}}},{"marketCount",110}};
    auto eventTypeResult = j.get<BetfairAPI::BettingType::EventTypeResults>();
    
    EXPECT_EQ(eventTypeResult.getEventType(),e);
    EXPECT_EQ(eventTypeResult.getMarketCount(),110);
}