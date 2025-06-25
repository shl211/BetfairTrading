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

TEST(BettingTypeSerialiser,MarketFilterEventIds) {
    BetfairAPI::BettingType::MarketFilter market_filter;
    market_filter.addEventId("123456");
    
    //test for a single one
    nlohmann::json j = market_filter;
    EXPECT_TRUE(j.contains("eventIds"));
    EXPECT_EQ(j["eventIds"], nlohmann::json::array({"123456"}));
    
    //test for multiple
    market_filter.addEventId("98765");
    j = market_filter;
    EXPECT_TRUE(j.contains("eventIds"));
    EXPECT_EQ(j["eventIds"], nlohmann::json::array({"123456","98765"}));
}

TEST(BettingTypeSerialiser,MarketFilterMarketIds) {
    BetfairAPI::BettingType::MarketFilter market_filter;
    market_filter.addMarketId("123456");
    
    //test for a single one
    nlohmann::json j = market_filter;
    EXPECT_TRUE(j.contains("marketIds"));
    EXPECT_EQ(j["marketIds"], nlohmann::json::array({"123456"}));
    
    //test for multiple
    market_filter.addMarketId("98765");
    j = market_filter;
    EXPECT_TRUE(j.contains("marketIds"));
    EXPECT_EQ(j["marketIds"], nlohmann::json::array({"123456","98765"}));
}

TEST(BettingTypeSerialiser,MarketFilterVenues) {
    BetfairAPI::BettingType::MarketFilter market_filter;
    market_filter.addVenue("Harlow");
    
    //test for a single one
    nlohmann::json j = market_filter;
    EXPECT_TRUE(j.contains("venues"));
    EXPECT_EQ(j["venues"], nlohmann::json::array({"Harlow"}));
    
    //test for multiple
    market_filter.addVenue("Race");
    j = market_filter;
    EXPECT_TRUE(j.contains("venues"));
    EXPECT_EQ(j["venues"], nlohmann::json::array({"Harlow","Race"}));
}

TEST(BettingTypeSerialiser,MarketFilterMarketTypeCodes) {
    BetfairAPI::BettingType::MarketFilter market_filter;
    market_filter.addMarketTypeCode("Winners");
    
    //test for a single one
    nlohmann::json j = market_filter;
    EXPECT_TRUE(j.contains("marketTypeCodes"));
    EXPECT_EQ(j["marketTypeCodes"], nlohmann::json::array({"Winners"}));
    
    //test for multiple
    market_filter.addMarketTypeCode("Race");
    j = market_filter;
    EXPECT_TRUE(j.contains("marketTypeCodes"));
    EXPECT_EQ(j["marketTypeCodes"], nlohmann::json::array({"Winners","Race"}));
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

TEST(BettingTypeSerialiser,CompetitionConstruction) {
    BetfairAPI::BettingType::Competition c("123","name");
    nlohmann::json j {{"id","123"},{"name","name"}};
    auto competition = j.get<BetfairAPI::BettingType::Competition>();
    
    EXPECT_EQ(competition,c);
}

TEST(BettingTypeSerialiser,CompetitionResultConstruction) {
    BetfairAPI::BettingType::Competition c("123","name");
    BetfairAPI::BettingType::CompetitionResult c_res(c,100,"GB");
    
    nlohmann::json j {{"competition",{{"id","123"},{"name","name"}}},{"marketCount",100},{"competitionRegion","GB"}};
    auto competition = j.get<BetfairAPI::BettingType::CompetitionResult>();
    
    EXPECT_EQ(competition.getCompetition(),c);
    EXPECT_EQ(competition.getCompetitionRegion(),"GB");
    EXPECT_EQ(competition.getMarketCount(),100);
}

TEST(BettingTypeSerialiser,EventConstruction) {
    std::string id{"123"};
    std::string name{"name"};
    std::string country_code{"GB"};
    std::string timezone{"GB"};
    std::string venue{"venue"};
    BetfairAPI::Utils::Date open_date{"2024-06-01T12:34:56Z"};
    BetfairAPI::BettingType::Event e(id, name,country_code,timezone,venue,open_date);

    nlohmann::json j{
        {"id", id},
        {"name", name},
        {"countryCode", country_code},
        {"timezone", timezone},
        {"venue", venue},
        {"openDate", open_date.toIsoString()}
    };
    auto event = j.get<BetfairAPI::BettingType::Event>();

    EXPECT_EQ(event, e);
}

TEST(BettingTypeSerialiser,EventResultConstruction) {
    std::string id{"123"};
    std::string name{"name"};
    std::string country_code{"GB"};
    std::string timezone{"GB"};
    std::string venue{"venue"};
    BetfairAPI::Utils::Date open_date{"2024-06-01T12:34:56Z"};
    BetfairAPI::BettingType::Event e(id, name,country_code,timezone,venue,open_date);

    int m_count {100};

    BetfairAPI::BettingType::EventResult e_res(e, m_count);

    nlohmann::json j{
        {"event", {
            {"id", id},
            {"name", name},
            {"countryCode", country_code},
            {"timezone", timezone},
            {"venue", venue},
            {"openDate", open_date.toIsoString()}
        }},
        {"marketCount", m_count}
    };
    auto event_result = j.get<BetfairAPI::BettingType::EventResult>();

    EXPECT_EQ(event_result.getEvent(), e);
    EXPECT_EQ(event_result.getMarketCount(), m_count);
}

TEST(BettingTypeSerialiser,MarketTypeResultConstruction) {
    std::string m_type = "MarketType";
    int m_count = 100;
    //BetfairAPI::BettingType::MarketTypeResult mtr(m_type,m_count);

    nlohmann::json j {
        {"marketType", m_type},
        {"marketCount", m_count},
    };
    auto mtr_res = j.get<BetfairAPI::BettingType::MarketTypeResult>();

    EXPECT_EQ(mtr_res.getMarketType(),m_type);
    EXPECT_EQ(mtr_res.getMarketCount(),m_count);
}

TEST(BettingTypeSerialiser,TimeRangeConstruction) {
    std::string from_str = "2024-06-01T12:00:00Z";
    std::string to_str = "2024-06-02T12:00:00Z";
    BetfairAPI::Utils::Date from_date(from_str);
    BetfairAPI::Utils::Date to_date(to_str);
    BetfairAPI::BettingType::TimeRange expected_time_range(from_date, to_date);

    nlohmann::json j{
        {"from", from_str},
        {"to", to_str}
    };
    auto time_range = j.get<BetfairAPI::BettingType::TimeRange>();

    EXPECT_EQ(time_range.getFromDate(), expected_time_range.getFromDate());
    EXPECT_EQ(time_range.getToDate(), expected_time_range.getToDate());
}

TEST(BettingTypeSerialiser,TimeRangeResultConstruction) {
    std::string from_str = "2024-06-01T12:00:00Z";
    std::string to_str = "2024-06-02T12:00:00Z";
    BetfairAPI::Utils::Date from_date(from_str);
    BetfairAPI::Utils::Date to_date(to_str);
    BetfairAPI::BettingType::TimeRange expected_time_range(from_date, to_date);
    int m_count = 42;

    nlohmann::json j{
        {"timeRange", {
            {"from", from_str},
            {"to", to_str}
        }},
        {"marketCount", m_count}
    };
    auto time_range_result = j.get<BetfairAPI::BettingType::TimeRangeResult>();

    EXPECT_EQ(time_range_result.getTimeRange(), expected_time_range);
    EXPECT_EQ(time_range_result.getMarketCount(), m_count);
}