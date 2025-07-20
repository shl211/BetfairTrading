#include <magic_enum.hpp>
#include "BetfairAPI/betting_type/json_serialiser.hpp"
#include "BetfairAPI/betting_type/time_range.h"
#include "BetfairAPI/betting_type/market_filter.h"
#include "BetfairAPI/betting_type/event_type.h"
#include "BetfairAPI/betting_type/event_type_result.h"
#include "BetfairAPI/betting_type/time_range_result.h"
#include "BetfairAPI/betting_type/competition.h"
#include "BetfairAPI/betting_type/competition_result.h"
#include "BetfairAPI/betting_type/event.h"
#include "BetfairAPI/betting_type/event_result.h"
#include "BetfairAPI/betting_type/market_type_result.h"
#include "BetfairAPI/betting_type/country_code_result.h"
#include "BetfairAPI/betting_type/venue_result.h"
#include "BetfairAPI/betting_type/market_catalogue.h"
#include "BetfairAPI/betting_type/market_line_range_info.h"
#include "BetfairAPI/betting_type/price_ladder_description.h"
#include "BetfairAPI/betting_type/market_description.h"
#include "BetfairAPI/betting_type/runner_catalog.h"
#include "BetfairAPI/betting_type/market_version.h"
#include "BetfairAPI/betting_type/current_item_description.h"
#include "BetfairAPI/betting_type/price_size.h"
#include "BetfairAPI/betting_type/current_order_summary.h"
#include "BetfairAPI/betting_type/current_order_summary_report.h"
#include "BetfairAPI/betting_type/runner_id.h"
#include "BetfairAPI/betting_type/item_description.h"
#include "BetfairAPI/betting_type/cleared_order_summary.h"
#include "BetfairAPI/betting_type/cleared_order_summary_report.h"

namespace BetfairAPI::BettingType {

    namespace {
        template<typename Enum>
        std::string to_string(Enum value) {
            return std::string(magic_enum::enum_name(value));
        };

        template<typename Enum>
        std::set<std::string> to_string(const std::set<Enum>& value) {
            std::set<std::string> result;
            for (const auto& v : magic_enum::enum_values<Enum>()) {
                result.insert(to_string<Enum>(v));
            }
            return result;
        };

        template<typename Enum>
        Enum from_string(std::string_view name) {
            auto result = magic_enum::enum_cast<Enum>(name);
            if (!result) {
                throw std::invalid_argument("Invalid enum string: " + std::string(name));
            }
            return result.value();
        };

        template<typename Enum>
        std::set<Enum> from_string(const std::set<std::string>& name) {
            std::set<Enum> result;
            for (const auto& v : name) {
                result.insert(from_string<Enum>(v));
            }
            return result;
        };
    }

    /**************************************************************************
    * TimeRange  
    **************************************************************************/
    template<>
    nlohmann::json JsonSer<TimeRange>::toJson(const TimeRange& obj) {
        nlohmann::json j{};
        if(obj.from) j["from"] = obj.from->getIsoString();
        if(obj.to) j["to"] = obj.to->getIsoString();
        return j.is_null() ? nlohmann::json::object() : j;
    }
    
    template<>
    TimeRange JsonSer<TimeRange>::fromJson(const nlohmann::json& j) {
        TimeRange tr;
        if(j.contains("from")) tr.from = BetfairAPI::Date(j.at("from").get<std::string>());
        if(j.contains("to")) tr.to = BetfairAPI::Date(j.at("to").get<std::string>());
        return tr;
    }
    
    /**************************************************************************
    * MarketFilter  
    **************************************************************************/
   
   template<>
   nlohmann::json JsonSer<MarketFilter>::toJson(const MarketFilter& obj) {
       nlohmann::json j = {};
       if(!obj.textQuery.empty()) j["textQuery"] = obj.textQuery;
       if(!obj.eventTypeIds.empty()) j["eventTypeIds"] = obj.eventTypeIds;
       if(!obj.eventIds.empty()) j["eventIds"] = obj.eventIds;
       if(!obj.competitionIds.empty()) j["competitionIds"] = obj.competitionIds;
       if(!obj.marketIds.empty()) j["marketIds"] = obj.marketIds;
       if(!obj.venues.empty()) j["venues"] = obj.venues;
       if(obj.bspOnly.has_value()) j["bspOnly"] = *(obj.bspOnly);
       if(obj.turnInPlayEnabled.has_value()) j["turnInPlayEnabled"] = *(obj.turnInPlayEnabled);
       if(obj.inPlayOnly.has_value()) j["inPlayOnly"] = *(obj.inPlayOnly);
       if(!obj.marketBettingTypes.empty()) j["marketBettingTypes"] = to_string<BettingEnum::MarketBettingType>(obj.marketBettingTypes);
       if(!obj.marketCountries.empty()) j["marketCountries"] = obj.marketCountries;
       if(!obj.marketTypeCodes.empty()) j["marketTypeCodes"] = obj.marketTypeCodes;
       if(obj.marketStartTime.has_value()) j["marketStartTime"] = JsonSer<TimeRange>::toJson(*(obj.marketStartTime));
       if(!obj.withOrders.empty()) j["withOrders"] = to_string<BettingEnum::OrderStatus>(obj.withOrders);
       if(!obj.raceTypes.empty()) j["raceTypes"] = obj.raceTypes;
       
       return j.is_null() ? nlohmann::json::object() : j;
    }
    
