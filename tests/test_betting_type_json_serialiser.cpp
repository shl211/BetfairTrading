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

TEST(BettingTypeSerialiser,KeyLineSelectionConstruction) {
    // Create a KeyLineSelection object
    long selection_id = 123456;
    double handicap = 2.5;
    BetfairAPI::BettingType::KeyLineSelection key_line_selection(selection_id, handicap);

    // Serialise to JSON
    nlohmann::json j = key_line_selection;

    // Check JSON fields
    EXPECT_EQ(j.at("selectionId"), selection_id);
    EXPECT_EQ(j.at("handicap"), handicap);

    // Deserialise from JSON
    auto parsed = j.get<BetfairAPI::BettingType::KeyLineSelection>();

    // Check values
    EXPECT_EQ(parsed.getSelectionId(), selection_id);
    EXPECT_EQ(parsed.getHandicap(), handicap);
}

TEST(BettingTypeSerialiser,KeyLineDescriptionConstruction) {
    // Create KeyLineSelection objects
    BetfairAPI::BettingType::KeyLineSelection sel1(123, 1.5);
    BetfairAPI::BettingType::KeyLineSelection sel2(456, 2.5);

    // Create a KeyLineDescription object
    std::vector<BetfairAPI::BettingType::KeyLineSelection> selections{sel1, sel2};
    BetfairAPI::BettingType::KeyLineDescription key_line_desc(selections);

    // Serialise to JSON
    nlohmann::json j = key_line_desc;

    // Check JSON fields
    EXPECT_TRUE(j.contains("keyLine"));
    ASSERT_EQ(j.at("keyLine").size(), 2);
    EXPECT_EQ(j.at("keyLine").at(0).at("selectionId"), 123);
    EXPECT_EQ(j.at("keyLine").at(0).at("handicap"), 1.5);
    EXPECT_EQ(j.at("keyLine").at(1).at("selectionId"), 456);
    EXPECT_EQ(j.at("keyLine").at(1).at("handicap"), 2.5);

    // Deserialise from JSON
    auto parsed = j.get<BetfairAPI::BettingType::KeyLineDescription>();

    // Check values
    ASSERT_EQ(parsed.getKeyLine().size(), 2);
    EXPECT_EQ(parsed.getKeyLine()[0], sel1);
    EXPECT_EQ(parsed.getKeyLine()[1], sel2);
}

TEST(BettingTypeSerialiser, PriceSizeToJsonFromJson) {
    double price = 3.75;
    double size = 50.0;
    BetfairAPI::BettingType::PriceSize price_size(price, size);

    // Serialize to JSON
    nlohmann::json j = price_size;
    EXPECT_TRUE(j.contains("price"));
    EXPECT_TRUE(j.contains("size"));
    EXPECT_EQ(j["price"], price);
    EXPECT_EQ(j["size"], size);

    // Deserialize from JSON
    auto parsed = j.get<BetfairAPI::BettingType::PriceSize>();
    EXPECT_EQ(parsed.getPrice(), price);
    EXPECT_EQ(parsed.getSize(), size);
}

TEST(BettingTypeSerialiser, StartingPricesToJsonFromJson) {
    BetfairAPI::BettingType::StartingPrices sp(
        2.5, // nearPrice
        3.0, // farPrice
        2.75, // actualSP
        {BetfairAPI::BettingType::PriceSize(2.5, 100.0)}, // backStakeTaken
        {BetfairAPI::BettingType::PriceSize(3.0, 50.0)}  // layLiabilityTaken
    );

    // Serialize to JSON
    nlohmann::json j = sp;
    EXPECT_TRUE(j.contains("nearPrice"));
    EXPECT_TRUE(j.contains("farPrice"));
    EXPECT_TRUE(j.contains("backStakeTaken"));
    EXPECT_TRUE(j.contains("layLiabilityTaken"));
    EXPECT_TRUE(j.contains("actualSP"));
    EXPECT_EQ(j.at("nearPrice"), 2.5);
    EXPECT_EQ(j.at("farPrice"), 3.0);
    EXPECT_EQ(j.at("actualSP"), 2.75);
    ASSERT_EQ(j.at("backStakeTaken").size(), 1);
    ASSERT_EQ(j.at("layLiabilityTaken").size(), 1);
    EXPECT_EQ(j.at("backStakeTaken").at(0).at("price"), 2.5);
    EXPECT_EQ(j.at("backStakeTaken").at(0).at("size"), 100.0);
    EXPECT_EQ(j.at("layLiabilityTaken").at(0).at("price"), 3.0);
    EXPECT_EQ(j.at("layLiabilityTaken").at(0).at("size"), 50.0);

    // Deserialize from JSON
    auto parsed = j.get<BetfairAPI::BettingType::StartingPrices>();
    EXPECT_EQ(parsed.getNearPrice(), 2.5);
    EXPECT_EQ(parsed.getFarPrice(), 3.0);
    EXPECT_EQ(parsed.getActualSP(), 2.75);
    ASSERT_EQ(parsed.getBackStakeTaken().size(), 1);
    ASSERT_EQ(parsed.getLayLiabilityTaken().size(), 1);
    EXPECT_EQ(parsed.getBackStakeTaken()[0].getPrice(), 2.5);
    EXPECT_EQ(parsed.getBackStakeTaken()[0].getSize(), 100.0);
    EXPECT_EQ(parsed.getLayLiabilityTaken()[0].getPrice(), 3.0);
    EXPECT_EQ(parsed.getLayLiabilityTaken()[0].getSize(), 50.0);
}

