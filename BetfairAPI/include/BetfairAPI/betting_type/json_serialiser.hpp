#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include "BetfairAPI/betting_enum/json_serialiser.hpp"
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
#include "BetfairAPI/betting_type/limit_order.h"
#include "BetfairAPI/betting_type/limit_on_close_order.h"
#include "BetfairAPI/betting_type/market_on_close_order.h"
#include "BetfairAPI/betting_type/place_instruction.h"
#include "BetfairAPI/betting_type/place_instruction_report.h"
#include "BetfairAPI/betting_type/place_execution_report.h"
#include "BetfairAPI/betting_type/cancel_instruction.h"
#include "BetfairAPI/betting_type/cancel_instruction_report.h"
#include "BetfairAPI/betting_type/cancel_execution_report.h"
#include "BetfairAPI/betting_type/replace_instruction.h"
#include "BetfairAPI/betting_type/replace_instruction_report.h"
#include "BetfairAPI/betting_type/replace_execution_report.h"
#include "BetfairAPI/betting_type/update_instruction.h"
#include "BetfairAPI/betting_type/update_instruction_report.h"
#include "BetfairAPI/betting_type/update_execution_report.h"
#include "BetfairAPI/betting_type/offers_overrides.h"
#include "BetfairAPI/betting_type/price_projection.h"
#include "BetfairAPI/betting_type/key_line_selection.h"
#include "BetfairAPI/betting_type/key_line_description.h"
#include "BetfairAPI/betting_type/starting_prices.h"
#include "BetfairAPI/betting_type/exchange_prices.h"
#include "BetfairAPI/betting_type/order.h"
#include "BetfairAPI/betting_type/match.h"
#include "BetfairAPI/betting_type/runner.h"
#include "BetfairAPI/betting_type/market_book.h"
#include "BetfairAPI/betting_type/runner_profit_loss.h"
#include "BetfairAPI/betting_type/market_profit_loss.h"

namespace BetfairAPI::BettingType {
    template<typename T>
    struct JsonSer {
        // These should be specialised per type
        static nlohmann::json toJson(const T& obj);
        static T fromJson(const nlohmann::json& j);
    };
    
    //Cleaner syntax for users
    template<typename T>
    nlohmann::json toJson(const T& obj) {
        return JsonSer<T>::toJson(obj);
    }
    
    template<typename T>
    T fromJson(const nlohmann::json& j) {
        return JsonSer<T>::fromJson(j);
    }
}

namespace BetfairAPI::BettingType {
    
    /**************************************************************************
    * TimeRange  
    **************************************************************************/
    inline void to_json(nlohmann::json& j,const TimeRange& tr) {
        if(tr.from) j["from"] = tr.from->getIsoString();
        if(tr.to) j["to"] = tr.to->getIsoString();
    }

    inline void from_json(const nlohmann::json& j, TimeRange& tr) {
        if(j.contains("from")) tr.from = BetfairAPI::Date(j.at("from").get<std::string>());
        if(j.contains("to")) tr.to = BetfairAPI::Date(j.at("to").get<std::string>());
    }

    /**************************************************************************
    * MarketFilter  
    **************************************************************************/
    inline void to_json(nlohmann::json& j,const MarketFilter& mf) {
        if(!mf.textQuery.empty()) j["textQuery"] = mf.textQuery;
        if(!mf.eventTypeIds.empty()) j["eventTypeIds"] = mf.eventTypeIds;
        if(!mf.eventIds.empty()) j["eventIds"] = mf.eventIds;
        if(!mf.competitionIds.empty()) j["competitionIds"] = mf.competitionIds;
        if(!mf.marketIds.empty()) j["marketIds"] = mf.marketIds;
        if(!mf.venues.empty()) j["venues"] = mf.venues;
        if(mf.bspOnly.has_value()) j["bspOnly"] = *(mf.bspOnly);
        if(mf.turnInPlayEnabled.has_value()) j["turnInPlayEnabled"] = *(mf.turnInPlayEnabled);
        if(mf.inPlayOnly.has_value()) j["inPlayOnly"] = *(mf.inPlayOnly);
        if(!mf.marketBettingTypes.empty()) j["marketBettingTypes"] = mf.marketBettingTypes;
        if(!mf.marketCountries.empty()) j["marketCountries"] = mf.marketCountries;
        if(!mf.marketTypeCodes.empty()) j["marketTypeCodes"] = mf.marketTypeCodes;
        if(mf.marketStartTime.has_value()) j["marketStartTime"] = *(mf.marketStartTime);
        if(!mf.withOrders.empty()) j["withOrders"] = mf.withOrders;
        if(!mf.raceTypes.empty()) j["raceTypes"] = mf.raceTypes;
    }
    
    inline void from_json(const nlohmann::json& j, MarketFilter& mf) {
        if(j.contains("textQuery")) mf.textQuery = j.at("textQuery").get<std::string>();
        if(j.contains("eventTypeIds")) mf.eventTypeIds = j.at("eventTypeIds").get<std::set<std::string>>();
        if(j.contains("eventIds")) mf.eventIds = j.at("eventIds").get<std::set<std::string>>();
        if(j.contains("competitionIds")) mf.competitionIds = j.at("competitionIds").get<std::set<std::string>>();
        if(j.contains("marketIds")) mf.marketIds = j.at("marketIds").get<std::set<std::string>>();
        if(j.contains("venues")) mf.venues = j.at("venues").get<std::set<std::string>>();
        if(j.contains("bspOnly")) mf.bspOnly = j.at("bspOnly").get<bool>();
        if(j.contains("turnInPlayEnabled")) mf.turnInPlayEnabled = j.at("turnInPlayEnabled").get<bool>();
        if(j.contains("inPlayOnly")) mf.inPlayOnly = j.at("inPlayOnly").get<bool>();
        if(j.contains("marketBettingTypes")) mf.marketBettingTypes = j.at("marketBettingTypes").get<std::set<BettingEnum::MarketBettingType>>();
        if(j.contains("marketCountries")) mf.marketCountries = j.at("marketCountries").get<std::set<std::string>>();
        if(j.contains("marketTypeCodes")) mf.marketTypeCodes = j.at("marketTypeCodes").get<std::set<std::string>>();
        if(j.contains("marketStartTime")) mf.marketStartTime = j.at("marketStartTime");
        if(j.contains("withOrders")) mf.withOrders = j.at("withOrders").get<std::set<BettingEnum::OrderStatus>>() ;
        if(j.contains("raceTypes")) mf.raceTypes = j.at("raceTypes").get<std::set<std::string>>();
    }


