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

TEST(BettingTypeSerialiser,MarketFilterMarketStartTime) {
    BetfairAPI::BettingType::MarketFilter market_filter;
    BetfairAPI::Utils::Date from_date("2024-06-01T12:00:00Z");
    BetfairAPI::Utils::Date to_date("2024-06-02T12:00:00Z");
    BetfairAPI::BettingType::TimeRange time_range(from_date, to_date);
    market_filter.setMarketStartTime(time_range);

    nlohmann::json j = market_filter;
    EXPECT_TRUE(j.contains("marketStartTime"));
    EXPECT_TRUE(j["marketStartTime"].contains("from"));
    EXPECT_TRUE(j["marketStartTime"].contains("to"));
    EXPECT_EQ(j["marketStartTime"]["from"], "2024-06-01T12:00:00Z");
    EXPECT_EQ(j["marketStartTime"]["to"], "2024-06-02T12:00:00Z");
}

TEST(BettingTypeSerialiser,MarketFilterMarketCountry) {
    BetfairAPI::BettingType::MarketFilter market_filter;
    market_filter.addMarketCountry("GB");

    // test for a single country
    nlohmann::json j = market_filter;
    EXPECT_TRUE(j.contains("marketCountries"));
    EXPECT_EQ(j["marketCountries"], nlohmann::json::array({"GB"}));

    // test for multiple countries
    market_filter.addMarketCountry("FR");
    j = market_filter;
    EXPECT_TRUE(j.contains("marketCountries"));
    EXPECT_EQ(j["marketCountries"], nlohmann::json::array({"GB", "FR"}));
}

