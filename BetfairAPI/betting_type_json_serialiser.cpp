#include <iostream>
#include "betting_type_json_serialiser.h"
#include "utils/enum_utils.hpp"

namespace BetfairAPI::BettingType {
    void to_json(nlohmann::json& j, const MarketFilter& mf) {
        //boolean values
        j["inPlayOnly"] = mf.isInPlayOnly();
        j["turnInPlayEnabled"] = mf.isTurnInPlayEnabled();
        j["bspOnly"] = mf.isBspOnly();

        if (const auto& query = mf.getQuery(); !query.empty()) {
            j["textQuery"] = query;
        }

        if(const auto& event_type_ids = mf.getEventTypeIds(); !event_type_ids.empty()) {
            j["eventTypeIds"] = event_type_ids;
        }

        //not sure if this is working - untested
        if(const auto& event_ids = mf.getEventIds(); !event_ids.empty()) {
            j["eventIds"] = event_ids;
        }
        
        if(const auto& comp_ids = mf.getCompetitionIds(); !comp_ids.empty()) {
            j["competitionIds"] = comp_ids;
        }

        //not sure if this is working - untested
        if(const auto& market_ids = mf.getMarketIds(); !market_ids.empty()) {
            j["marketIds"] = market_ids;
        }

        //not sure if this is working - untested
        if(const auto& venues = mf.getVenues(); !venues.empty()) {
            j["venues"] = venues;
        }

        if (const auto& mbt = mf.getMarketBettingTypes(); !mbt.empty()) {
            j["marketBettingTypes"] = Utils::to_string<BettingEnum::MarketBettingType>(mbt);
        }

        //not sure if this is working - untested
        if (const auto& market_countries = mf.getMarketCountries(); !market_countries.empty()) {
            j["marketCountries"] = market_countries;
        }

        //not sure if this is working - untested
        if (const auto& mtc = mf.getMarketTypeCodes(); !mtc.empty()) {
            j["marketTypeCodes"] = mtc;
        }

        //date???

        //not sure if this is working - untested
        if (const auto& orders = mf.getOrders(); !orders.empty()) {
            j["withOrders"] = orders;
        }

        //not sure if this is working - untested
        if (const auto& rt = mf.getRaceTypes(); !rt.empty()) {
            j["raceTypes"] = rt;
        }
    }

    void from_json(const nlohmann::json& j, EventType& etype) {
        std::string id = j.at("id").get<std::string>();
        std::string name = j.at("name").get<std::string>();
        etype = EventType(id,name);
    }

    void from_json(const nlohmann::json& j, EventTypeResults& etype) {
        EventType e = j.at("eventType").get<EventType>();
        int m_count = j.at("marketCount").get<int>();
        etype = EventTypeResults(e,m_count);
    }

    void from_json(const nlohmann::json& j, Competition& c) {
        std::string id = j.at("id").get<std::string>();
        std::string name = j.at("name").get<std::string>();
        c = Competition(id,name);
    }

    void from_json(const nlohmann::json& j, CompetitionResult& c) {
        Competition comp = j.at("competition").get<Competition>();
        std::string region = j.at("competitionRegion").get<std::string>();
        int m_count = j.at("marketCount").get<int>();
        c = CompetitionResult(comp,m_count,region);
    }

}