    template<>
    MarketFilter JsonSer<MarketFilter>::fromJson(const nlohmann::json& j) {
        MarketFilter mf;
        if(j.contains("textQuery")) mf.textQuery = j.at("textQuery").get<std::string>();
        if(j.contains("eventTypeIds")) mf.eventTypeIds = j.at("eventTypeIds").get<std::set<std::string>>();
        if(j.contains("eventIds")) mf.eventIds = j.at("eventIds").get<std::set<std::string>>();
        if(j.contains("competitionIds")) mf.competitionIds = j.at("competitionIds").get<std::set<std::string>>();
        if(j.contains("marketIds")) mf.marketIds = j.at("marketIds").get<std::set<std::string>>();
        if(j.contains("venues")) mf.venues = j.at("venues").get<std::set<std::string>>();
        if(j.contains("bspOnly")) mf.bspOnly = j.at("bspOnly").get<bool>();
        if(j.contains("turnInPlayEnabled")) mf.turnInPlayEnabled = j.at("turnInPlayEnabled").get<bool>();
        if(j.contains("inPlayOnly")) mf.inPlayOnly = j.at("inPlayOnly").get<bool>();
        
        if(j.contains("marketBettingTypes")) {
            auto s = j.at("marketBettingTypes").get<std::set<std::string>>();
            mf.marketBettingTypes = from_string<BettingEnum::MarketBettingType>(s);
        }
        
        if(j.contains("marketCountries")) mf.marketCountries = j.at("marketCountries").get<std::set<std::string>>();
        if(j.contains("marketTypeCodes")) mf.marketTypeCodes = j.at("marketTypeCodes").get<std::set<std::string>>();
        if(j.contains("marketStartTime")) mf.marketStartTime = JsonSer<TimeRange>::fromJson(j.at("marketStartTime"));
        
        if(j.contains("withOrders")) {
            auto s = j.at("withOrders").get<std::set<std::string>>() ;
            mf.withOrders = from_string<BettingEnum::OrderStatus>(s);
        }
        
        if(j.contains("raceTypes")) mf.raceTypes = j.at("raceTypes").get<std::set<std::string>>();
        
        return mf;
    }
    
    /**************************************************************************
    * EventType  
    **************************************************************************/
    template<>
    nlohmann::json JsonSer<EventType>::toJson(const EventType& obj) {
        nlohmann::json j = {};
        if(!obj.id.empty()) j["id"] = obj.id;
        if(!obj.name.empty()) j["name"] = obj.name;
        return j.is_null() ? nlohmann::json::object() : j;
    }
    
    template<>
    EventType JsonSer<EventType>::fromJson(const nlohmann::json& j) {
        EventType et;
        if(j.contains("id")) et.id = j.at("id").get<std::string>();
        if(j.contains("name")) et.name = j.at("name").get<std::string>();
        
        return et;
    }

    /**************************************************************************
    * EventTypeResult  
    **************************************************************************/
    template<>
    nlohmann::json JsonSer<EventTypeResult>::toJson(const EventTypeResult& obj) {
        nlohmann::json j = {};
        if(!obj.eventType.name.empty() && !obj.eventType.name.empty()) j["eventType"] = JsonSer<EventType>::toJson(obj.eventType);
        if(obj.marketCount > 0) j["marketCount"] = obj.marketCount;
        return j.is_null() ? nlohmann::json::object() : j;
    }
    
    template<>
    EventTypeResult JsonSer<EventTypeResult>::fromJson(const nlohmann::json& j) {
        EventTypeResult et;
        if(j.contains("eventType")) et.eventType = JsonSer<EventType>::fromJson(j.at("eventType"));
        if(j.contains("marketCount")) et.marketCount = j.at("marketCount").get<int>();
        return et;
    }

    /**************************************************************************
    * TimeRangeResult  
    **************************************************************************/
    template<>
    nlohmann::json JsonSer<TimeRangeResult>::toJson(const TimeRangeResult& obj) {
        nlohmann::json j = {};
        if(!obj.timeRange.from->getIsoString().empty() || !obj.timeRange.to->getIsoString().empty()) {
            j["timeRange"] = JsonSer<TimeRange>::toJson(obj.timeRange);
        } 
        if(obj.marketCount > 0) j["marketCount"] = obj.marketCount;
        return j.is_null() ? nlohmann::json::object() : j;
    }
    
    template<>
    TimeRangeResult JsonSer<TimeRangeResult>::fromJson(const nlohmann::json& j) {
        TimeRangeResult trr;
        if(j.contains("timeRange")) trr.timeRange = JsonSer<TimeRange>::fromJson(j.at("timeRange"));
        if(j.contains("marketCount")) trr.marketCount = j.at("marketCount").get<int>();
        return trr;
    }

    /**************************************************************************
    * Competition  
    **************************************************************************/
    template<>
    nlohmann::json JsonSer<Competition>::toJson(const Competition& obj) {
        nlohmann::json j = {};
        if(!obj.id.empty()) j["id"] = obj.id;
        if(!obj.name.empty()) j["name"] = obj.name;
        return j.is_null() ? nlohmann::json::object() : j;
    }
    
    template<>
    Competition JsonSer<Competition>::fromJson(const nlohmann::json& j) {
        Competition comp;
        if(j.contains("id")) comp.id = j.at("id").get<std::string>();
        if(j.contains("name")) comp.name = j.at("name").get<std::string>();
        return comp;
    }

    /**************************************************************************
    * CompetitionResult
    **************************************************************************/
    template<>
    nlohmann::json JsonSer<CompetitionResult>::toJson(const CompetitionResult& obj) {
        nlohmann::json j = {};
        j["competition"] = JsonSer<Competition>::toJson(obj.competition);
        if(obj.marketCount != 0) j["marketCount"] = obj.marketCount;
        if(!obj.competitionRegion.empty()) j["competitionRegion"] = obj.competitionRegion;
        return j.is_null() ? nlohmann::json::object() : j;
    }
    
