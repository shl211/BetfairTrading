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

        if(const auto& event_ids = mf.getEventIds(); !event_ids.empty()) {
            j["eventIds"] = event_ids;
        }
        
        if(const auto& comp_ids = mf.getCompetitionIds(); !comp_ids.empty()) {
            j["competitionIds"] = comp_ids;
        }

        //not sure if this is working
        if(const auto& market_ids = mf.getMarketIds(); !market_ids.empty()) {
            j["marketIds"] = market_ids;
        }

        if(const auto& venues = mf.getVenues(); !venues.empty()) {
            j["venues"] = venues;
        }

        if (const auto& mbt = mf.getMarketBettingTypes(); !mbt.empty()) {
            j["marketBettingTypes"] = Utils::to_string<BettingEnum::MarketBettingType>(mbt);
        }

        if (const auto& market_countries = mf.getMarketCountries(); !market_countries.empty()) {
            j["marketCountries"] = market_countries;
        }

        if (const auto& mtc = mf.getMarketTypeCodes(); !mtc.empty()) {
            j["marketTypeCodes"] = mtc;
        }

        if (const auto& mst = mf.getMarketStartTime(); mst.getFromDate().isValid() || mst.getToDate().isValid()) {
            j["marketStartTime"] = mst;
        }

        //not sure if this is working - untested
        if (const auto& orders = mf.getOrders(); !orders.empty()) {
            j["withOrders"] = Utils::to_string<BettingEnum::OrderStatus>(orders);
        }

        //not sure if this is working - untested
        if (const auto& rt = mf.getRaceTypes(); !rt.empty()) {
            j["raceTypes"] = rt;
        }
    }

    void to_json(nlohmann::json& j, const TimeRange& t) {
        j["from"] = t.getFromDate().toIsoString();
        j["to"] = t.getToDate().toIsoString();
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

    void from_json(const nlohmann::json& j, Event& e) {
        std::string id = j.at("id").get<std::string>();
        std::string name = j.at("name").get<std::string>();
        std::string country_code = j.contains("countryCode") ? j.at("countryCode").get<std::string>() : "";
        std::string tz = j.at("timezone").get<std::string>();
        std::string venue = j.contains("venue") ? j.at("venue").get<std::string>() : "";
        BetfairAPI::Utils::Date date = BetfairAPI::Utils::Date(j.at("openDate").get<std::string>());
        e = Event(id, name, country_code, tz, venue, date);
    }

    void from_json(const nlohmann::json& j, EventResult& e) {
        BetfairAPI::BettingType::Event event = j.at("event").get<BetfairAPI::BettingType::Event>();
        int m_count = j.at("marketCount").get<int>();
        e = BetfairAPI::BettingType::EventResult(event,m_count);
    }

    void from_json(const nlohmann::json& j, MarketTypeResult& mt) {
        std::string m_type = j.at("marketType").get<std::string>();
        int m_count = j.at("marketCount").get<int>();
        mt = BetfairAPI::BettingType::MarketTypeResult(m_type,m_count);
    }

    void from_json(const nlohmann::json& j, TimeRange& t) {
        auto from = BetfairAPI::Utils::Date(j.at("from").get<std::string>());
        auto to = BetfairAPI::Utils::Date(j.at("to").get<std::string>());
        t = TimeRange(from,to);
    }

    void from_json(const nlohmann::json& j, TimeRangeResult& t) {
        auto time_range = j.at("timeRange").get<TimeRange>();
        int m_count = j.at("marketCount").get<int>();
        t = TimeRangeResult(time_range,m_count);
    }

    void from_json(const nlohmann::json& j, CountryCodeResult& t) {
        std::string country_code = j.at("countryCode").get<std::string>();
        int m_count = j.at("marketCount").get<int>();
        t = CountryCodeResult(country_code,m_count);
    }

    void from_json(const nlohmann::json& j, VenueResult& v) {
        std::string venue = j.at("venue").get<std::string>();
        int m_count = j.at("marketCount").get<int>();
        v = VenueResult(venue,m_count);
    }

    void from_json(const nlohmann::json& j, MarketCatalogue& m) {
        //mandatory
        std::string m_id = j.at("marketId").get<std::string>();
        std::string m_name = j.at("marketName").get<std::string>();

        //optional
        Utils::Date start_time;
        if(j.contains("marketStartTime")) {
            start_time = Utils::Date(j.at("marketStartTime").get<std::string>());
        }

        MarketDescription m_desc;
        if(j.contains("marketDescription")) {
            m_desc = j.at("marketDescription").get<MarketDescription>();
        }

        double tot_matched = 0;
        if(j.contains("totalMatched")) {
            tot_matched = j.at("totalMatched").get<double>();
        }

        std::vector<RunnerCatalog> r_list {};
        if(j.contains("runners")) {
            r_list.reserve(j.at("totalMatched").size());
            for(auto& r : j.at("totalMatched")) {
                r_list.push_back(r.get<RunnerCatalog>());
            }
        }

        EventType e_type;
        if(j.contains("eventType")) {
            e_type = j.at("eventType").get<EventType>();
        }

        Competition comp;
        if(j.contains("competition")) {
            comp = j.at("competition").get<Competition>();
        }

        Event e;
        if (j.contains("event")) {
            e = j.at("event").get<Event>();
        }

        //construct
        m = MarketCatalogue(m_id,m_name,start_time,m_desc,tot_matched,
            r_list,e_type,comp,e);
    }

    void from_json(const nlohmann::json& j, MarketLineRangeInfo& m) {
        double max_v = j.at("maxUnitValue").get<double>();
        double min_v = j.at("minUnitValue").get<double>();
        double interval = j.at("interval").get<double>();
        std::string m_unit = j.at("marketUnit").get<std::string>();
        m = MarketLineRangeInfo(max_v,min_v,interval,m_unit);
    }

    void from_json(const nlohmann::json& j, PriceLadderDescription& p) {
        auto t = Utils::from_string<BettingEnum::PriceLadderType>(j.at("type").get<std::string>());
        p = PriceLadderDescription(t);
    }

    void from_json(const nlohmann::json& j, MarketDescription& p) {
        //these are mandatory returns
        p.setPersistenceEnabled(j.at("persistenceEnabled").get<bool>());
        p.setBspMarket(j.at("bspMarket").get<bool>());
        p.setMarketTime(Utils::Date(j.at("marketTime").get<std::string>()));
        p.setSuspendTime(Utils::Date(j.at("suspendTime").get<std::string>()));
        p.setSettleTime(Utils::Date(j.at("settleTime").get<std::string>()));
        p.setBettingType(
            Utils::from_string<BettingEnum::MarketBettingType>(
                j.at("bettingType").get<std::string>()
            ));
        p.setTurnInPlayEnabled(j.at("turnInPlayEnabled").get<bool>());
        p.setMarketType(j.at("marketType").get<std::string>());
        p.setRegulator(j.at("regulator").get<std::string>());
        p.setMarketBaseRate(j.at("marketBaseRate").get<double>());
        p.setDiscountAllowed(j.at("discountAllowed").get<bool>());

        //optional
        if(j.contains("wallet")) {
            p.setWallet(j.at("wallet").get<std::string>());
        }

        if(j.contains("rules")) {
            p.setRules(j.at("rules").get<std::string>());
        }

        if(j.contains("rulesHasDates")) {
            p.setRulesHasDates(j.at("rulesHasDates").get<bool>());
        }

        if(j.contains("eachWayDivisor")) {
            p.setEachWayDivisor(j.at("eachWayDivisor").get<double>());
        }

        if(j.contains("clarifications")) {
            p.setClarifications(j.at("clarifications").get<std::string>());
        }

        if(j.contains("lineRangeInfo")) {
            p.setLineRangeInfo(j.at("lineRangeInfo").get<MarketLineRangeInfo>());
        }

        if(j.contains("raceType")) {
            p.setRaceType(j.at("raceType").get<std::string>());
        }

        if(j.contains("priceLadderDescription")) {
            p.setPriceLadderDescription(j.at("priceLadderDescription").get<PriceLadderDescription>());
        }
    }

    void from_json(const nlohmann::json& j, RunnerCatalog& r) {
        //mandatory
        long selection_id = j.at("selectionId").get<long>();
        std::string name = j.at("runnerName").get<std::string>();
        double h  = j.at("handicap").get<double>();
        int s = j.at("sortPriority").get<int>();

        //optional
        std::map<std::string,std::string> m{};
        if (j.contains("metadata")) {
            m = j.at("metadata").get<std::map<std::string,std::string>>();
        }

        r = RunnerCatalog(selection_id,name,h,s,m);
    }


}