TEST(BettingTypeSerialiser, ExchangePricesToJsonFromJson) {
    // Create ExchangePrices object
    std::vector<BetfairAPI::BettingType::PriceSize> availableToBack = {
        BetfairAPI::BettingType::PriceSize(2.0, 100.0),
        BetfairAPI::BettingType::PriceSize(2.2, 50.0)
    };
    std::vector<BetfairAPI::BettingType::PriceSize> availableToLay = {
        BetfairAPI::BettingType::PriceSize(2.5, 80.0),
        BetfairAPI::BettingType::PriceSize(2.6, 40.0)
    };
    std::vector<BetfairAPI::BettingType::PriceSize> tradedVolume = {
        BetfairAPI::BettingType::PriceSize(2.0, 200.0),
        BetfairAPI::BettingType::PriceSize(2.5, 150.0)
    };

    BetfairAPI::BettingType::ExchangePrices ex_prices(
        availableToBack,
        availableToLay,
        tradedVolume
    );

    // Serialize to JSON
    nlohmann::json j = ex_prices;
    EXPECT_TRUE(j.contains("availableToBack"));
    EXPECT_TRUE(j.contains("availableToLay"));
    EXPECT_TRUE(j.contains("tradedVolume"));
    ASSERT_EQ(j.at("availableToBack").size(), 2);
    ASSERT_EQ(j.at("availableToLay").size(), 2);
    ASSERT_EQ(j.at("tradedVolume").size(), 2);
    EXPECT_EQ(j.at("availableToBack").at(0).at("price"), 2.0);
    EXPECT_EQ(j.at("availableToBack").at(0).at("size"), 100.0);
    EXPECT_EQ(j.at("availableToLay").at(1).at("price"), 2.6);
    EXPECT_EQ(j.at("availableToLay").at(1).at("size"), 40.0);
    EXPECT_EQ(j.at("tradedVolume").at(0).at("price"), 2.0);
    EXPECT_EQ(j.at("tradedVolume").at(0).at("size"), 200.0);

    // Deserialize from JSON
    auto parsed = j.get<BetfairAPI::BettingType::ExchangePrices>();
    ASSERT_EQ(parsed.getAvailableToBack().size(), 2);
    ASSERT_EQ(parsed.getAvailableToLay().size(), 2);
    ASSERT_EQ(parsed.getTradedVolume().size(), 2);
    EXPECT_EQ(parsed.getAvailableToBack()[0].getPrice(), 2.0);
    EXPECT_EQ(parsed.getAvailableToBack()[0].getSize(), 100.0);
    EXPECT_EQ(parsed.getAvailableToLay()[1].getPrice(), 2.6);
    EXPECT_EQ(parsed.getAvailableToLay()[1].getSize(), 40.0);
    EXPECT_EQ(parsed.getTradedVolume()[0].getPrice(), 2.0);
    EXPECT_EQ(parsed.getTradedVolume()[0].getSize(), 200.0);
}