    template<>
    CompetitionResult JsonSer<CompetitionResult>::fromJson(const nlohmann::json& j) {
        CompetitionResult comp_res;
        if(j.contains("competition")) comp_res.competition = JsonSer<Competition>::fromJson(j.at("competition"));
        if(j.contains("marketCount")) comp_res.marketCount = j.at("marketCount").get<int>();
        if(j.contains("competitionRegion")) comp_res.competitionRegion = j.at("competitionRegion").get<std::string>();
        return comp_res;
    }

    /**************************************************************************
    * Event
    **************************************************************************/
    template<>
    nlohmann::json JsonSer<Event>::toJson(const Event& obj) {
        nlohmann::json j = {};
        if(!obj.id.empty()) j["id"] = obj.id;
        if(!obj.name.empty()) j["name"] = obj.name;
        if(!obj.countryCode.empty()) j["countryCode"] = obj.countryCode;
        if(!obj.timezone.empty()) j["timezone"] = obj.timezone;
        if(!obj.venue.empty()) j["venue"] = obj.venue;
        if(obj.openDate) j["openDate"] = obj.openDate->getIsoString();
        return j.is_null() ? nlohmann::json::object() : j;
    }
    
    template<>
    Event JsonSer<Event>::fromJson(const nlohmann::json& j) {
        Event e;
        if(j.contains("id")) e.id = j.at("id").get<std::string>();
        if(j.contains("name")) e.name = j.at("name").get<std::string>();
        if(j.contains("countryCode")) e.countryCode = j.at("countryCode").get<std::string>();
        if(j.contains("timezone")) e.timezone = j.at("timezone").get<std::string>();
        if(j.contains("venue")) e.venue = j.at("venue").get<std::string>();
        if(j.contains("openDate")) e.openDate = BetfairAPI::Date(j.at("openDate").get<std::string>());
        return e;
    }

    /**************************************************************************
    * EventResult
    **************************************************************************/
    template<>
    nlohmann::json JsonSer<EventResult>::toJson(const EventResult& obj) {
        nlohmann::json j = {};
        j["event"] = JsonSer<Event>::toJson(obj.event);
        if(obj.marketCount > 0) j["marketCount"] = obj.marketCount;
        return j.is_null() ? nlohmann::json::object() : j;
    }
    
    template<>
    EventResult JsonSer<EventResult>::fromJson(const nlohmann::json& j) {
        EventResult e;
        if(j.contains("event")) e.event = JsonSer<Event>::fromJson(j.at("event"));
        if(j.contains("marketCount")) e.marketCount = j.at("marketCount").get<int>();
        return e;
    }

    /**************************************************************************
    * MarketTypeResult
    **************************************************************************/
    template<>
    nlohmann::json JsonSer<MarketTypeResult>::toJson(const MarketTypeResult& obj) {
        nlohmann::json j = {};
        if(!obj.marketType.empty()) j["marketType"] = obj.marketType;
        if(obj.marketCount > 0) j["marketCount"] = obj.marketCount;
        return j.is_null() ? nlohmann::json::object() : j;
    }
    
    template<>
    MarketTypeResult JsonSer<MarketTypeResult>::fromJson(const nlohmann::json& j) {
        MarketTypeResult mtr;
        if(j.contains("marketType")) mtr.marketType = j.at("marketType").get<std::string>();
        if(j.contains("marketCount")) mtr.marketCount = j.at("marketCount").get<int>();
        return mtr;
    }

    /**************************************************************************
    * CountryCodeResult
    **************************************************************************/
    template<>
    nlohmann::json JsonSer<CountryCodeResult>::toJson(const CountryCodeResult& obj) {
        nlohmann::json j = {};
        if(!obj.countryCode.empty()) j["countryCode"] = obj.countryCode;
        if(obj.marketCount > 0) j["marketCount"] = obj.marketCount;
        return j.is_null() ? nlohmann::json::object() : j;
    }
    
    template<>
    CountryCodeResult JsonSer<CountryCodeResult>::fromJson(const nlohmann::json& j) {
        CountryCodeResult mtr;
        if(j.contains("countryCode")) mtr.countryCode = j.at("countryCode").get<std::string>();
        if(j.contains("marketCount")) mtr.marketCount = j.at("marketCount").get<int>();
        return mtr;
    }

    /**************************************************************************
    * VenueResult
    **************************************************************************/
    template<>
    nlohmann::json JsonSer<VenueResult>::toJson(const VenueResult& obj) {
        nlohmann::json j = {};
        if(!obj.venue.empty()) j["venue"] = obj.venue;
        if(obj.marketCount > 0) j["marketCount"] = obj.marketCount;
        return j.is_null() ? nlohmann::json::object() : j;
    }
    
    template<>
    VenueResult JsonSer<VenueResult>::fromJson(const nlohmann::json& j) {
        VenueResult v_res;
        if(j.contains("venue")) v_res.venue = j.at("venue").get<std::string>();
        if(j.contains("marketCount")) v_res.marketCount = j.at("marketCount").get<int>();
        return v_res;
    }

    /**************************************************************************
    * MarketLineRangeInfo
    **************************************************************************/
    template<>
    nlohmann::json JsonSer<MarketLineRangeInfo>::toJson(const MarketLineRangeInfo& obj) {
        nlohmann::json j = {};
        if(obj.minUnitValue >= 0) j["minUnitValue"] = obj.minUnitValue;
        if(obj.maxUnitValue >= 0) j["maxUnitValue"] = obj.maxUnitValue;
        if(obj.interval >= 0) j["interval"] = obj.interval;
        if(!obj.marketUnit.empty()) j["marketUnit"] = obj.marketUnit;
        return j.is_null() ? nlohmann::json::object() : j;
    }
    