TEST(BettingTypeSerialiser,TimeRangeToJson) {
    std::string from_str = "2024-06-01T12:00:00Z";
    std::string to_str = "2024-06-02T12:00:00Z";
    BetfairAPI::Utils::Date from_date(from_str);
    BetfairAPI::Utils::Date to_date(to_str);
    BetfairAPI::BettingType::TimeRange time_range(from_date, to_date);

    nlohmann::json j = time_range;

    EXPECT_TRUE(j.contains("from"));
    EXPECT_TRUE(j.contains("to"));
    EXPECT_EQ(j["from"], from_str);
    EXPECT_EQ(j["to"], to_str);
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

TEST(BettingTypeSerialiser,CountryCodeResultConstruction) {
    std::string country_code = "GB";
    int market_count = 99;

    nlohmann::json j{
        {"countryCode", country_code},
        {"marketCount", market_count}
    };
    auto country_code_result = j.get<BetfairAPI::BettingType::CountryCodeResult>();

    EXPECT_EQ(country_code_result.getCountryCode(), country_code);
    EXPECT_EQ(country_code_result.getMarketCount(), market_count);
}

TEST(BettingTypeSerialiser,VenueResultConstruction) {
    std::string venue = "Ascot";
    int market_count = 77;

    nlohmann::json j{
        {"venue", venue},
        {"marketCount", market_count}
    };
    auto venue_result = j.get<BetfairAPI::BettingType::VenueResult>();

    EXPECT_EQ(venue_result.getVenue(), venue);
    EXPECT_EQ(venue_result.getMarketCount(), market_count);
}

TEST(BettingTypeSerialiser,MarketLineRangeInfoConstruction) {
    double min = 1.5;
    double max = 3.5;
    double interval = 0.5;
    std::string m_unit = "1";

    nlohmann::json j{
        {"minUnitValue", min},
        {"maxUnitValue", max},
        {"interval", interval},
        {"marketUnit", m_unit}
    };
    auto info = j.get<BetfairAPI::BettingType::MarketLineRangeInfo>();

    EXPECT_EQ(info.getMinUnitValue(), min);
    EXPECT_EQ(info.getMaxUnitValue(), max);
    EXPECT_EQ(info.getInterval(), interval);
    EXPECT_EQ(info.getMarketUnit(),m_unit);
}

TEST(BettingTypeSerialiser,PriceLadderDescriptionConstructor) {
    BetfairAPI::BettingEnum::PriceLadderType type = BetfairAPI::BettingEnum::PriceLadderType::CLASSIC;
    BetfairAPI::BettingType::PriceLadderDescription desc(type);

    nlohmann::json j{
        {"type", "CLASSIC"},
    };
    auto parsed = j.get<BetfairAPI::BettingType::PriceLadderDescription>();

    EXPECT_EQ(parsed.getType(), type);
}

TEST(BettingTypeSerialiser,MarketDescriptionConstructor) {
    BetfairAPI::BettingType::MarketDescription desc;
    desc.setPersistenceEnabled(true);
    desc.setBspMarket(false);
    desc.setMarketTime(BetfairAPI::Utils::Date("2024-06-01T12:00:00Z"));
    desc.setSuspendTime(BetfairAPI::Utils::Date("2024-06-01T11:00:00Z"));
    desc.setSettleTime(BetfairAPI::Utils::Date("2024-06-01T13:00:00Z"));
    desc.setBettingType(BetfairAPI::BettingEnum::MarketBettingType::FIXED_ODDS);
    desc.setTurnInPlayEnabled(true);
    desc.setMarketType("WIN");
    desc.setRegulator("UKGC");
    desc.setMarketBaseRate(5.0);
    desc.setDiscountAllowed(true);
    desc.setWallet("Main");
    desc.setRules("Some rules");
    desc.setRulesHasDates(true);
    desc.setEachWayDivisor(0.25);
    desc.setClarifications("Clarification text");
    desc.setLineRangeInfo(BetfairAPI::BettingType::MarketLineRangeInfo(10.0, 1.0, 0.5, "unit"));
    desc.setRaceType("FLAT");
    desc.setPriceLadderDescription(BetfairAPI::BettingType::PriceLadderDescription(BetfairAPI::BettingEnum::PriceLadderType::CLASSIC));

    nlohmann::json j = {
        {"persistenceEnabled", true},
        {"bspMarket", false},
        {"marketTime", "2024-06-01T12:00:00Z"},
        {"suspendTime", "2024-06-01T11:00:00Z"},
        {"settleTime", "2024-06-01T13:00:00Z"},
        {"bettingType", "FIXED_ODDS"},
        {"turnInPlayEnabled", true},
        {"marketType", "WIN"},
        {"regulator", "UKGC"},
        {"marketBaseRate", 5.0},
        {"discountAllowed", true},
        {"wallet", "Main"},
        {"rules", "Some rules"},
        {"rulesHasDates", true},
        {"eachWayDivisor", 0.25},
        {"clarifications", "Clarification text"},
        {"lineRangeInfo", {
            {"maxUnitValue", 10.0},
            {"minUnitValue", 1.0},
            {"interval", 0.5},
            {"marketUnit", "unit"}
        }},
        {"raceType", "FLAT"},
        {"priceLadderDescription", {
            {"type", "CLASSIC"}
        }}
    };

    auto parsed = j.get<BetfairAPI::BettingType::MarketDescription>();

    EXPECT_EQ(parsed.isPersistenceEnabled(), desc.isPersistenceEnabled());
    EXPECT_EQ(parsed.isBspMarket(), desc.isBspMarket());
    EXPECT_EQ(parsed.getMarketTime(), desc.getMarketTime());
    EXPECT_EQ(parsed.getSuspendTime(), desc.getSuspendTime());
    EXPECT_EQ(parsed.getSettleTime(), desc.getSettleTime());
    EXPECT_EQ(parsed.getBettingType(), desc.getBettingType());
    EXPECT_EQ(parsed.isTurnInPlayEnabled(), desc.isTurnInPlayEnabled());
    EXPECT_EQ(parsed.getMarketType(), desc.getMarketType());
    EXPECT_EQ(parsed.getRegulator(), desc.getRegulator());
    EXPECT_EQ(parsed.getMarketBaseRate(), desc.getMarketBaseRate());
    EXPECT_EQ(parsed.isDiscountAllowed(), desc.isDiscountAllowed());
    EXPECT_EQ(parsed.getWallet(), desc.getWallet());
    EXPECT_EQ(parsed.getRules(), desc.getRules());
    EXPECT_EQ(parsed.hasRulesWithDates(), desc.hasRulesWithDates());
    EXPECT_EQ(parsed.getEachWayDivisor(), desc.getEachWayDivisor());
    EXPECT_EQ(parsed.getClarifications(), desc.getClarifications());
    EXPECT_EQ(parsed.getLineRangeInfo(), desc.getLineRangeInfo());
    EXPECT_EQ(parsed.getRaceType(), desc.getRaceType());
    EXPECT_EQ(parsed.getPriceLadderDescription().getType(),desc.getPriceLadderDescription().getType());
}

TEST(BettingTypeSerialiser,RunnerCatalogConstructor) {
    // Test with only mandatory fields
    {
        long selection_id = 12345;
        std::string name = "RunnerName";
        double handicap = 0.0;
        int sort_priority = 1;

        nlohmann::json j = {
            {"selectionId", selection_id},
            {"runnerName", name},
            {"handicap", handicap},
            {"sortPriority", sort_priority}
        };

        auto runner = j.get<BetfairAPI::BettingType::RunnerCatalog>();
        EXPECT_EQ(runner.getSelectionId(), selection_id);
        EXPECT_EQ(runner.getRunnerName(), name);
        EXPECT_EQ(runner.getHandicap(), handicap);
        EXPECT_EQ(runner.getSortPriority(), sort_priority);
        EXPECT_TRUE(runner.getMetadata().empty());
    }

    // Test with metadata present
    {
        long selection_id = 54321;
        std::string name = "AnotherRunner";
        double handicap = 1.5;
        int sort_priority = 2;
        std::map<std::string, std::string> metadata = {{"key1", "value1"}, {"key2", "value2"}};

        nlohmann::json j = {
            {"selectionId", selection_id},
            {"runnerName", name},
            {"handicap", handicap},
            {"sortPriority", sort_priority},
            {"metadata", metadata}
        };

        auto runner = j.get<BetfairAPI::BettingType::RunnerCatalog>();
        EXPECT_EQ(runner.getSelectionId(), selection_id);
        EXPECT_EQ(runner.getRunnerName(), name);
        EXPECT_EQ(runner.getHandicap(), handicap);
        EXPECT_EQ(runner.getSortPriority(), sort_priority);
        EXPECT_EQ(runner.getMetadata(), metadata);
    }
}

//TODO Fix at some point
TEST(BettingTypeSerialiser,MarketCatalogueConstructor) {
    // Test with only most common fields
    std::string market_id = "1.23456789";
    std::string market_name = "WIN";
    double total_matched = 1000.0;
    nlohmann::json j = {
        {"marketId", market_id},
        {"marketName", market_name},
        {"totalMatched", total_matched},
    };

    auto market_catalogue = j.get<BetfairAPI::BettingType::MarketCatalogue>();
    SCOPED_TRACE("Checking MarketCatalogue construction from JSON");
    EXPECT_EQ(market_catalogue.getMarketId(), market_id) << "marketId mismatch";
    EXPECT_EQ(market_catalogue.getMarketName(), market_name) << "marketName mismatch";
    EXPECT_EQ(market_catalogue.getTotalMatched(), total_matched) << "totalMatched mismatch";

    //test with otgher fields --> ???
}