TEST(BettingTypeSerialiser, MatchToJsonFromJson) {
    std::string bet_id = "bet123";
    std::string match_id = "456789";
    double price = 2.5;
    double size = 100.0;
    auto side = BetfairAPI::BettingEnum::Side::BACK;
    BetfairAPI::Utils::Date match_time = BetfairAPI::Utils::Date("2024-06-01T12:34:56Z");

    BetfairAPI::BettingType::Match match(side,price,size,bet_id,match_id,match_time);

    // Serialize to JSON
    nlohmann::json j = match;

    // Deserialize from JSON
    auto parsed = j.get<BetfairAPI::BettingType::Match>();
    EXPECT_EQ(parsed.getBetId(), bet_id);
    EXPECT_EQ(parsed.getMatchId(), match_id);
    EXPECT_EQ(parsed.getPrice(), price);
    EXPECT_EQ(parsed.getSize(), size);
    EXPECT_EQ(parsed.getSide(), side);
    EXPECT_EQ(parsed.getMatchDate(), match_time);
}

TEST(BettingTypeSerialiser, OrderToJsonFromJson) {
    BetfairAPI::BettingType::OrderParams params;
    params.bet_id = "bet123";
    params.order_type = BetfairAPI::BettingEnum::OrderType::LIMIT;
    params.order_status = BetfairAPI::BettingEnum::OrderStatus::EXECUTABLE;
    params.persistence_type = BetfairAPI::BettingEnum::PersistenceType::LAPSE;
    params.side = BetfairAPI::BettingEnum::Side::BACK;
    params.price = 2.5;
    params.size = 100.0;
    params.bsp_liability = 0.0;
    params.placed_date = BetfairAPI::Utils::Date("2024-06-01T12:34:56Z");
    params.avg_price_matched = 2.6;
    params.size_matched = 50.0;
    params.size_remaining = 50.0;
    params.size_lapsed = 0.0;
    params.size_cancelled = 0.0;
    params.size_voided = 0.0;
    params.customer_order_ref = "orderRef";
    params.customer_strategy_ref = "strategyRef";

    BetfairAPI::BettingType::Order order(params);

    // Serialise to JSON
    nlohmann::json j = order;

    // Deserialise from JSON
    auto parsed = j.get<BetfairAPI::BettingType::Order>();
    EXPECT_EQ(parsed.getBetId(), params.bet_id) << "bet_id mismatch";
    EXPECT_EQ(parsed.getOrderType(), params.order_type) << "order_type mismatch";
    EXPECT_EQ(parsed.getOrderStatus(), params.order_status) << "order_status mismatch";
    EXPECT_EQ(parsed.getPersistenceType(), params.persistence_type) << "persistence_type mismatch";
    EXPECT_EQ(parsed.getSide(), params.side) << "side mismatch";
    EXPECT_EQ(parsed.getPrice(), params.price) << "price mismatch";
    EXPECT_EQ(parsed.getSize(), params.size) << "size mismatch";
    EXPECT_EQ(parsed.getBspLiability(), params.bsp_liability) << "bsp_liability mismatch";
    EXPECT_EQ(parsed.getPlacedDate(), params.placed_date) << "placed_date mismatch";
    EXPECT_EQ(parsed.getAvgPriceMatched(), params.avg_price_matched) << "avg_price_matched mismatch";
    EXPECT_EQ(parsed.getSizeMatched(), params.size_matched) << "size_matched mismatch";
    EXPECT_EQ(parsed.getSizeRemaining(), params.size_remaining) << "size_remaining mismatch";
    EXPECT_EQ(parsed.getSizeLapsed(), params.size_lapsed) << "size_lapsed mismatch";
    EXPECT_EQ(parsed.getSizeCancelled(), params.size_cancelled) << "size_cancelled mismatch";
    EXPECT_EQ(parsed.getSizeVoided(), params.size_voided) << "size_voided mismatch";
    EXPECT_EQ(parsed.getCustomerOrderRef(), params.customer_order_ref) << "customer_order_ref mismatch";
    EXPECT_EQ(parsed.getCustomerStrategyRef(), params.customer_strategy_ref) << "customer_strategy_ref mismatch";
}