    template<>
    MarketLineRangeInfo JsonSer<MarketLineRangeInfo>::fromJson(const nlohmann::json& j) {
        MarketLineRangeInfo m_cat;
        if(j.contains("minUnitValue")) m_cat.minUnitValue = j.at("minUnitValue").get<double>();
        if(j.contains("maxUnitValue")) m_cat.maxUnitValue = j.at("maxUnitValue").get<double>();
        if(j.contains("interval")) m_cat.interval = j.at("interval").get<double>();
        if(j.contains("marketUnit")) m_cat.marketUnit = j.at("marketUnit").get<std::string>();
        return m_cat;
    }

    /**************************************************************************
    * PriceLadderDescription
    **************************************************************************/
    template<>
    nlohmann::json JsonSer<PriceLadderDescription>::toJson(const PriceLadderDescription& obj) {
        nlohmann::json j = {};
        if(obj.type) j["type"] = to_string<BettingEnum::PriceLadderType>(*obj.type);
        return j.is_null() ? nlohmann::json::object() : j;
    }
    
    template<>
    PriceLadderDescription JsonSer<PriceLadderDescription>::fromJson(const nlohmann::json& j) {
        PriceLadderDescription obj;
        if(j.contains("type")) obj.type = from_string<BettingEnum::PriceLadderType>(j.at("type").get<std::string>());
        return obj;
    }

    /**************************************************************************
    * RunnerCatalog
    **************************************************************************/
    template<>
    nlohmann::json JsonSer<RunnerCatalog>::toJson(const RunnerCatalog& obj) {
        nlohmann::json j = {};
        j["selectionId"] = obj.selectionId;
        j["runnerName"] = obj.runnerName;
        j["handicap"] = obj.handicap;
        j["sortPriority"] = obj.sortPriority;
        if(!obj.metadata.empty()) j["metadata"] = obj.metadata;
        return j.is_null() ? nlohmann::json::object() : j;
    }
    
    template<>
    RunnerCatalog JsonSer<RunnerCatalog>::fromJson(const nlohmann::json& j) {
        RunnerCatalog obj;
        if(j.contains("selectionId")) obj.selectionId = j.at("selectionId").get<int64_t>();
        if(j.contains("runnerName")) obj.runnerName = j.at("runnerName").get<std::string>();
        if(j.contains("handicap")) obj.handicap = j.at("handicap").get<double>();
        if(j.contains("sortPriority")) obj.sortPriority = j.at("sortPriority").get<int>();
        if(j.contains("metadata")) obj.metadata = j.at("metadata").get<std::map<std::string, std::string>>();
        return obj;
    }

    /**************************************************************************
    * MarketDescription
    **************************************************************************/
    template<>
    nlohmann::json JsonSer<MarketDescription>::toJson(const MarketDescription& obj) {
        nlohmann::json j = {};
        j["persistenceEnabled"] = obj.persistenceEnabled;
        j["bspMarket"] = obj.bspMarket;
        if(obj.marketTime) j["marketTime"] = obj.marketTime->getIsoString();
        if(obj.marketTime) j["suspendTime"] = obj.suspendTime->getIsoString();

        if(obj.settleTime) j["settleTime"] = obj.settleTime->getIsoString();

        j["bettingType"] = to_string<BettingEnum::MarketBettingType>(obj.bettingType);
        j["turnInPlayEnabled"] = obj.turnInPlay;
        j["marketType"] = obj.marketType;
        j["regulator"] = obj.regulator;
        j["marketBaseRate"] = obj.marketBaseRate;
        j["discountAllowed"] = obj.discountAllowed;
        if(!obj.wallet.empty()) j["wallet"] = obj.wallet;
        if(!obj.rules.empty()) j["rules"] = obj.rules;
        if(obj.rulesHasDate) j["rulesHasDates"] = *obj.rulesHasDate;
        if(obj.eachWayDivisor > 0) j["eachWayDivisor"] = obj.eachWayDivisor;
        if(!obj.clarifications.empty()) j["clarifications"] = obj.clarifications;
        if(obj.lineRangeInfo) j["lineRangeInfo"] = JsonSer<MarketLineRangeInfo>::toJson(*obj.lineRangeInfo);
        if(!obj.raceType.empty()) j["raceType"] = obj.raceType;
        if(obj.priceLadderDescription) j["priceLadderDescription"] = JsonSer<PriceLadderDescription>::toJson(*obj.priceLadderDescription);
        return j.is_null() ? nlohmann::json::object() : j;
    }
    
