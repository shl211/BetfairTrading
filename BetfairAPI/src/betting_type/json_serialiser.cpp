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
}