TEST(BettingTypeSerialiser, MarketBookToJsonFromJson) {
    // Prepare MarketBook fields
    std::string market_id = "1.23456789";
    bool is_market_data_delayed = false;
    auto status = BetfairAPI::BettingEnum::MarketStatus::OPEN;
    bool bet_delay = 5;
    bool bsp_reconciled = true;
    bool complete = false;
    bool inplay = true;
    int number_of_winners = 1;
    int number_of_runners = 10;
    int number_of_active_runners = 8;
    BetfairAPI::Utils::Date last_match_time("2024-06-01T12:34:56Z");
    double total_matched = 12345.67;
    double total_available = 2345.67;
    bool cross_matching = true;
    bool runners_voidable = false;
    long version = 123456789;
    std::vector<BetfairAPI::BettingType::Runner> runners {
        {123455,1.023, BetfairAPI::BettingEnum::RunnerStatus::ACTIVE}
    };
    BetfairAPI::BettingType::KeyLineDescription key_line_description({{1,1}});

    BetfairAPI::BettingType::MarketBook m_book(market_id,is_market_data_delayed);
    m_book.setStatus(status);
    m_book.setBetDelay(bet_delay);
    m_book.setBspReconciled(bsp_reconciled);
    m_book.setComplete(complete);
    m_book.setInplay(inplay);
    m_book.setNumberOfWinners(number_of_winners);
    m_book.setNumberOfRunners(number_of_runners);
    m_book.setNumberOfActiveRunners(number_of_active_runners);
    m_book.setLastMatchTime(last_match_time);
    m_book.setTotalMatched(total_matched);
    m_book.setTotalAvailable(total_available);
    m_book.setCrossMatching(cross_matching);
    m_book.setRunnersVoidable(runners_voidable);
    m_book.setVersion(version);
    for(auto& i : runners) {
        m_book.addRunners(i);
    }

    //convert to and from json
    nlohmann::json j = m_book; 

    auto market_book = j.get<BetfairAPI::BettingType::MarketBook>();
    EXPECT_EQ(market_book.getMarketId(), market_id);
    EXPECT_EQ(market_book.isMarketDataDelayed(), is_market_data_delayed);
    EXPECT_EQ(market_book.getStatus(), status);
    EXPECT_EQ(market_book.getBetDelay(), bet_delay);
    EXPECT_EQ(market_book.isBspReconciled(), bsp_reconciled);
    EXPECT_EQ(market_book.isComplete(), complete);
    EXPECT_EQ(market_book.isInplay(), inplay);
    EXPECT_EQ(market_book.getNumberOfWinners(), number_of_winners);
    EXPECT_EQ(market_book.getNumberOfRunners(), number_of_runners);
    EXPECT_EQ(market_book.getNumberOfActiveRunners(), number_of_active_runners);
    EXPECT_EQ(market_book.getLastMatchTime().toIsoString(), last_match_time.toIsoString());
    EXPECT_EQ(market_book.getTotalMatched(), total_matched);
    EXPECT_EQ(market_book.getTotalAvailable(), total_available);
    EXPECT_EQ(market_book.isCrossMatching(), cross_matching);
    EXPECT_EQ(market_book.isRunnersVoidable(), runners_voidable);
    EXPECT_EQ(market_book.getVersion(), version);
    //no tests for runners or keyline until they have == overloaded
}

TEST(BettingTypeSerialiser, MarketProfitLossConstruction) {
    // Prepare JSON for MarketProfitLoss with one RunnerProfitLoss
    std::string market_id = "1.23456789";
    double commission_applied = 2.5;
    long selection_id = 123456;
    double if_win = 100.0;
    double if_lose = -50.0;
    double if_place = 25.0;

    nlohmann::json j = {
        {"marketId", market_id},
        {"commissionApplied", commission_applied},
        {"profitAndLosses", {
            {
                {"selectionId", selection_id},
                {"ifWin", if_win},
                {"ifLose", if_lose},
                {"ifPlace", if_place}
            }
        }}
    };

    auto mpl = j.get<BetfairAPI::BettingType::MarketProfitLoss>();
    EXPECT_EQ(mpl.getMarketId(), market_id);
    EXPECT_EQ(mpl.getCommissionApplied(), commission_applied);
    const auto& rpl = mpl.getProfitLoss()[0];
    EXPECT_EQ(rpl.getSelectionId(), selection_id);
    EXPECT_EQ(rpl.getIfWin(), if_win);
    EXPECT_EQ(rpl.getIfLose(), if_lose);
    EXPECT_EQ(rpl.getIfPlace(), if_place);
}

TEST(BettingTypeSerialiser, RunnerProfitLossConstruction) {
    long selection_id = 987654;
    double if_win = 150.0;
    double if_lose = -75.0;
    double if_place = 30.0;

    nlohmann::json j = {
        {"selectionId", selection_id},
        {"ifWin", if_win},
        {"ifLose", if_lose},
        {"ifPlace", if_place}
    };

    auto rpl = j.get<BetfairAPI::BettingType::RunnerProfitLoss>();
    EXPECT_EQ(rpl.getSelectionId(), selection_id);
    EXPECT_EQ(rpl.getIfWin(), if_win);
    EXPECT_EQ(rpl.getIfLose(), if_lose);
    EXPECT_EQ(rpl.getIfPlace(), if_place);
}