    template<>
    MarketDescription JsonSer<MarketDescription>::fromJson(const nlohmann::json& j) {
        MarketDescription obj;
        if(j.contains("persistenceEnabled")) obj.persistenceEnabled = j.at("persistenceEnabled").get<bool>();
        if(j.contains("bspMarket")) obj.bspMarket = j.at("bspMarket").get<bool>();
        if(j.contains("marketTime")) obj.marketTime = BetfairAPI::Date(j.at("marketTime").get<std::string>());
        if(j.contains("suspendTime")) obj.suspendTime = BetfairAPI::Date(j.at("suspendTime").get<std::string>());
        if(j.contains("settleTime")) obj.settleTime = BetfairAPI::Date(j.at("settleTime").get<std::string>());
        if(j.contains("bettingType")) obj.bettingType = from_string<BettingEnum::MarketBettingType>(j.at("bettingType").get<std::string>());
        if(j.contains("turnInPlayEnabled")) obj.turnInPlay = j.at("turnInPlayEnabled").get<bool>();
        if(j.contains("marketType")) obj.marketType = j.at("marketType").get<std::string>();
        if(j.contains("regulator")) obj.regulator = j.at("regulator").get<std::string>();
        if(j.contains("marketBaseRate")) obj.marketBaseRate = j.at("marketBaseRate").get<double>();
        if(j.contains("discountAllowed")) obj.discountAllowed = j.at("discountAllowed").get<bool>();
        if(j.contains("wallet")) obj.wallet = j.at("wallet").get<std::string>();
        if(j.contains("rules")) obj.rules = j.at("rules").get<std::string>();
        if(j.contains("rulesHasDates")) obj.rulesHasDate = j.at("rulesHasDates").get<bool>();
        if(j.contains("eachWayDivisor")) obj.eachWayDivisor = j.at("eachWayDivisor").get<double>();
        if(j.contains("clarifications")) obj.clarifications = j.at("clarifications").get<std::string>();
        if(j.contains("lineRangeInfo")) obj.lineRangeInfo = JsonSer<MarketLineRangeInfo>::fromJson(j.at("lineRangeInfo"));
        if(j.contains("raceType")) obj.raceType = j.at("raceType").get<std::string>();
        if(j.contains("priceLadderDescription")) obj.priceLadderDescription = JsonSer<PriceLadderDescription>::fromJson(j.at("priceLadderDescription"));
        return obj;
    }

    /**************************************************************************
    * MarketCatalogue
    **************************************************************************/
    template<>
    nlohmann::json JsonSer<MarketCatalogue>::toJson(const MarketCatalogue& obj) {
        nlohmann::json j = {};
        if(!obj.marketId.empty()) j["marketId"] = obj.marketId;
        if(!obj.marketName.empty()) j["marketName"] = obj.marketName;
        if(!obj.marketStartTime) j["marketStartTime"] = obj.marketStartTime->getIsoString();
        if(obj.totalMatched > 0) j["totalMatched"] = obj.totalMatched;
        if(obj.eventType) j["eventType"] = JsonSer<EventType>::toJson(*(obj.eventType));
        if(obj.competition) j["competition"] = JsonSer<Competition>::toJson(*(obj.competition));
        if(obj.description) j["description"] = JsonSer<MarketDescription>::toJson(*obj.description);
        if(obj.event) j["event"] = JsonSer<Event>::toJson(*obj.event);
        if(!obj.runners.empty()) {
            nlohmann::json runners_json = nlohmann::json::array();
            for (const auto& runner : obj.runners) {
                runners_json.push_back(JsonSer<RunnerCatalog>::toJson(runner));
            }
            j["runners"] = runners_json;
        } 
        return j.is_null() ? nlohmann::json::object() : j;
    }
    
    template<>
    MarketCatalogue JsonSer<MarketCatalogue>::fromJson(const nlohmann::json& j) {
        MarketCatalogue m_cat;
        if(j.contains("marketId")) m_cat.marketId = j.at("marketId").get<std::string>();
        if(j.contains("marketName")) m_cat.marketName = j.at("marketName").get<std::string>();
        if(j.contains("marketStartTime")) m_cat.marketStartTime = Date{j.at("marketStartTime").get<std::string>()};
        if(j.contains("totalMatched")) m_cat.totalMatched = j.at("totalMatched").get<double>();
        if(j.contains("eventType")) m_cat.eventType = JsonSer<EventType>::fromJson(j.at("eventType"));
        if(j.contains("competition")) m_cat.competition = JsonSer<Competition>::fromJson(j.at("competition"));
        if(j.contains("description")) m_cat.description = JsonSer<MarketDescription>::fromJson(j.at("description"));
        if(j.contains("event")) m_cat.event = JsonSer<Event>::fromJson(j.at("event"));
        if(j.contains("runners")) {
            m_cat.runners.reserve(std::size(j.at("runners")));
            for (const auto& runner_json : j.at("runners")) {
                m_cat.runners.push_back(JsonSer<RunnerCatalog>::fromJson(runner_json));
            }
        }

        return m_cat;
    }

    /**************************************************************************
    * MarketVersion
    **************************************************************************/
    template<>
    nlohmann::json JsonSer<MarketVersion>::toJson(const MarketVersion& obj) {
        nlohmann::json j = {};
        j["version"] = obj.version;
        return j;
    }
    
    template<>
    MarketVersion JsonSer<MarketVersion>::fromJson(const nlohmann::json& j) {
        MarketVersion mv;
        if(j.contains("version")) mv.version = j.at("version").get<long>();

        return mv;
    }

    /**************************************************************************
    * CurrentItemDescription
    **************************************************************************/
    template<>
    nlohmann::json JsonSer<CurrentItemDescription>::toJson(const CurrentItemDescription& obj) {
        nlohmann::json j = {};
        j["marketVersion"] = JsonSer<MarketVersion>::toJson(obj.marketVersion);
        return j;
    }
    
    template<>
    CurrentItemDescription JsonSer<CurrentItemDescription>::fromJson(const nlohmann::json& j) {
        CurrentItemDescription cid;
        if(j.contains("marketVersion")) cid.marketVersion = std::move(
            JsonSer<MarketVersion>::fromJson(j.at("marketVersion"))
        );

        return cid;
    }

    /**************************************************************************
    * PriceSize
    **************************************************************************/
    template<>
    nlohmann::json JsonSer<PriceSize>::toJson(const PriceSize& obj) {
        nlohmann::json j = {};
        j["price"] = obj.price;
        j["size"] = obj.size;
        return j;
    }
    