    /**************************************************************************
    * EventType  
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const EventType& et) {
        if(!et.id.empty()) j["id"] = et.id;
        if(!et.name.empty()) j["name"] = et.name;
    }

    inline void from_json(const nlohmann::json& j, EventType& et) {
        if(j.contains("id")) et.id = j.at("id").get<std::string>();
        if(j.contains("name")) et.name = j.at("name").get<std::string>();
    }

    /**************************************************************************
    * EventTypeResult  
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const EventTypeResult& obj) {
        if(!obj.eventType.name.empty() && !obj.eventType.id.empty()) j["eventType"] = obj.eventType;
        if(obj.marketCount > 0) j["marketCount"] = obj.marketCount;
    }

    inline void from_json(const nlohmann::json& j, EventTypeResult& et) {
        if(j.contains("eventType")) et.eventType = j.at("eventType").get<EventType>();
        if(j.contains("marketCount")) et.marketCount = j.at("marketCount").get<int>();
    }

    /**************************************************************************
    * TimeRangeResult  
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const TimeRangeResult& obj) {
        if(!obj.timeRange.from->getIsoString().empty() || !obj.timeRange.to->getIsoString().empty()) {
            j["timeRange"] = obj.timeRange;
        } 
        if(obj.marketCount > 0) j["marketCount"] = obj.marketCount;
    }

    inline void from_json(const nlohmann::json& j, TimeRangeResult& trr) {
        if(j.contains("timeRange")) trr.timeRange = j.at("timeRange").get<TimeRange>();
        if(j.contains("marketCount")) trr.marketCount = j.at("marketCount").get<int>();
    }

    /**************************************************************************
    * Competition  
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const Competition& obj) {
        if(!obj.id.empty()) j["id"] = obj.id;
        if(!obj.name.empty()) j["name"] = obj.name;
    }
    
    inline void from_json(const nlohmann::json& j, Competition& comp) {
        if(j.contains("id")) comp.id = j.at("id").get<std::string>();
        if(j.contains("name")) comp.name = j.at("name").get<std::string>();
    }

    /**************************************************************************
    * CompetitionResult
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const CompetitionResult& obj) {
        j["competition"] = obj.competition;
        if(obj.marketCount != 0) j["marketCount"] = obj.marketCount;
        if(!obj.competitionRegion.empty()) j["competitionRegion"] = obj.competitionRegion;
    }
    
    inline void from_json(const nlohmann::json& j, CompetitionResult& comp_res) {
        if(j.contains("competition")) comp_res.competition = j.at("competition").get<Competition>();
        if(j.contains("marketCount")) comp_res.marketCount = j.at("marketCount").get<int>();
        if(j.contains("competitionRegion")) comp_res.competitionRegion = j.at("competitionRegion").get<std::string>();
    }


    /**************************************************************************
    * Event
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const Event& obj) {
        if(!obj.id.empty()) j["id"] = obj.id;
        if(!obj.name.empty()) j["name"] = obj.name;
        if(!obj.countryCode.empty()) j["countryCode"] = obj.countryCode;
        if(!obj.timezone.empty()) j["timezone"] = obj.timezone;
        if(!obj.venue.empty()) j["venue"] = obj.venue;
        if(obj.openDate) j["openDate"] = obj.openDate->getIsoString();
    }

    inline void from_json(const nlohmann::json& j, Event& e) {
        if(j.contains("id")) e.id = j.at("id").get<std::string>();
        if(j.contains("name")) e.name = j.at("name").get<std::string>();
        if(j.contains("countryCode")) e.countryCode = j.at("countryCode").get<std::string>();
        if(j.contains("timezone")) e.timezone = j.at("timezone").get<std::string>();
        if(j.contains("venue")) e.venue = j.at("venue").get<std::string>();
        if(j.contains("openDate")) e.openDate = BetfairAPI::Date(j.at("openDate").get<std::string>());
    }
    

    /**************************************************************************
    * EventResult
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const EventResult& obj) {
        j["event"] = obj.event;
        if(obj.marketCount > 0) j["marketCount"] = obj.marketCount;
    }
    
    inline void from_json(const nlohmann::json& j, EventResult& e) {
        if(j.contains("event")) e.event = j.at("event").get<Event>();
        if(j.contains("marketCount")) e.marketCount = j.at("marketCount").get<int>();
    }

    /**************************************************************************
    * MarketTypeResult
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const MarketTypeResult& obj) {
        if(!obj.marketType.empty()) j["marketType"] = obj.marketType;
        if(obj.marketCount > 0) j["marketCount"] = obj.marketCount;
    }

    inline void from_json(const nlohmann::json& j, MarketTypeResult& mtr) {
        if(j.contains("marketType")) mtr.marketType = j.at("marketType").get<std::string>();
        if(j.contains("marketCount")) mtr.marketCount = j.at("marketCount").get<int>();
    }

    /**************************************************************************
    * CountryCodeResult
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const CountryCodeResult& obj) {
        if(!obj.countryCode.empty()) j["countryCode"] = obj.countryCode;
        if(obj.marketCount > 0) j["marketCount"] = obj.marketCount;
    }

    inline void from_json(const nlohmann::json& j, CountryCodeResult& mtr) {
        if(j.contains("countryCode")) mtr.countryCode = j.at("countryCode").get<std::string>();
        if(j.contains("marketCount")) mtr.marketCount = j.at("marketCount").get<int>();
    }

    /**************************************************************************
    * VenueResult
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const VenueResult& obj) {
        if(!obj.venue.empty()) j["venue"] = obj.venue;
        if(obj.marketCount > 0) j["marketCount"] = obj.marketCount;
    }

    inline void from_json(const nlohmann::json& j, VenueResult& v_res) {
        if(j.contains("venue")) v_res.venue = j.at("venue").get<std::string>();
        if(j.contains("marketCount")) v_res.marketCount = j.at("marketCount").get<int>();
    }
    

    /**************************************************************************
    * MarketLineRangeInfo
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const MarketLineRangeInfo& obj) {
        if(obj.minUnitValue >= 0) j["minUnitValue"] = obj.minUnitValue;
        if(obj.maxUnitValue >= 0) j["maxUnitValue"] = obj.maxUnitValue;
        if(obj.interval >= 0) j["interval"] = obj.interval;
        if(!obj.marketUnit.empty()) j["marketUnit"] = obj.marketUnit;
    }

    inline void from_json(const nlohmann::json& j, MarketLineRangeInfo& m_cat) {
        if(j.contains("minUnitValue")) m_cat.minUnitValue = j.at("minUnitValue").get<double>();
        if(j.contains("maxUnitValue")) m_cat.maxUnitValue = j.at("maxUnitValue").get<double>();
        if(j.contains("interval")) m_cat.interval = j.at("interval").get<double>();
        if(j.contains("marketUnit")) m_cat.marketUnit = j.at("marketUnit").get<std::string>();
    }    

    /**************************************************************************
    * PriceLadderDescription
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const PriceLadderDescription& obj) {
        if(obj.type) j["type"] = *obj.type;
    }

    inline void from_json(const nlohmann::json& j, PriceLadderDescription& obj) {
        if(j.contains("type")) obj.type = j.at("type").get<BettingEnum::PriceLadderType>();
    }

    /**************************************************************************
    * RunnerCatalog
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const RunnerCatalog& obj) {
        j["selectionId"] = obj.selectionId;
        j["runnerName"] = obj.runnerName;
        j["handicap"] = obj.handicap;
        j["sortPriority"] = obj.sortPriority;
        if (!obj.metadata.empty()) j["metadata"] = obj.metadata;
    }

    inline void from_json(const nlohmann::json& j, RunnerCatalog& obj) {
        if (j.contains("selectionId")) obj.selectionId = j.at("selectionId").get<long>();
        if (j.contains("runnerName")) obj.runnerName = j.at("runnerName").get<std::string>();
        if (j.contains("handicap")) obj.handicap = j.at("handicap").get<double>();
        if (j.contains("sortPriority")) obj.sortPriority = j.at("sortPriority").get<int>();
        if (j.contains("metadata")) obj.metadata = j.at("metadata").get<std::map<std::string, std::string>>();
    }
    

    /**************************************************************************
    * MarketDescription
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const MarketDescription& obj) {
        j["persistenceEnabled"] = obj.persistenceEnabled;
        j["bspMarket"] = obj.bspMarket;
        if(obj.marketTime) j["marketTime"] = obj.marketTime->getIsoString();
        if(obj.marketTime) j["suspendTime"] = obj.suspendTime->getIsoString();
        if(obj.settleTime) j["settleTime"] = obj.settleTime->getIsoString();
        j["bettingType"] = obj.bettingType;
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
        if(obj.lineRangeInfo) j["lineRangeInfo"] = *obj.lineRangeInfo;
        if(!obj.raceType.empty()) j["raceType"] = obj.raceType;
        if(obj.priceLadderDescription) j["priceLadderDescription"] = *obj.priceLadderDescription;
    }
    
    inline void from_json(const nlohmann::json& j, MarketDescription& obj) {
        if(j.contains("persistenceEnabled")) obj.persistenceEnabled = j.at("persistenceEnabled").get<bool>();
        if(j.contains("bspMarket")) obj.bspMarket = j.at("bspMarket").get<bool>();
        if(j.contains("marketTime")) obj.marketTime = BetfairAPI::Date(j.at("marketTime").get<std::string>());
        if(j.contains("suspendTime")) obj.suspendTime = BetfairAPI::Date(j.at("suspendTime").get<std::string>());
        if(j.contains("settleTime")) obj.settleTime = BetfairAPI::Date(j.at("settleTime").get<std::string>());
        if(j.contains("bettingType")) obj.bettingType = j.at("bettingType").get<BettingEnum::MarketBettingType>();
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
        if(j.contains("lineRangeInfo")) obj.lineRangeInfo = j.at("lineRangeInfo").get<MarketLineRangeInfo>();
        if(j.contains("raceType")) obj.raceType = j.at("raceType").get<std::string>();
        if(j.contains("priceLadderDescription")) obj.priceLadderDescription = j.at("priceLadderDescription").get<PriceLadderDescription>();
    }


    /**************************************************************************
    * MarketCatalogue
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const MarketCatalogue& obj) {
        if (!obj.marketId.empty()) j["marketId"] = obj.marketId;
        if (!obj.marketName.empty()) j["marketName"] = obj.marketName;
        if (obj.marketStartTime) j["marketStartTime"] = obj.marketStartTime->getIsoString();
        if (obj.totalMatched > 0) j["totalMatched"] = obj.totalMatched;
        if (obj.eventType) j["eventType"] = *obj.eventType;
        if (obj.competition) j["competition"] = *obj.competition;
        if (obj.description) j["description"] = *obj.description;
        if (obj.event) j["event"] = *obj.event;
        if (!obj.runners.empty()) j["runners"] = obj.runners;
    }

    inline void from_json(const nlohmann::json& j, MarketCatalogue& obj) {
        if (j.contains("marketId")) obj.marketId = j.at("marketId").get<std::string>();
        if (j.contains("marketName")) obj.marketName = j.at("marketName").get<std::string>();
        if (j.contains("marketStartTime")) obj.marketStartTime = BetfairAPI::Date(j.at("marketStartTime").get<std::string>());
        if (j.contains("totalMatched")) obj.totalMatched = j.at("totalMatched").get<double>();
        if (j.contains("eventType")) obj.eventType = j.at("eventType").get<EventType>();
        if (j.contains("competition")) obj.competition = j.at("competition").get<Competition>();
        if (j.contains("description")) obj.description = j.at("description").get<MarketDescription>();
        if (j.contains("event")) obj.event = j.at("event").get<Event>();
        if (j.contains("runners")) obj.runners = j.at("runners").get<std::vector<RunnerCatalog>>();
    }

    /**************************************************************************
    * MarketVersion
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const MarketVersion& obj) {
        j = nlohmann::json{};
        j["version"] = obj.version;
    }

    inline void from_json(const nlohmann::json& j, MarketVersion& obj) {
        if(j.contains("version")) obj.version = j.at("version").get<long>();
    }

    /**************************************************************************
    * CurrentItemDescription
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const CurrentItemDescription& obj) {
        j = nlohmann::json{};
        j["marketVersion"] = obj.marketVersion;
    }

    inline void from_json(const nlohmann::json& j, CurrentItemDescription& obj) {
        if (j.contains("marketVersion")) obj.marketVersion = j.at("marketVersion").get<MarketVersion>();
    }

    /**************************************************************************
    * PriceSize
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const PriceSize& obj) {
        j = nlohmann::json{};
        j["price"] = obj.price;
        j["size"] = obj.size;
    }

    inline void from_json(const nlohmann::json& j, PriceSize& obj) {
        if(j.contains("price")) obj.price = j.at("price").get<double>();
        if(j.contains("size")) obj.size = j.at("size").get<double>();
    }

    /**************************************************************************
    * CurrentOrderSummary
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const CurrentOrderSummary& obj) {
        j["betId"] = obj.betId;
        j["marketId"] = obj.marketId;
        j["selectionId"] = obj.selectionId;
        j["handicap"] = obj.handicap;
        j["priceSize"] = obj.priceSize;
        j["bspLiability"] = obj.bspLiability;
        j["side"] = obj.side;
        j["status"] = obj.status;
        j["persistenceType"] = obj.persistenceType;
        j["orderType"] = obj.orderType;
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
        if(obj.currentItemDescription) j["currentItemDescription"] = *obj.currentItemDescription;
        if(obj.sourceIdKey) j["sourceIdKey"] = *obj.sourceIdKey;
        if(obj.sourceIdDescription) j["sourceIdDescription"] = *obj.sourceIdDescription;
    }

    inline void from_json(const nlohmann::json& j, CurrentOrderSummary& summary) {
        if(j.contains("betId")) summary.betId = j.at("betId").get<std::string>();
        if(j.contains("marketId")) summary.marketId = j.at("marketId").get<std::string>();
        if(j.contains("selectionId")) summary.selectionId = j.at("selectionId").get<long>();
        if(j.contains("handicap")) summary.handicap = j.at("handicap").get<double>();
        if(j.contains("priceSize")) summary.priceSize = j.at("priceSize").get<PriceSize>();
        if(j.contains("bspLiability")) summary.bspLiability = j.at("bspLiability").get<double>();
        if(j.contains("side")) summary.side = j.at("side").get<BettingEnum::Side>();
        if(j.contains("status")) summary.status = j.at("status").get<BettingEnum::OrderStatus>();
        if(j.contains("persistenceType")) summary.persistenceType = j.at("persistenceType").get<BettingEnum::PersistenceType>();
        if(j.contains("orderType")) summary.orderType = j.at("orderType").get<BettingEnum::OrderType>();
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
        if(j.contains("currentItemDescription")) summary.currentItemDescription = j.at("currentItemDescription").get<CurrentItemDescription>();
        if(j.contains("sourceIdKey")) summary.sourceIdKey = j.at("sourceIdKey").get<std::string>();
        if(j.contains("sourceIdDescription")) summary.sourceIdDescription = j.at("sourceIdDescription").get<std::string>();
    }

    /**************************************************************************
    * CurrentOrderSummaryReport
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const CurrentOrderSummaryReport& obj) {
        if (!obj.currentOrders.empty()) j["currentOrders"] = obj.currentOrders;
        j["moreAvailable"] = obj.moreAvailable;
    }

    inline void from_json(const nlohmann::json& j, CurrentOrderSummaryReport& r) {
        if (j.contains("currentOrders")) r.currentOrders = j.at("currentOrders").get<std::vector<CurrentOrderSummary>>();
        if (j.contains("moreAvailable")) r.moreAvailable = j.at("moreAvailable").get<bool>();
    }

    /**************************************************************************
    * RunnerId
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const RunnerId& obj) {
        j["marketId"] = obj.marketId;
        j["selectionId"] = obj.selectionId;
        if (obj.handicap) j["handicap"] = *obj.handicap;
    }

    inline void from_json(const nlohmann::json& j, RunnerId& obj) {
        if (j.contains("marketId")) obj.marketId = j.at("marketId").get<std::string>();
        if (j.contains("selectionId")) obj.selectionId = j.at("selectionId").get<long>();
        if (j.contains("handicap")) obj.handicap = j.at("handicap").get<double>();
    }
    
    /**************************************************************************
    * ItemDescription
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const ItemDescription& obj) {
        if (obj.eventTypeDesc) j["eventTypeDesc"] = *obj.eventTypeDesc;
        if (obj.eventDesc) j["eventDesc"] = *obj.eventDesc;
        if (obj.marketDesc) j["marketDesc"] = *obj.marketDesc;
        if (obj.marketType) j["marketType"] = *obj.marketType;
        if (obj.marketStartTime) j["marketStartTime"] = obj.marketStartTime->getIsoString();
        if (obj.runnerDesc) j["runnerDesc"] = *obj.runnerDesc;
        if (obj.numberOfWinners) j["numberOfWinners"] = *obj.numberOfWinners;
        if (obj.eachWayDivisor) j["eachWayDivisor"] = *obj.eachWayDivisor;
    }

    inline void from_json(const nlohmann::json& j, ItemDescription& obj) {
        if (j.contains("eventTypeDesc")) obj.eventTypeDesc = j.at("eventTypeDesc").get<std::string>();
        if (j.contains("eventDesc")) obj.eventDesc = j.at("eventDesc").get<std::string>();
        if (j.contains("marketDesc")) obj.marketDesc = j.at("marketDesc").get<std::string>();
        if (j.contains("marketType")) obj.marketType = j.at("marketType").get<std::string>();
        if (j.contains("marketStartTime")) obj.marketStartTime = BetfairAPI::Date(j.at("marketStartTime").get<std::string>());
        if (j.contains("runnerDesc")) obj.runnerDesc = j.at("runnerDesc").get<std::string>();
        if (j.contains("numberOfWinners")) obj.numberOfWinners = j.at("numberOfWinners").get<int>();
        if (j.contains("eachWayDivisor")) obj.eachWayDivisor = j.at("eachWayDivisor").get<double>();
    }

    /**************************************************************************
    * ClearedOrderSummary
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const ClearedOrderSummary& obj) {
        if(obj.eventTypeId) j["eventTypeId"] = *obj.eventTypeId;
        if(obj.eventId) j["eventId"] = *obj.eventId;
        if(obj.marketId) j["marketId"] = *obj.marketId;
        if(obj.selectionId) j["selectionId"] = *obj.selectionId;
        if(obj.handicap) j["handicap"] = *obj.handicap;
        if(obj.betId) j["betId"] = *obj.betId;
        if(obj.placedDate) j["placedDate"] = obj.placedDate->getIsoString();
        if(obj.persistenceType) j["persistenceType"] = *obj.persistenceType;
        if(obj.orderType) j["orderType"] = *obj.orderType;
        if(obj.side) j["side"] = *obj.side;
        if(obj.itemDescription) j["itemDescription"] = *obj.itemDescription;
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
    }

    inline void from_json(const nlohmann::json& j, ClearedOrderSummary& obj) {
        if(j.contains("eventTypeId")) obj.eventTypeId = j.at("eventTypeId").get<std::string>();
        if(j.contains("eventId")) obj.eventId = j.at("eventId").get<std::string>();
        if(j.contains("marketId")) obj.marketId = j.at("marketId").get<std::string>();
        if(j.contains("selectionId")) obj.selectionId = j.at("selectionId").get<long>();
        if(j.contains("handicap")) obj.handicap = j.at("handicap").get<double>();
        if(j.contains("betId")) obj.betId = j.at("betId").get<std::string>();
        if(j.contains("placedDate")) obj.placedDate = BetfairAPI::Date(j.at("placedDate").get<std::string>());
        if(j.contains("persistenceType")) obj.persistenceType = j.at("persistenceType").get<BettingEnum::PersistenceType>();
        if(j.contains("orderType")) obj.orderType = j.at("orderType").get<BettingEnum::OrderType>();
        if(j.contains("side")) obj.side = j.at("side").get<BettingEnum::Side>();
        if(j.contains("itemDescription")) obj.itemDescription = j.at("itemDescription").get<ItemDescription>();
        if(j.contains("betOutcome")) obj.betOutcome = j.at("betOutcome").get<std::string>();
        if(j.contains("priceRequested")) obj.priceRequested = j.at("priceRequested").get<double>();
        if(j.contains("settledDate")) obj.settledDate = BetfairAPI::Date(j.at("settledDate").get<std::string>());
        if(j.contains("lastMatchedDate")) obj.lastMatchedDate = BetfairAPI::Date(j.at("lastMatchedDate").get<std::string>());
        if(j.contains("betCount")) obj.betCount = j.at("betCount").get<int>();
        if(j.contains("commission")) obj.commission = j.at("commission").get<double>();
        if(j.contains("priceMatched")) obj.priceMatched = j.at("priceMatched").get<double>();
        if(j.contains("priceReduced")) obj.priceReduced = j.at("priceReduced").get<bool>();
        if(j.contains("sizeSettled")) obj.sizeSettled = j.at("sizeSettled").get<double>();
        if(j.contains("profit")) obj.profit = j.at("profit").get<double>();
        if(j.contains("sizeCancelled")) obj.sizeCancelled = j.at("sizeCancelled").get<double>();
        if(j.contains("customerOrderRef")) obj.customerOrderRef = j.at("customerOrderRef").get<std::string>();
        if(j.contains("customerStrategyRef")) obj.customerStrategyRef = j.at("customerStrategyRef").get<std::string>();
        if(j.contains("sourceIdKey")) obj.sourceIdKey = j.at("sourceIdKey").get<std::string>();
        if(j.contains("sourceIdDescription")) obj.sourceIdDescription = j.at("sourceIdDescription").get<std::string>();
    }
    
    /**************************************************************************
    * ClearedOrderSummaryReport
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const ClearedOrderSummaryReport& obj) {
        if (!obj.clearedOrders.empty()) j["clearedOrders"] = obj.clearedOrders;
        j["moreAvailable"] = obj.moreAvailable;
    }

    inline void from_json(const nlohmann::json& j, ClearedOrderSummaryReport& obj) {
        if (j.contains("clearedOrders")) obj.clearedOrders = j.at("clearedOrders").get<std::vector<ClearedOrderSummary>>();
        if (j.contains("moreAvailable")) obj.moreAvailable = j.at("moreAvailable").get<bool>();
    }
    
    /**************************************************************************
    * LimitOrder
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const LimitOrder& obj) {
        j = nlohmann::json{};
        j["size"] = obj.size;
        j["price"] = obj.price;
        j["persistenceType"] = obj.persistenceType;

        if (obj.timeInForce) j["timeInForce"] = *obj.timeInForce;
        if (obj.minFillSize) j["minFillSize"] = *obj.minFillSize;
        if (obj.betTargetType) j["betTargetType"] = *obj.betTargetType;
        if (obj.betTargetSize) j["betTargetSize"] = *obj.betTargetSize;
    }

    inline void from_json(const nlohmann::json& j, LimitOrder& obj) {
        if (j.contains("size")) obj.size = j.at("size").get<double>();
        if (j.contains("price")) obj.price = j.at("price").get<double>();
        if (j.contains("persistenceType")) obj.persistenceType = j.at("persistenceType").get<BettingEnum::PersistenceType>();
        if (j.contains("timeInForce")) obj.timeInForce = j.at("timeInForce").get<BettingEnum::TimeInForce>();
        if (j.contains("minFillSize")) obj.minFillSize = j.at("minFillSize").get<double>();
        if (j.contains("betTargetType")) obj.betTargetType = j.at("betTargetType").get<BettingEnum::BetTargetType>();
        if (j.contains("betTargetSize")) obj.betTargetSize = j.at("betTargetSize").get<double>();
    }
    
    /**************************************************************************
    * LimitOnCloseOrder
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const LimitOnCloseOrder& obj) {
        j = nlohmann::json{};
        j["liability"] = obj.liability;
        j["price"] = obj.price;
    }

    inline void from_json(const nlohmann::json& j, LimitOnCloseOrder& obj) {
        if (j.contains("liability")) obj.liability = j.at("liability").get<double>();
        if (j.contains("price")) obj.price = j.at("price").get<double>();
    }
    
    /**************************************************************************
    * MarketOnCloseOrder
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const MarketOnCloseOrder& obj) {
        j = nlohmann::json{};
        j["liability"] = obj.liability;
    }

    inline void from_json(const nlohmann::json& j, MarketOnCloseOrder& obj) {
        if (j.contains("liability")) obj.liability = j.at("liability").get<double>();
    }
    
    /**************************************************************************
    * PlaceInstruction
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const PlaceInstruction& obj) {
        j["orderType"] = obj.orderType;
        j["selectionId"] = obj.selectionId;
        j["side"] = obj.side;

        if (obj.handicap) j["handicap"] = *obj.handicap;
        if (obj.limitOrder) j["limitOrder"] = *obj.limitOrder;
        if (obj.limitOnCloseOrder) j["limitOnCloseOrder"] = *obj.limitOnCloseOrder;
        if (obj.marketOnCloseOrder) j["marketOnCloseOrder"] = *obj.marketOnCloseOrder;
        if (obj.customerOrderRef) j["customerOrderRef"] = *obj.customerOrderRef;
    }

    inline void from_json(const nlohmann::json& j, PlaceInstruction& obj) {
        if (j.contains("orderType")) obj.orderType = j.at("orderType").get<BettingEnum::OrderType>();
        if (j.contains("selectionId")) obj.selectionId = j.at("selectionId").get<long>();
        if (j.contains("side")) obj.side = j.at("side").get<BettingEnum::Side>();
        if (j.contains("handicap")) obj.handicap = j.at("handicap").get<double>();
        if (j.contains("limitOrder")) obj.limitOrder = j.at("limitOrder").get<LimitOrder>();
        if (j.contains("limitOnCloseOrder")) obj.limitOnCloseOrder = j.at("limitOnCloseOrder").get<LimitOnCloseOrder>();
        if (j.contains("marketOnCloseOrder")) obj.marketOnCloseOrder = j.at("marketOnCloseOrder").get<MarketOnCloseOrder>();
        if (j.contains("customerOrderRef")) obj.customerOrderRef = j.at("customerOrderRef").get<std::string>();
    }
    
    /**************************************************************************
    * PlaceInstructionReport
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const PlaceInstructionReport& obj) {
        j["status"] = obj.status;
        if (obj.errorCode) j["errorCode"] = *obj.errorCode;
        if (obj.orderStatus) j["orderStatus"] = *obj.orderStatus;
        j["instruction"] = obj.instruction;
        if (obj.betId) j["betId"] = *obj.betId;
        if (obj.placedDate) j["placedDate"] = obj.placedDate->getIsoString();
        if (obj.averagePriceMatched) j["averagePriceMatched"] = *obj.averagePriceMatched;
        if (obj.sizeMatched) j["sizeMatched"] = *obj.sizeMatched;
    }

    inline void from_json(const nlohmann::json& j, PlaceInstructionReport& obj) {
        if (j.contains("status")) obj.status = j.at("status").get<BettingEnum::InstructionReportStatus>();
        if (j.contains("errorCode")) obj.errorCode = j.at("errorCode").get<BettingEnum::InstructionReportErrorCode>();
        if (j.contains("orderStatus")) obj.orderStatus = j.at("orderStatus").get<BettingEnum::OrderStatus>();
        if (j.contains("instruction")) obj.instruction = j.at("instruction").get<PlaceInstruction>();
        if (j.contains("betId")) obj.betId = j.at("betId").get<std::string>();
        if (j.contains("placedDate")) obj.placedDate = BetfairAPI::Date(j.at("placedDate").get<std::string>());
        if (j.contains("averagePriceMatched")) obj.averagePriceMatched = j.at("averagePriceMatched").get<double>();
        if (j.contains("sizeMatched")) obj.sizeMatched = j.at("sizeMatched").get<double>();
    }
    
    /**************************************************************************
    * PlaceExecutionReport
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const PlaceExecutionReport& obj) {
        j["status"] = obj.status;
        if (obj.customerRef) j["customerRef"] = *obj.customerRef;
        if (obj.errorCode) j["errorCode"] = *obj.errorCode;
        if (obj.marketId) j["marketId"] = *obj.marketId;
        if (!obj.instructionReports.empty()) j["instructionReports"] = obj.instructionReports;
    }

    inline void from_json(const nlohmann::json& j, PlaceExecutionReport& obj) {
        if (j.contains("status")) obj.status = j.at("status").get<BettingEnum::ExecutionReportStatus>();
        if (j.contains("customerRef")) obj.customerRef = j.at("customerRef").get<std::string>();
        if (j.contains("errorCode")) obj.errorCode = j.at("errorCode").get<BettingEnum::ExecutionReportErrorCode>();
        if (j.contains("marketId")) obj.marketId = j.at("marketId").get<std::string>();
        if (j.contains("instructionReports")) obj.instructionReports = j.at("instructionReports").get<std::vector<PlaceInstructionReport>>();
    }
        
    /**************************************************************************
    * CancelInstruction
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const CancelInstruction& obj) {
        j["betId"] = obj.betId;
        if (obj.sizeReduction) j["sizeReduction"] = *obj.sizeReduction;
    }

    inline void from_json(const nlohmann::json& j, CancelInstruction& obj) {
        if (j.contains("betId")) obj.betId = j.at("betId").get<std::string>();
        if (j.contains("sizeReduction")) obj.sizeReduction = j.at("sizeReduction").get<double>();
    }
    

    /**************************************************************************
    * CancelInstructionReport
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const CancelInstructionReport& obj) {
        j["status"] = obj.status;
        j["instruction"] = obj.instruction;
        j["sizeCancelled"] = obj.sizeCancelled;
        if (obj.errorCode) j["errorCode"] = *obj.errorCode;
        if (obj.cancelledDate) j["cancelledDate"] = obj.cancelledDate->getIsoString();
    }

    inline void from_json(const nlohmann::json& j, CancelInstructionReport& obj) {
        if (j.contains("status")) obj.status = j.at("status").get<BettingEnum::InstructionReportStatus>();
        if (j.contains("instruction")) obj.instruction = j.at("instruction").get<CancelInstruction>();
        if (j.contains("sizeCancelled")) obj.sizeCancelled = j.at("sizeCancelled").get<double>();
        if (j.contains("errorCode")) obj.errorCode = j.at("errorCode").get<BettingEnum::InstructionReportErrorCode>();
        if (j.contains("cancelledDate")) obj.cancelledDate = BetfairAPI::Date(j.at("cancelledDate").get<std::string>());
    }

    /**************************************************************************
    * CancelExecutionReport
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const CancelExecutionReport& obj) {
        j["status"] = obj.status;
        if (obj.errorCode) j["errorCode"] = *obj.errorCode;
        if (obj.marketId) j["marketId"] = *obj.marketId;
        if (!obj.instructionReports.empty()) j["instructionReports"] = obj.instructionReports;
    }

    inline void from_json(const nlohmann::json& j, CancelExecutionReport& obj) {
        if (j.contains("status")) obj.status = from_string<BettingEnum::ExecutionReportStatus>(j.at("status").get<std::string>());
        if (j.contains("errorCode")) obj.errorCode = from_string<BettingEnum::ExecutionReportErrorCode>(j.at("errorCode").get<std::string>());
        if (j.contains("marketId")) obj.marketId = j.at("marketId").get<std::string>();
        if (j.contains("instructionReports")) obj.instructionReports = j.at("instructionReports").get<std::vector<CancelInstructionReport>>();
    }

    /**************************************************************************
    * ReplaceInstruction
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const ReplaceInstruction& obj) {
        j["betId"] = obj.betId;
        j["newPrice"] = obj.newPrice;
    }

    inline void from_json(const nlohmann::json& j, ReplaceInstruction& obj) {
        if (j.contains("betId")) obj.betId = j.at("betId").get<std::string>();
        if (j.contains("newPrice")) obj.newPrice = j.at("newPrice").get<double>();
    }

    /**************************************************************************
    * ReplaceInstructionReport
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const ReplaceInstructionReport& obj) {
        j["status"] = obj.status;
        if (obj.errorCode) j["errorCode"] = *obj.errorCode;
        if (obj.cancelInstructionReport) j["cancelInstructionReport"] = *obj.cancelInstructionReport;
        if (obj.placeInstructionReport) j["placeInstructionReport"] = *obj.placeInstructionReport;
    }

    inline void from_json(const nlohmann::json& j, ReplaceInstructionReport& obj) {
        if (j.contains("status")) obj.status = from_string<BettingEnum::InstructionReportStatus>(j.at("status").get<std::string>());
        if (j.contains("errorCode")) obj.errorCode = from_string<BettingEnum::InstructionReportErrorCode>(j.at("errorCode").get<std::string>());
        if (j.contains("cancelInstructionReport")) obj.cancelInstructionReport = j.at("cancelInstructionReport").get<CancelInstructionReport>();
        if (j.contains("placeInstructionReport")) obj.placeInstructionReport = j.at("placeInstructionReport").get<PlaceInstructionReport>();
    }

    /**************************************************************************
    * ReplaceExecutionReport
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const ReplaceExecutionReport& obj) {
        j["status"] = obj.status;
        if (obj.customerRef) j["customerRef"] = *obj.customerRef;
        if (obj.errorCode) j["errorCode"] = *obj.errorCode;
        if (obj.marketId) j["marketId"] = *obj.marketId;
        if (!obj.instructionReports.empty()) j["instructionReports"] = obj.instructionReports;
    }

    inline void from_json(const nlohmann::json& j, ReplaceExecutionReport& obj) {
        if (j.contains("status")) obj.status = from_string<BettingEnum::ExecutionReportStatus>(j.at("status").get<std::string>());
        if (j.contains("customerRef")) obj.customerRef = j.at("customerRef").get<std::string>();
        if (j.contains("errorCode")) obj.errorCode = from_string<BettingEnum::ExecutionReportErrorCode>(j.at("errorCode").get<std::string>());
        if (j.contains("marketId")) obj.marketId = j.at("marketId").get<std::string>();
        if (j.contains("instructionReports")) obj.instructionReports = j.at("instructionReports").get<std::vector<ReplaceInstructionReport>>();
    }
    
    /**************************************************************************
    * UpdateInstruction
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const UpdateInstruction& obj) {
        j["betId"] = obj.betId;
        j["newPersistenceType"] = obj.newPersistenceType;
    }

    inline void from_json(const nlohmann::json& j, UpdateInstruction& obj) {
        if (j.contains("betId")) obj.betId = j.at("betId").get<std::string>();
        if (j.contains("newPersistenceType")) obj.newPersistenceType = from_string<BettingEnum::PersistenceType>(j.at("newPersistenceType").get<std::string>());
    }
    
    /**************************************************************************
    * UpdateInstructionReport
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const UpdateInstructionReport& obj) {
        j["status"] = obj.status;
        j["instruction"] = obj.instruction;
        if (obj.errorCode) j["errorCode"] = *obj.errorCode;
    }

    inline void from_json(const nlohmann::json& j, UpdateInstructionReport& obj) {
        if (j.contains("status")) obj.status = from_string<BettingEnum::InstructionReportStatus>(j.at("status").get<std::string>());
        if (j.contains("instruction")) obj.instruction = j.at("instruction").get<UpdateInstruction>();
        if (j.contains("errorCode")) obj.errorCode = from_string<BettingEnum::InstructionReportErrorCode>(j.at("errorCode").get<std::string>());
    }

    /**************************************************************************
    * UpdateExecutionReport
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const UpdateExecutionReport& obj) {
        j["status"] = obj.status;
        if (obj.customerRef) j["customerRef"] = *obj.customerRef;
        if (obj.errorCode) j["errorCode"] = *obj.errorCode;
        if (obj.marketId) j["marketId"] = *obj.marketId;
        if (!obj.instructionReports.empty()) j["instructionReports"] = obj.instructionReports;
    }

    inline void from_json(const nlohmann::json& j, UpdateExecutionReport& obj) {
        if (j.contains("status")) obj.status = from_string<BettingEnum::ExecutionReportStatus>(j.at("status").get<std::string>());
        if (j.contains("customerRef")) obj.customerRef = j.at("customerRef").get<std::string>();
        if (j.contains("errorCode")) obj.errorCode = from_string<BettingEnum::ExecutionReportErrorCode>(j.at("errorCode").get<std::string>());
        if (j.contains("marketId")) obj.marketId = j.at("marketId").get<std::string>();
        if (j.contains("instructionReports")) obj.instructionReports = j.at("instructionReports").get<std::vector<UpdateInstructionReport>>();
    }

    /**************************************************************************
    * OffersOverrides
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const ExBestOffersOverrides& obj) {
        if(obj.bestPricesDepth) j["bestPricesDepth"] = *obj.bestPricesDepth;
        if(obj.rollupModel) j["rollupModel"] = *obj.rollupModel;
        if(obj.rollupLimit) j["rollupLimit"] = *obj.rollupLimit;
        if(obj.rollupLiabilityThreshold) j["rollupLiabilityThreshold"] = *obj.rollupLiabilityThreshold;
        if(obj.rollupLiabilityFactor) j["rollupLiabilityFactor"] = *obj.rollupLiabilityFactor;    
    }

    inline void from_json(const nlohmann::json& j, ExBestOffersOverrides& obj) {
        if(j.contains("bestPricesDepth")) obj.bestPricesDepth = j.at("bestPricesDepth").get<int>();
        if(j.contains("rollupModel")) obj.rollupModel = j.at("rollupModel").get<BettingEnum::RollupModel>();
        if(j.contains("rollupLimit")) obj.rollupLimit = j.at("rollupLimit").get<int>();
        if(j.contains("rollupLiabilityThreshold")) obj.rollupLiabilityThreshold = j.at("rollupLiabilityThreshold").get<double>();
        if(j.contains("rollupLiabilityFactor")) obj.rollupLiabilityFactor = j.at("rollupLiabilityFactor").get<int>();
    }

    /**************************************************************************
    * PriceProjection
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const PriceProjection& obj) {
        if (!obj.priceData.empty()) j["priceData"] = obj.priceData;
        if (obj.exBestOffersOverrides) j["exBestOffersOverrides"] = *obj.exBestOffersOverrides;
        if (obj.virtualise) j["virtualise"] = *obj.virtualise;
        if (obj.rolloverStakes) j["rolloverStakes"] = *obj.rolloverStakes;
    }

    inline void from_json(const nlohmann::json& j, PriceProjection& obj) {
        if (j.contains("priceData")) obj.priceData = j.at("priceData").get<std::set<BettingEnum::PriceData>>();
        if (j.contains("exBestOffersOverrides")) obj.exBestOffersOverrides = j.at("exBestOffersOverrides").get<ExBestOffersOverrides>();
        if (j.contains("virtualise")) obj.virtualise = j.at("virtualise").get<bool>();
        if (j.contains("rolloverStakes")) obj.rolloverStakes = j.at("rolloverStakes").get<bool>();
    }

    /**************************************************************************
    * KeyLineSelection
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const KeyLineSelection& obj) {
        if(obj.selectionId) j["selectionId"] = *obj.selectionId;
        if(obj.handicap) j["handicap"] = *obj.handicap;
    }

    inline void from_json(const nlohmann::json& j, KeyLineSelection& obj) {
        if(j.contains("selectionId")) obj.selectionId = j.at("selectionId").get<long>();
        if(j.contains("handicap")) obj.handicap = j.at("handicap").get<double>();
    }

    /**************************************************************************
    * KeyLineDescription
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const KeyLineDescription& obj) {
        if (!obj.keyLine.empty()) j["keyLine"] = obj.keyLine;
    }

    inline void from_json(const nlohmann::json& j, KeyLineDescription& obj) {
        if (j.contains("keyLine")) obj.keyLine = j.at("keyLine").get<std::vector<KeyLineSelection>>();
    }

    /**************************************************************************
    * StartingPrices
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const StartingPrices& obj) {
        if (obj.nearPrice) j["nearPrice"] = *obj.nearPrice;
        if (obj.farPrice) j["farPrice"] = *obj.farPrice;
        if (!obj.backStakeTaken.empty()) j["backStakeTaken"] = obj.backStakeTaken;
        if (!obj.layLiabilityTaken.empty()) j["layLiabilityTaken"] = obj.layLiabilityTaken;
        if (obj.actualSP) j["actualSP"] = *obj.actualSP;
    }

    inline void from_json(const nlohmann::json& j, StartingPrices& obj) {
        if (j.contains("nearPrice")) obj.nearPrice = j.at("nearPrice").get<double>();
        if (j.contains("farPrice")) obj.farPrice = j.at("farPrice").get<double>();
        if (j.contains("backStakeTaken")) obj.backStakeTaken = j.at("backStakeTaken").get<std::vector<PriceSize>>();
        if (j.contains("layLiabilityTaken")) obj.layLiabilityTaken = j.at("layLiabilityTaken").get<std::vector<PriceSize>>();
        if (j.contains("actualSP")) obj.actualSP = j.at("actualSP").get<double>();
    }

    /**************************************************************************
    * ExchangePrices
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const ExchangePrices& obj) {
        if (!obj.availableToBack.empty()) j["availableToBack"] = obj.availableToBack;
        if (!obj.availableToLay.empty()) j["availableToLay"] = obj.availableToLay;
        if (!obj.tradedVolume.empty()) j["tradedVolume"] = obj.tradedVolume;
    }

    inline void from_json(const nlohmann::json& j, ExchangePrices& obj) {
        if (j.contains("availableToBack")) obj.availableToBack = j.at("availableToBack").get<std::vector<PriceSize>>();
        if (j.contains("availableToLay")) obj.availableToLay = j.at("availableToLay").get<std::vector<PriceSize>>();
        if (j.contains("tradedVolume")) obj.tradedVolume = j.at("tradedVolume").get<std::vector<PriceSize>>();
    }

    /**************************************************************************
    * Order
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const Order& obj) {
        j["betId"] = obj.betId;
        j["orderType"] = obj.orderType;
        j["status"] = obj.status;
        j["persistenceType"] = obj.persistenceType;
        j["side"] = obj.side;
        j["price"] = obj.price;
        j["size"] = obj.size;
        j["bspLiability"] = obj.bspLiability;
        if (obj.placedDate) j["placedDate"] = obj.placedDate->getIsoString();
        if (obj.avgPriceMatched) j["avgPriceMatched"] = *obj.avgPriceMatched;
        if (obj.sizeMatched) j["sizeMatched"] = *obj.sizeMatched;
        if (obj.sizeRemaining) j["sizeRemaining"] = *obj.sizeRemaining;
        if (obj.sizeLapsed) j["sizeLapsed"] = *obj.sizeLapsed;
        if (obj.sizeCancelled) j["sizeCancelled"] = *obj.sizeCancelled;
        if (obj.sizeVoided) j["sizeVoided"] = *obj.sizeVoided;
        if (obj.customerOrderRef) j["customerOrderRef"] = *obj.customerOrderRef;
        if (obj.customerStrategyRef) j["customerStrategyRef"] = *obj.customerStrategyRef;
    }

    inline void from_json(const nlohmann::json& j, Order& obj) {
        if (j.contains("betId")) obj.betId = j.at("betId").get<std::string>();
        if (j.contains("orderType")) obj.orderType = j.at("orderType").get<BettingEnum::OrderType>();
        if (j.contains("status")) obj.status = j.at("status").get<BettingEnum::OrderStatus>();
        if (j.contains("persistenceType")) obj.persistenceType = j.at("persistenceType").get<BettingEnum::PersistenceType>();
        if (j.contains("side")) obj.side = j.at("side").get<BettingEnum::Side>();
        if (j.contains("price")) obj.price = j.at("price").get<double>();
        if (j.contains("size")) obj.size = j.at("size").get<double>();
        if (j.contains("bspLiability")) obj.bspLiability = j.at("bspLiability").get<double>();
        if (j.contains("placedDate")) obj.placedDate = BetfairAPI::Date(j.at("placedDate").get<std::string>());
        if (j.contains("avgPriceMatched")) obj.avgPriceMatched = j.at("avgPriceMatched").get<double>();
        if (j.contains("sizeMatched")) obj.sizeMatched = j.at("sizeMatched").get<double>();
        if (j.contains("sizeRemaining")) obj.sizeRemaining = j.at("sizeRemaining").get<double>();
        if (j.contains("sizeLapsed")) obj.sizeLapsed = j.at("sizeLapsed").get<double>();
        if (j.contains("sizeCancelled")) obj.sizeCancelled = j.at("sizeCancelled").get<double>();
        if (j.contains("sizeVoided")) obj.sizeVoided = j.at("sizeVoided").get<double>();
        if (j.contains("customerOrderRef")) obj.customerOrderRef = j.at("customerOrderRef").get<std::string>();
        if (j.contains("customerStrategyRef")) obj.customerStrategyRef = j.at("customerStrategyRef").get<std::string>();
    }

    /**************************************************************************
    * Match
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const Match& obj) {
        if (obj.betId) j["betId"] = *obj.betId;
        if (obj.matchId) j["matchId"] = *obj.matchId;
        j["side"] = obj.side;
        j["price"] = obj.price;
        j["size"] = obj.size;
        if (obj.matchDate) j["matchDate"] = obj.matchDate->getIsoString();
    }

    inline void from_json(const nlohmann::json& j, Match& obj) {
        if (j.contains("betId")) obj.betId = j.at("betId").get<std::string>();
        if (j.contains("matchId")) obj.matchId = j.at("matchId").get<std::string>();
        if (j.contains("side")) obj.side = j.at("side").get<BettingEnum::Side>();
        if (j.contains("price")) obj.price = j.at("price").get<double>();
        if (j.contains("size")) obj.size = j.at("size").get<double>();
        if (j.contains("matchDate")) obj.matchDate = BetfairAPI::Date(j.at("matchDate").get<std::string>());
    }

    /**************************************************************************
    * Runner
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const Runner& obj) {
        j["selectionId"] = obj.selectionId;
        j["handicap"] = obj.handicap;
        j["status"] = obj.status;
        if (obj.adjustmentFactor) j["adjustmentFactor"] = *obj.adjustmentFactor;
        if (obj.lastPriceTraded) j["lastPriceTraded"] = *obj.lastPriceTraded;
        if (obj.totalMatched) j["totalMatched"] = *obj.totalMatched;
        if (obj.removalDate) j["removalDate"] = obj.removalDate->getIsoString();
        if (obj.sp) j["sp"] = *obj.sp;
        if (obj.ex) j["ex"] = *obj.ex;
        if (!obj.orders.empty()) j["orders"] = obj.orders;
        if (!obj.matches.empty()) j["matches"] = obj.matches;
        if (!obj.matchesByStrategy.empty()) j["matchesByStrategy"] = obj.matchesByStrategy;
    }

    inline void from_json(const nlohmann::json& j, Runner& obj) {
        if (j.contains("selectionId")) obj.selectionId = j.at("selectionId").get<long>();
        if (j.contains("handicap")) obj.handicap = j.at("handicap").get<double>();
        if (j.contains("status")) obj.status = j.at("status").get<BettingEnum::RunnerStatus>();
        if (j.contains("adjustmentFactor")) obj.adjustmentFactor = j.at("adjustmentFactor").get<double>();
        if (j.contains("lastPriceTraded")) obj.lastPriceTraded = j.at("lastPriceTraded").get<double>();
        if (j.contains("totalMatched")) obj.totalMatched = j.at("totalMatched").get<double>();
        if (j.contains("removalDate")) obj.removalDate = BetfairAPI::Date(j.at("removalDate").get<std::string>());
        if (j.contains("sp")) obj.sp = j.at("sp").get<StartingPrices>();
        if (j.contains("ex")) obj.ex = j.at("ex").get<ExchangePrices>();
        if (j.contains("orders")) obj.orders = j.at("orders").get<std::vector<Order>>();
        if (j.contains("matches")) obj.matches = j.at("matches").get<std::vector<Match>>();
        if (j.contains("matchesByStrategy")) {
            obj.matchesByStrategy.clear();
            for (auto& [key, value] : j.at("matchesByStrategy").items()) {
                obj.matchesByStrategy[key] = value.get<std::vector<Match>>();
            }
        }
    }

    /**************************************************************************
    * MarketBook
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const MarketBook& obj) {
        j["marketId"] = obj.marketId;
        j["isMarketDataDelayed"] = obj.isMarketDataDelayed;
        if (obj.status) j["status"] = *obj.status;
        if (obj.betDelay) j["betDelay"] = *obj.betDelay;
        if (obj.bspReconciled) j["bspReconciled"] = *obj.bspReconciled;
        if (obj.complete) j["complete"] = *obj.complete;
        if (obj.inplay) j["inplay"] = *obj.inplay;
        if (obj.numberOfWinners) j["numberOfWinners"] = *obj.numberOfWinners;
        if (obj.numberOfRunners) j["numberOfRunners"] = *obj.numberOfRunners;
        if (obj.numberOfActiveRunners) j["numberOfActiveRunners"] = *obj.numberOfActiveRunners;
        if (obj.lastMatchTime) j["lastMatchTime"] = obj.lastMatchTime->getIsoString();
        if (obj.totalMatched) j["totalMatched"] = *obj.totalMatched;
        if (obj.totalAvailable) j["totalAvailable"] = *obj.totalAvailable;
        if (obj.crossMatching) j["crossMatching"] = *obj.crossMatching;
        if (obj.runnersVoidable) j["runnersVoidable"] = *obj.runnersVoidable;
        if (obj.version) j["version"] = *obj.version;
        if (!obj.runners.empty()) j["runners"] = obj.runners;
        if (obj.keyLineDescription) j["keyLineDescription"] = *obj.keyLineDescription;
    }

    inline void from_json(const nlohmann::json& j, MarketBook& obj) {
        if (j.contains("marketId")) obj.marketId = j.at("marketId").get<std::string>();
        if (j.contains("isMarketDataDelayed")) obj.isMarketDataDelayed = j.at("isMarketDataDelayed").get<bool>();
        if (j.contains("status")) obj.status = j.at("status").get<BettingEnum::MarketStatus>();
        if (j.contains("betDelay")) obj.betDelay = j.at("betDelay").get<int>();
        if (j.contains("bspReconciled")) obj.bspReconciled = j.at("bspReconciled").get<bool>();
        if (j.contains("complete")) obj.complete = j.at("complete").get<bool>();
        if (j.contains("inplay")) obj.inplay = j.at("inplay").get<bool>();
        if (j.contains("numberOfWinners")) obj.numberOfWinners = j.at("numberOfWinners").get<int>();
        if (j.contains("numberOfRunners")) obj.numberOfRunners = j.at("numberOfRunners").get<int>();
        if (j.contains("numberOfActiveRunners")) obj.numberOfActiveRunners = j.at("numberOfActiveRunners").get<int>();
        if (j.contains("lastMatchTime")) obj.lastMatchTime = BetfairAPI::Date(j.at("lastMatchTime").get<std::string>());
        if (j.contains("totalMatched")) obj.totalMatched = j.at("totalMatched").get<double>();
        if (j.contains("totalAvailable")) obj.totalAvailable = j.at("totalAvailable").get<double>();
        if (j.contains("crossMatching")) obj.crossMatching = j.at("crossMatching").get<bool>();
        if (j.contains("runnersVoidable")) obj.runnersVoidable = j.at("runnersVoidable").get<bool>();
        if (j.contains("version")) obj.version = j.at("version").get<long>();
        if (j.contains("runners")) obj.runners = j.at("runners").get<std::vector<Runner>>();
        if (j.contains("keyLineDescription")) obj.keyLineDescription = j.at("keyLineDescription").get<KeyLineDescription>();
    }

    /**************************************************************************
    * RunnerProfitAndLoss
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const RunnerProfitAndLoss& obj) {
        if (obj.selectionId) j["selectionId"] = *obj.selectionId;
        if (obj.ifWin) j["ifWin"] = *obj.ifWin;
        if (obj.ifLose) j["ifLose"] = *obj.ifLose;
        if (obj.ifPlace) j["ifPlace"] = *obj.ifPlace;
    }

    inline void from_json(const nlohmann::json& j, RunnerProfitAndLoss& obj) {
        if (j.contains("selectionId")) obj.selectionId = j.at("selectionId").get<long>();
        if (j.contains("ifWin")) obj.ifWin = j.at("ifWin").get<double>();
        if (j.contains("ifLose")) obj.ifLose = j.at("ifLose").get<double>();
        if (j.contains("ifPlace")) obj.ifPlace = j.at("ifPlace").get<double>();
    }

    /**************************************************************************
    * MarketProfitAndLoss
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const MarketProfitAndLoss& obj) {
        if (!obj.marketId.empty()) j["marketId"] = obj.marketId;
        if(obj.commissionApplied) j["commissionApplied"] = *obj.commissionApplied;
        if (!obj.profitAndLoss.empty()) j["profitAndLoss"] = obj.profitAndLoss;
    }

    inline void from_json(const nlohmann::json& j, MarketProfitAndLoss& obj) {
        if (j.contains("marketId")) obj.marketId = j.at("marketId").get<std::string>();
        if (j.contains("commissionApplied")) obj.commissionApplied = j.at("commissionApplied").get<bool>();
        if (j.contains("profitAndLoss")) obj.profitAndLoss = j.at("profitAndLoss").get<std::vector<RunnerProfitAndLoss>>();
    }
}