TEST(BettingTypeSerialiser, MarketVersionConstruction) {
    long version = 987654321;

    nlohmann::json j = {
        {"version", version}
    };

    auto market_version = j.get<BetfairAPI::BettingType::MarketVersion>();
    EXPECT_EQ(market_version.getVersion(), version);
}

TEST(BettingTypeSerialiser, CurrentItemDescriptionConstruction) {
    BetfairAPI::BettingType::MarketVersion mv(123);
    BetfairAPI::BettingType::CurrentItemDescription item_desc(mv);

    // Serialize to JSON
    nlohmann::json j = item_desc;

    // Deserialize from JSON
    auto parsed = j.get<BetfairAPI::BettingType::CurrentItemDescription>();
    EXPECT_EQ(parsed.getMarketVersion(), mv);
}

TEST(BettingTypeSerialiser, CurrentOrderSummaryConstruction) {
    BetfairAPI::BettingType::CurrentOrderSummary order(
        "123",
        "456",
        1234,
        1,
        BetfairAPI::BettingType::PriceSize(2,3),
        12,
        BetfairAPI::BettingEnum::Side::BACK,
        BetfairAPI::BettingEnum::OrderStatus::EXECUTABLE,
        BetfairAPI::BettingEnum::PersistenceType::PERSIST,
        BetfairAPI::BettingEnum::OrderType::LIMIT,
        BetfairAPI::Utils::Date("2024-06-01T12:34:56Z"),
        BetfairAPI::Utils::Date("2024-06-01T12:34:59Z")
    );

    nlohmann::json j = order;

    BetfairAPI::BettingType::CurrentOrderSummary order_from_json = j;

    EXPECT_EQ(order_from_json.getBetId(), order.getBetId());
    EXPECT_EQ(order_from_json.getMarketId(), order.getMarketId());
    EXPECT_EQ(order_from_json.getSelectionId(), order.getSelectionId());
    EXPECT_EQ(order_from_json.getHandicap(), order.getHandicap());
    EXPECT_EQ(order_from_json.getPriceSize(), order.getPriceSize());
    EXPECT_EQ(order_from_json.getBspLiability(), order.getBspLiability());
    EXPECT_EQ(order_from_json.getSide(), order.getSide());
    EXPECT_EQ(order_from_json.getStatus(), order.getStatus());
    EXPECT_EQ(order_from_json.getPersistenceType(), order.getPersistenceType());
    EXPECT_EQ(order_from_json.getOrderType(), order.getOrderType());
    EXPECT_EQ(order_from_json.getPlacedDate(), order.getPlacedDate());
    EXPECT_EQ(order_from_json.getMatchedDate(), order.getMatchedDate());

    //and other optional ones???

}

TEST(BettingTypeSerialiser, ItemDescriptionFromJsonToJson) {
    // Prepare test data for ItemDescription
    BetfairAPI::BettingType::ItemDescription item_desc;
    item_desc.setEventTypeDesc("Horse Racing");
    item_desc.setEventDesc("Ascot");
    item_desc.setMarketDesc("WIN");
    item_desc.setMarketType("WIN");
    item_desc.setMarketStartTime(BetfairAPI::Utils::Date("2024-06-01T15:00:00Z"));
    item_desc.setRunnerDesc("RunnerName");
    item_desc.setNumberOfWinners(1);
    item_desc.setEachWayDivisor(0.25);

    // Serialize to JSON
    nlohmann::json j = item_desc;

    // Check JSON fields
    EXPECT_EQ(j.at("eventTypeDesc"), "Horse Racing");
    EXPECT_EQ(j.at("eventDesc"), "Ascot");
    EXPECT_EQ(j.at("marketDesc"), "WIN");
    EXPECT_EQ(j.at("marketType"), "WIN");
    EXPECT_EQ(j.at("marketStartTime"), "2024-06-01T15:00:00Z");
    EXPECT_EQ(j.at("runnerDesc"), "RunnerName");
    EXPECT_EQ(j.at("numberOfWinners"), 1);
    EXPECT_DOUBLE_EQ(j.at("eachWayDivisor"), 0.25);

    // Deserialize from JSON
    auto parsed = j.get<BetfairAPI::BettingType::ItemDescription>();

    // Check values
    EXPECT_EQ(parsed.getEventTypeDesc(), "Horse Racing");
    EXPECT_EQ(parsed.getEventDesc(), "Ascot");
    EXPECT_EQ(parsed.getMarketDesc(), "WIN");
    EXPECT_EQ(parsed.getMarketType(), "WIN");
    EXPECT_EQ(parsed.getMarketStartTime(), BetfairAPI::Utils::Date("2024-06-01T15:00:00Z"));
    EXPECT_EQ(parsed.getRunnerDesc(), "RunnerName");
    EXPECT_EQ(parsed.getNumberOfWinners(), 1);
    EXPECT_DOUBLE_EQ(parsed.getEachWayDivisor(), 0.25);
}