    template<>
    PriceSize JsonSer<PriceSize>::fromJson(const nlohmann::json& j) {
        PriceSize ps;
        if(j.contains("price")) ps.price = j.at("price").get<double>();
        if(j.contains("size")) ps.size = j.at("size").get<double>();

        return ps;
    }

    /**************************************************************************
    * CurrentOrderSummary
    **************************************************************************/
    template<>
    nlohmann::json JsonSer<CurrentOrderSummary>::toJson(const CurrentOrderSummary& obj) {
        nlohmann::json j = {};

        j["betId"] = obj.betId;
        j["marketId"] = obj.marketId;
        j["selectionId"] = obj.selectionId;
        j["handicap"] = obj.handicap;
        j["priceSize"] = JsonSer<PriceSize>::toJson(obj.priceSize);
        j["bspLiability"] = obj.bspLiability;
        j["side"] = to_string<BettingEnum::Side>(obj.side);
        j["status"] = to_string<BettingEnum::OrderStatus>(obj.status);
        j["persistenceType"] = to_string<BettingEnum::PersistenceType>(obj.persistenceType);
        j["orderType"] = to_string<BettingEnum::OrderType>(obj.orderType);
        if (obj.placedDate) j["placedDate"] = obj.placedDate->getIsoString();
        if (obj.matchedDate) j["matchedDate"] = obj.matchedDate->getIsoString();

        if(obj.averagePriceMatched) j["averagePriceMatched"] = *obj.averagePriceMatched;
        if(obj.sizeMatched) j["sizeMatched"] = *obj.sizeMatched;
        if(obj.sizeRemaining) j["sizeRemaining"] = *obj.sizeRemaining;
        if(obj.sizeLapsed) j["sizeLapsed"] = *obj.sizeLapsed;
        if(obj.sizeCancelled) j["sizeCancelled"] = *obj.sizeCancelled;
        if(obj.sizeVoided) j["sizeVoided"] = *obj.sizeVoided;
        if(obj.regulatorAuthCode) j["regulatorAuthCode"] = *obj.regulatorAuthCode;
        if(obj.regulatorCode) j["regulatorCode"] = *obj.regulatorCode;
        if(obj.customerOrderRef) j["customerOrderRef"] = *obj.customerOrderRef;
        if(obj.customerStrategyRef) j["customerStrategyRef"] = *obj.customerStrategyRef;
        if(obj.currentItemDescription) j["currentItemDescription"] = JsonSer<CurrentItemDescription>::toJson(*obj.currentItemDescription);
        if(obj.sourceIdKey) j["sourceIdKey"] = *obj.sourceIdKey;
        if(obj.sourceIdDescription) j["sourceIdDescription"] = *obj.sourceIdDescription;

        return j;
    }
    
    template<>
    CurrentOrderSummary JsonSer<CurrentOrderSummary>::fromJson(const nlohmann::json& j) {
        CurrentOrderSummary summary;

        if(j.contains("betId")) summary.betId = j.at("betId").get<std::string>();
        if(j.contains("marketId")) summary.marketId = j.at("marketId").get<std::string>();
        if(j.contains("selectionId")) summary.selectionId = j.at("selectionId").get<long>();
        if(j.contains("handicap")) summary.handicap = j.at("handicap").get<double>();
        if(j.contains("priceSize")) summary.priceSize = JsonSer<PriceSize>::fromJson(j.at("priceSize"));
        if(j.contains("bspLiability")) summary.bspLiability = j.at("bspLiability").get<double>();
        if(j.contains("side")) summary.side = from_string<BettingEnum::Side>(j.at("side").get<std::string>());
        if(j.contains("status")) summary.status = from_string<BettingEnum::OrderStatus>(j.at("status").get<std::string>());
        if(j.contains("persistenceType")) summary.persistenceType = from_string<BettingEnum::PersistenceType>(j.at("persistenceType").get<std::string>());
        if(j.contains("orderType")) summary.orderType = from_string<BettingEnum::OrderType>(j.at("orderType").get<std::string>());
        if(j.contains("placedDate")) summary.placedDate = BetfairAPI::Date(j.at("placedDate").get<std::string>());
        if(j.contains("matchedDate")) summary.matchedDate = BetfairAPI::Date(j.at("matchedDate").get<std::string>());
        if(j.contains("averagePriceMatched")) summary.averagePriceMatched = j.at("averagePriceMatched").get<double>();
        if(j.contains("sizeMatched")) summary.sizeMatched = j.at("sizeMatched").get<double>();
        if(j.contains("sizeRemaining")) summary.sizeRemaining = j.at("sizeRemaining").get<double>();
        if(j.contains("sizeLapsed")) summary.sizeLapsed = j.at("sizeLapsed").get<double>();
        if(j.contains("sizeCancelled")) summary.sizeCancelled = j.at("sizeCancelled").get<double>();
        if(j.contains("sizeVoided")) summary.sizeVoided = j.at("sizeVoided").get<double>();
        if(j.contains("regulatorAuthCode")) summary.regulatorAuthCode = j.at("regulatorAuthCode").get<std::string>();
        if(j.contains("regulatorCode")) summary.regulatorCode = j.at("regulatorCode").get<std::string>();
        if(j.contains("customerOrderRef")) summary.customerOrderRef = j.at("customerOrderRef").get<std::string>();
        if(j.contains("customerStrategyRef")) summary.customerStrategyRef = j.at("customerStrategyRef").get<std::string>();
        if(j.contains("currentItemDescription")) summary.currentItemDescription = JsonSer<CurrentItemDescription>::fromJson(j.at("currentItemDescription"));
        if(j.contains("sourceIdKey")) summary.sourceIdKey = j.at("sourceIdKey").get<std::string>();
        if(j.contains("sourceIdDescription")) summary.sourceIdDescription = j.at("sourceIdDescription").get<std::string>();
        return summary;
    }

    /**************************************************************************
    * CurrentOrderSummaryReport
    **************************************************************************/
    template<>
    nlohmann::json JsonSer<CurrentOrderSummaryReport>::toJson(const CurrentOrderSummaryReport& obj) {
        nlohmann::json j = {};

        if (!obj.currentOrders.empty()) {
            nlohmann::json orders_json = nlohmann::json::array();
            for (const auto& order : obj.currentOrders) {
                orders_json.push_back(JsonSer<CurrentOrderSummary>::toJson(order));
            }
            j["currentOrders"] = orders_json;
        }

        j["moreAvailable"] = obj.moreAvailable;
        return j;
    }
    
    template<>
    CurrentOrderSummaryReport JsonSer<CurrentOrderSummaryReport>::fromJson(const nlohmann::json& j) {
        CurrentOrderSummaryReport r;

        if(j.contains("currentOrders")) {
            r.currentOrders.reserve(std::size(j.at("currentOrders")));
            for (const auto& order_json : j.at("currentOrders")) {
                r.currentOrders.push_back(JsonSer<CurrentOrderSummary>::fromJson(order_json));
            }
        }
        if(j.contains("moreAvailable")) r.moreAvailable = j.at("moreAvailable").get<bool>();
        return r;
    }

    /**************************************************************************
    * RunnerId
    **************************************************************************/
    template<>
    nlohmann::json JsonSer<RunnerId>::toJson(const RunnerId& obj) {
        nlohmann::json j = {};
        j["marketId"] = obj.marketId;
        j["selectionId"] = obj.selectionId;
        if(obj.handicap) j["handicap"] = *obj.handicap;

        return j;
    }
    
    template<>
    RunnerId JsonSer<RunnerId>::fromJson(const nlohmann::json& j) {
        RunnerId r;
        if(j.contains("marketId")) r.marketId = j.at("marketId").get<std::string>();
        if(j.contains("selectionId")) r.selectionId = j.at("selectionId").get<long>();
        if(j.contains("handicap")) r.handicap = j.at("handicap").get<double>();
        
        return r;
    }

    /**************************************************************************
    * ItemDescription
    **************************************************************************/
    template<>
    nlohmann::json JsonSer<ItemDescription>::toJson(const ItemDescription& obj) {
        nlohmann::json j = {};
        if(obj.eventTypeDesc) j["eventTypeDesc"] = *obj.eventTypeDesc;
        if(obj.eventDesc) j["eventDesc"] = *obj.eventDesc;
        if(obj.marketDesc) j["marketDesc"] = *obj.marketDesc;
        if(obj.marketType) j["marketType"] = *obj.marketType;
        if(obj.marketStartTime) j["marketStartTime"] = obj.marketStartTime->getIsoString();
        if(obj.runnerDesc) j["runnerDesc"] = *obj.runnerDesc;
        if(obj.numberOfWinners) j["numberOfWinners"] = *obj.numberOfWinners;
        if(obj.eachWayDivisor) j["eachWayDivisor"] = *obj.eachWayDivisor;

        return j.is_null() ? nlohmann::json::object() : j;
    }
    
    template<>
    ItemDescription JsonSer<ItemDescription>::fromJson(const nlohmann::json& j) {
        ItemDescription desc;
        if(j.contains("eventTypeDesc")) desc.eventTypeDesc = j.at("eventTypeDesc").get<std::string>();
        if(j.contains("eventDesc")) desc.eventDesc = j.at("eventDesc").get<std::string>();
        if(j.contains("marketDesc")) desc.marketDesc = j.at("marketDesc").get<std::string>();
        if(j.contains("marketType")) desc.marketType = j.at("marketType").get<std::string>();
        if(j.contains("marketStartTime")) desc.marketStartTime = BetfairAPI::Date(j.at("marketStartTime").get<std::string>());
        if(j.contains("runnerDesc")) desc.runnerDesc = j.at("runnerDesc").get<std::string>();
        if(j.contains("numberOfWinners")) desc.numberOfWinners = j.at("numberOfWinners").get<int>();
        if(j.contains("eachWayDivisor")) desc.eachWayDivisor = j.at("eachWayDivisor").get<double>();

        return desc;
    }