TEST(BettingTypeSerialiser, ClearedOrderSummaryTest) {
    BetfairAPI::BettingType::ClearedOrderSummary c;
    c.setBetId("bet123");
    c.setMarketId("market456");
    c.setSelectionId(789);
    c.setHandicap(1.5);
    c.setSide(BetfairAPI::BettingEnum::Side::BACK);
    c.setPriceRequested(100.0);
    c.setSizeSettled(0.0);
    c.setProfit(0.0);
    c.setCommission(0.0);
    c.setPlacedDate(BetfairAPI::Utils::Date("2024-06-01T12:34:56Z"));
    c.setSettledDate(BetfairAPI::Utils::Date("2024-06-01T12:35:56Z"));
    c.setCustomerOrderRef("orderRef");
    c.setCustomerStrategyRef("strategyRef");

    // Serialize to JSON
    nlohmann::json j = c;
    std::cout << "[DEBUG] Serialized JSON: " << j.dump(4) << std::endl;

    // Deserialize with exception handling
    BetfairAPI::BettingType::ClearedOrderSummary parsed;
    try {
        parsed = j.get<BetfairAPI::BettingType::ClearedOrderSummary>();
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Exception during deserialization: " << e.what() << std::endl;
        FAIL() << "Deserialization failed.";
    }

    // Check values
    EXPECT_EQ(parsed.getBetId(), "bet123");
    EXPECT_EQ(parsed.getMarketId(), "market456");
    EXPECT_EQ(parsed.getSelectionId(), 789);
    EXPECT_DOUBLE_EQ(parsed.getHandicap(), 1.5);
    EXPECT_EQ(parsed.getSide(), BetfairAPI::BettingEnum::Side::BACK);
    EXPECT_DOUBLE_EQ(parsed.getPriceRequested(), 100.0);
    EXPECT_DOUBLE_EQ(parsed.getSizeSettled(), 0.0);
    EXPECT_EQ(parsed.getProfit(), 0.0);
    EXPECT_DOUBLE_EQ(parsed.getCommission(), 0.0);
    EXPECT_EQ(parsed.getPlacedDate(), BetfairAPI::Utils::Date("2024-06-01T12:34:56Z"));
    EXPECT_EQ(parsed.getSettledDate(), BetfairAPI::Utils::Date("2024-06-01T12:35:56Z"));
    EXPECT_EQ(parsed.getCustomerOrderRef(), "orderRef");
    EXPECT_EQ(parsed.getCustomerStrategyRef(), "strategyRef");
}

TEST(BettingTypeSerialiser, ClearedOrderSummaryReportTest)  {
    // Prepare a ClearedOrderSummaryReport with multiple ClearedOrderSummary entries
    BetfairAPI::BettingType::ClearedOrderSummary summary1;
    summary1.setBetId("bet1");

    BetfairAPI::BettingType::ClearedOrderSummary summary2;
    summary2.setBetId("bet2");

    std::vector<BetfairAPI::BettingType::ClearedOrderSummary> summaries = {summary1, summary2};
    bool more_available = true;
    BetfairAPI::BettingType::ClearedOrderSummaryReport report(summaries, more_available);

    // Serialize to JSON
    nlohmann::json j = report;
    BetfairAPI::BettingType::ClearedOrderSummaryReport parsed = j;

    EXPECT_EQ(parsed.isMoreAvailable(), more_available);
    ASSERT_EQ(parsed.getClearedOrders().size(), 2);

    // Check first summary
    const auto& p1 = parsed.getClearedOrders()[0];
    EXPECT_EQ(p1.getBetId(), summary1.getBetId());

    // Check second summary
    const auto& p2 = parsed.getClearedOrders()[1];
    EXPECT_EQ(p2.getBetId(), summary2.getBetId());
}