    /**************************************************************************
    * ClearedOrderSummary
    **************************************************************************/
    template<>
    nlohmann::json JsonSer<ClearedOrderSummary>::toJson(const ClearedOrderSummary& obj) {
        nlohmann::json j = {};
        if(obj.eventTypeId) j["eventTypeId"] = *obj.eventTypeId;
        if(obj.eventId) j["eventId"] = *obj.eventId;
        if(obj.marketId) j["marketId"] = *obj.marketId;
        if(obj.selectionId) j["selectionId"] = *obj.selectionId;
        if(obj.handicap) j["handicap"] = *obj.handicap;
        if(obj.betId) j["betId"] = *obj.betId;
        if(obj.placedDate) j["placedDate"] = obj.placedDate->getIsoString();
        if(obj.persistenceType) j["persistenceType"] = to_string<BettingEnum::PersistenceType>(*obj.persistenceType);
        if(obj.orderType) j["orderType"] = to_string<BettingEnum::OrderType>(*obj.orderType);
        if(obj.side) j["side"] = to_string<BettingEnum::Side>(*obj.side);
        if(obj.itemDescription) j["itemDescription"] = JsonSer<ItemDescription>::toJson(*obj.itemDescription);
        if(obj.betOutcome) j["betOutcome"] = *obj.betOutcome;
        if(obj.priceRequested) j["priceRequested"] = *obj.priceRequested;
        if(obj.settledDate) j["settledDate"] = obj.settledDate->getIsoString();
        if(obj.lastMatchedDate) j["lastMatchedDate"] = obj.lastMatchedDate->getIsoString();
        if(obj.betCount) j["betCount"] = *obj.betCount;
        if(obj.commission) j["commission"] = *obj.commission;
        if(obj.priceMatched) j["priceMatched"] = *obj.priceMatched;
        if(obj.priceReduced) j["priceReduced"] = *obj.priceReduced;
        if(obj.sizeSettled) j["sizeSettled"] = *obj.sizeSettled;
        if(obj.profit) j["profit"] = *obj.profit;
        if(obj.sizeCancelled) j["sizeCancelled"] = *obj.sizeCancelled;
        if(obj.customerOrderRef) j["customerOrderRef"] = *obj.customerOrderRef;
        if(obj.customerStrategyRef) j["customerStrategyRef"] = *obj.customerStrategyRef;
        if(obj.sourceIdKey) j["sourceIdKey"] = *obj.sourceIdKey;
        if(obj.sourceIdDescription) j["sourceIdDescription"] = *obj.sourceIdDescription;

        return j.is_null() ? nlohmann::json::object() : j;
    }
    
    template<>
    ClearedOrderSummary JsonSer<ClearedOrderSummary>::fromJson(const nlohmann::json& j) {
        ClearedOrderSummary desc;
        if(j.contains("eventTypeId")) desc.eventTypeId = j.at("eventTypeId").get<std::string>();
        if(j.contains("eventId")) desc.eventId = j.at("eventId").get<std::string>();
        if(j.contains("marketId")) desc.marketId = j.at("marketId").get<std::string>();
        if(j.contains("selectionId")) desc.selectionId = j.at("selectionId").get<long>();
        if(j.contains("handicap")) desc.handicap = j.at("handicap").get<double>();
        if(j.contains("betId")) desc.betId = j.at("betId").get<std::string>();
        if(j.contains("placedDate")) desc.placedDate = BetfairAPI::Date(j.at("placedDate").get<std::string>());
        if(j.contains("persistenceType")) desc.persistenceType = from_string<BettingEnum::PersistenceType>(j.at("persistenceType").get<std::string>());
        if(j.contains("orderType")) desc.orderType = from_string<BettingEnum::OrderType>(j.at("orderType").get<std::string>());
        if(j.contains("side")) desc.side = from_string<BettingEnum::Side>(j.at("side").get<std::string>());
        if(j.contains("itemDescription")) desc.itemDescription = JsonSer<ItemDescription>::fromJson(j.at("itemDescription"));
        if(j.contains("betOutcome")) desc.betOutcome = j.at("betOutcome").get<std::string>();
        if(j.contains("priceRequested")) desc.priceRequested = j.at("priceRequested").get<double>();
        if(j.contains("settledDate")) desc.settledDate = BetfairAPI::Date(j.at("settledDate").get<std::string>());
        if(j.contains("lastMatchedDate")) desc.lastMatchedDate = BetfairAPI::Date(j.at("lastMatchedDate").get<std::string>());
        if(j.contains("betCount")) desc.betCount = j.at("betCount").get<int>();
        if(j.contains("commission")) desc.commission = j.at("commission").get<double>();
        if(j.contains("priceMatched")) desc.priceMatched = j.at("priceMatched").get<double>();
        if(j.contains("priceReduced")) desc.priceReduced = j.at("priceReduced").get<bool>();
        if(j.contains("sizeSettled")) desc.sizeSettled = j.at("sizeSettled").get<double>();
        if(j.contains("profit")) desc.profit = j.at("profit").get<double>();
        if(j.contains("sizeCancelled")) desc.sizeCancelled = j.at("sizeCancelled").get<double>();
        if(j.contains("customerOrderRef")) desc.customerOrderRef = j.at("customerOrderRef").get<std::string>();
        if(j.contains("customerStrategyRef")) desc.customerStrategyRef = j.at("customerStrategyRef").get<std::string>();
        if(j.contains("sourceIdKey")) desc.sourceIdKey = j.at("sourceIdKey").get<std::string>();
        if(j.contains("sourceIdDescription")) desc.sourceIdDescription = j.at("sourceIdDescription").get<std::string>();

        return desc;
    }

    /**************************************************************************
    * ClearedOrderSummaryReport
    **************************************************************************/
    template<>
    nlohmann::json JsonSer<ClearedOrderSummaryReport>::toJson(const ClearedOrderSummaryReport& obj) {
        nlohmann::json j = {};
        {
            nlohmann::json orders_json = nlohmann::json::array();
            for (const auto& order : obj.clearedOrders) {
                orders_json.push_back(JsonSer<ClearedOrderSummary>::toJson(order));
            }
            j["clearedOrders"] = orders_json;
        }
        j["moreAvailable"] = obj.moreAvailable;

        return j;
    }
    
    template<>
    ClearedOrderSummaryReport JsonSer<ClearedOrderSummaryReport>::fromJson(const nlohmann::json& j) {
        ClearedOrderSummaryReport desc;
        if(j.contains("clearedOrders")) {
            desc.clearedOrders.reserve(std::size(j.at("clearedOrders")));
            for (const auto& order_json : j.at("clearedOrders")) {
                desc.clearedOrders.push_back(JsonSer<ClearedOrderSummary>::fromJson(order_json));
            }
        }
        if(j.contains("moreAvailable")) desc.moreAvailable = j.at("moreAvailable").get<bool>();

        return desc;
    }
}