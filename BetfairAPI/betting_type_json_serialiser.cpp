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

    void from_json(const nlohmann::json& j, MarketBook& r) {
        std::string m_id = j.at("marketId").get<std::string>();
        bool is_m_delayed = j.at("isMarketDataDelayed").get<bool>();
        r = MarketBook(m_id,is_m_delayed);

        //now for optional
        if(j.contains("status")) {
            r.setStatus(Utils::from_string<BettingEnum::MarketStatus>(j.at("status").get<std::string>()));
        }

        if(j.contains("betDelay")) {
            r.setBetDelay(j.at("betDelay").get<int>());
        }

        if(j.contains("bspReconciled")) {
            r.setBspReconciled(j.at("bspReconciled").get<bool>());
        }

        if(j.contains("complete")) {
            r.setComplete(j.at("complete").get<bool>());
        }

        if(j.contains("inplay")) {
            r.setInplay(j.at("inplay").get<bool>());
        }

        if(j.contains("numberOfWinners")) {
            r.setNumberOfWinners(j.at("numberOfWinners").get<int>());
        }

        if(j.contains("numberOfRunners")) {
            r.setNumberOfRunners(j.at("numberOfRunners").get<int>());
        }

        if(j.contains("numberOfActiveRunners")) {
            r.setNumberOfActiveRunners(j.at("numberOfActiveRunners").get<int>());
        }

        if(j.contains("lastMatchTime")) {
            r.setLastMatchTime(Utils::Date(j.at("lastMatchTime").get<std::string>()));
        }

        if(j.contains("totalMatched")) {
            r.setTotalMatched(j.at("totalMatched").get<double>());
        }

        if(j.contains("totalAvailable")) {
            r.setTotalAvailable(j.at("totalAvailable").get<double>());
        }

        if(j.contains("crossMatching")) {
            r.setCrossMatching(j.at("crossMatching").get<bool>());
        }

        if(j.contains("runnersVoidable")) {
            r.setRunnersVoidable(j.at("runnersVoidable").get<bool>());
        }

        if(j.contains("version")) {
            r.setVersion(j.at("version").get<long>());
        }

        if(j.contains("runners")) {
            for(auto& runner : j.at("runners")) {
                r.addRunners(runner.get<Runner>());
            }
        }

        if(j.contains("keyLineDescription")) {
            r.setKeyLineDescription(j.at("keyLineDescription").get<KeyLineDescription>());
        }
    }

    void to_json(nlohmann::json& j, const MarketBook& mbook) {
        j["marketId"] = mbook.getMarketId();
        j["isMarketDataDelayed"] = mbook.isMarketDataDelayed();

        j["bspReconciled"] = mbook.isBspReconciled();
        j["complete"] = mbook.isComplete();
        j["inplay"] = mbook.isInplay();

        // optional
        if (auto obj = mbook.getStatus(); obj != BettingEnum::MarketStatus::UNKNOWN) {
            j["status"] = Utils::to_string<BettingEnum::MarketStatus>(obj);
        }

        if (int obj = mbook.getBetDelay(); obj >= 0) {
            j["betDelay"] = obj;
        }

        if (int obj = mbook.getNumberOfWinners(); obj >= 0) {
            j["numberOfWinners"] = obj;
        }

        if (int obj = mbook.getNumberOfRunners(); obj >= 0) {
            j["numberOfRunners"] = obj;
        }

        if (int obj = mbook.getNumberOfActiveRunners(); obj >= 0) {
            j["numberOfActiveRunners"] = obj;
        }

        if (auto date = mbook.getLastMatchTime(); date.isValid()) {
            j["lastMatchTime"] = date.toIsoString();
        }

        if (double obj = mbook.getTotalMatched(); obj >= 0) {
            j["totalMatched"] = obj;
        }

        if (double obj = mbook.getTotalAvailable(); obj >= 0) {
            j["totalAvailable"] = obj;
        }

        j["crossMatching"] = mbook.isCrossMatching();
        j["runnersVoidable"] = mbook.isRunnersVoidable();

        if (long obj = mbook.getVersion(); obj >= 0) {
            j["version"] = obj;
        }

        const auto& runners = mbook.getRunners();
        if (!runners.empty()) {
            j["runners"] = runners;
        }

        j["keyLineDescription"] = mbook.getKeyLineDescription();
    }


    void from_json(const nlohmann::json& j, Runner& r) {
        long s_id = j.at("selectionId").get<long>();
        double handicap = j.at("handicap").get<double>();
        auto status = Utils::from_string<BettingEnum::RunnerStatus>(
            j.at("status").get<std::string>()
        );

        r = Runner(s_id,handicap,status);

        //optional
        if(j.contains("adjustmentFactor")) {
            r.setAdjustmentFactor(j.at("adjustmentFactor").get<double>());
        }

        if(j.contains("lastPriceTraded")) {
            r.setLastPriceTraded(j.at("lastPriceTraded").get<double>());
        }

        if(j.contains("totalMatched")) {
            r.setTotalMatched(j.at("totalMatched").get<double>());
        }

        if(j.contains("removalDate")) {
            r.setRemovalDate(Utils::Date(j.at("removalDate").get<std::string>()));
        }

        if(j.contains("sp")) {
            r.setStartingPrices(j.at("sp").get<StartingPrices>());
        }

        if(j.contains("ex")) {
            r.setExchangePrices(j.at("ex").get<ExchangePrices>());
        }

        if(j.contains("orders")) {
            for(auto& i : j.at("orders")){
                r.addOrder(i.get<Order>());
            }
        }

        if(j.contains("matches")) {
            for(auto& i : j.at("matches")){
                r.addMatch(i.get<Match>());
            }
        }

        if(j.contains("matchesByStrategy")) {
            for (auto& [key, value] : j.at("matchesByStrategy").items()) {
            r.addMatchByStrategy(key, value.get<Match>());
            }
        }
    }

    void to_json(nlohmann::json& j, const Runner& k) {
        j["selectionId"] = k.getSelectionId();
        j["handicap"] = k.getHandicap();
        j["status"] = Utils::to_string<BettingEnum::RunnerStatus>(k.getStatus());

        if (k.getAdjustmentFactor() >= 0) {
            j["adjustmentFactor"] = k.getAdjustmentFactor();
        }
        if (k.getLastPriceTraded() >= 0) {
            j["lastPriceTraded"] = k.getLastPriceTraded();
        }
        if (k.getTotalMatched() >= 0) {
            j["totalMatched"] = k.getTotalMatched();
        }
        if (auto date = k.getRemovalDate(); date.isValid()) {
            j["removalDate"] = date.toIsoString();
        }

        j["sp"] = k.getStartingPrices();
        j["ex"] = k.getExchangePrices();

        const auto& orders = k.getOrders();
        if (!orders.empty()) {
            j["orders"] = orders;
        }
        const auto& matches = k.getMatches();
        if (!matches.empty()) {
            j["matches"] = matches;
        }
        const auto& matchesByStrategy = k.getMatchesByStrategy();
        if (!matchesByStrategy.empty()) {
            nlohmann::json mbs_json = nlohmann::json::object();
            for (const auto& [key, value] : matchesByStrategy) {
                mbs_json[key] = value;
            }
            j["matchesByStrategy"] = mbs_json;
        }
    }


    void from_json(const nlohmann::json& j, KeyLineSelection& k) {
        long s_id = j.at("selectionId").get<long>();
        double h = j.at("handicap").get<double>();
        k = KeyLineSelection(s_id,h);
    }

    void to_json(nlohmann::json& j, const KeyLineSelection& k) {
        j["selectionId"] = k.getSelectionId();
        j["handicap"] = k.getHandicap();
    }

    void from_json(const nlohmann::json& j, KeyLineDescription& k) {
        std::vector<KeyLineSelection> k_list;
        k_list.reserve(j.at("keyLine").size());
        for(auto& i : j.at("keyLine")) {
            k_list.push_back(i.get<KeyLineSelection>());
        }
        k = KeyLineDescription(k_list);
    }

    void to_json(nlohmann::json& j, const KeyLineDescription& k) {
        j["keyLine"] = nlohmann::json::array();
        for (const auto& i : k.getKeyLine()) {
            j["keyLine"].push_back(i);
        }
    }

    void from_json(const nlohmann::json& j, PriceSize& ps) {
        double p = j.at("price").get<double>();
        double s = j.at("size").get<double>();
        ps = PriceSize(p,s);
    }

    void to_json(nlohmann::json& j, const PriceSize& ps) {
        j["price"] = ps.getPrice();
        j["size"] = ps.getSize();
    }

    void from_json(const nlohmann::json& j, StartingPrices& sp) {
        double near_p = j.at("nearPrice").get<double>();
        double far_p = j.at("farPrice").get<double>();
        double actual_sp = j.at("actualSP").get<double>();
        
        std::vector<PriceSize> b_taken;
        b_taken.reserve(j.at("backStakeTaken").size());
        for(auto& i : j.at("backStakeTaken")) {
            b_taken.push_back(i.get<PriceSize>());
        }
        
        std::vector<PriceSize> l_taken;
        l_taken.reserve(j.at("layLiabilityTaken").size());
        for(auto& i : j.at("layLiabilityTaken")) {
            l_taken.push_back(i.get<PriceSize>());
        }

        sp = StartingPrices(near_p,far_p,actual_sp,b_taken,l_taken);
    }

    void to_json(nlohmann::json& j, const StartingPrices& sp) {
        j["nearPrice"] = sp.getNearPrice();
        j["farPrice"] = sp.getFarPrice();
        j["actualSP"] = sp.getActualSP();
        j["backStakeTaken"] = sp.getBackStakeTaken();
        j["layLiabilityTaken"] = sp.getLayLiabilityTaken();
    }

    void from_json(const nlohmann::json& j, ExchangePrices& ep) {
        std::vector<PriceSize> b;
        b.reserve(j.at("availableToBack").size());
        for(auto& i : j.at("availableToBack")) {
            b.push_back(i.get<PriceSize>());
        }

        std::vector<PriceSize> l;
        l.reserve(j.at("availableToLay").size());
        for(auto& i : j.at("availableToLay")) {
            l.push_back(i.get<PriceSize>());
        }

        std::vector<PriceSize> t;
        t.reserve(j.at("tradedVolume").size());
        for(auto& i : j.at("tradedVolume")) {
            t.push_back(i.get<PriceSize>());
        }

        ep = ExchangePrices(b,l,t);
    }

    void to_json(nlohmann::json& j, const ExchangePrices& ep) {
        j["availableToBack"] = ep.getAvailableToBack();
        j["availableToLay"] = ep.getAvailableToLay();
        j["tradedVolume"] = ep.getTradedVolume();
    }

    void from_json(const nlohmann::json& j, Match& m) {
        BettingEnum::Side side = Utils::from_string<BettingEnum::Side>(
            j.at("side").get<std::string>()
        );
        double p = j.at("price").get<double>();
        double sz = j.at("size").get<double>();

        //optional
        std::string b_id = (j.contains("betId")) ? j.at("betId").get<std::string>() : "";
        std::string m_id = (j.contains("matchId")) ? j.at("matchId").get<std::string>() : "";
        Utils::Date m_date = (j.contains("matchDate")) ? Utils::Date(j.at("matchDate").get<std::string>()) : Utils::Date();

        m = Match(side,p,sz,b_id,m_id,m_date);
    }

    void to_json(nlohmann::json& j, const Match& m) {
        j["side"] = Utils::to_string<BettingEnum::Side>(m.getSide());
        j["price"] = m.getPrice();
        j["size"] = m.getSize();
        
        if(auto obj = m.getBetId(); !obj.empty()) {
            j["betId"] = obj;
        }

        if(auto obj = m.getMatchId(); !obj.empty()) {
            j["matchId"] = obj;
        }

        if(auto date = m.getMatchDate(); date.isValid()) {
            j["matchDate"] = date.toIsoString();
        }
    }

    void from_json(const nlohmann::json& j, Order& o) {
        OrderParams op;
        op.bet_id = j.at("betId").get<std::string>();
        op.order_type = Utils::from_string<BettingEnum::OrderType>(j.at("orderType").get<std::string>());
        op.order_status = Utils::from_string<BettingEnum::OrderStatus>(j.at("orderStatus").get<std::string>());
        op.persistence_type = Utils::from_string<BettingEnum::PersistenceType>(j.at("persistenceType").get<std::string>());
        op.side = Utils::from_string<BettingEnum::Side>(j.at("side").get<std::string>());
        op.price = j.at("price").get<double>();
        op.size = j.at("size").get<double>();
        op.bsp_liability = j.at("bspLiability").get<double>();
        op.placed_date = Utils::Date(j.at("placedDate").get<std::string>());
        
        //optional
        double EMPTY{-1};
        op.avg_price_matched = (j.contains("avgPriceMatched")) ? j.at("avgPriceMatched").get<double>() : EMPTY;
        op.size_matched = (j.contains("sizeMatched")) ? j.at("sizeMatched").get<double>() : EMPTY;
        op.size_remaining = (j.contains("sizeRemaining")) ? j.at("sizeRemaining").get<double>() : EMPTY;
        op.size_lapsed = (j.contains("sizeLapsed")) ? j.at("sizeLapsed").get<double>() : EMPTY;
        op.size_cancelled = (j.contains("sizeCancelled")) ? j.at("sizeCancelled").get<double>() : EMPTY;
        op.size_voided = (j.contains("sizeVoided")) ? j.at("sizeVoided").get<double>() : EMPTY;
        op.customer_order_ref = (j.contains("customerOrderRef")) ? j.at("customerOrderRef").get<std::string>() : "";
        op.customer_strategy_ref = (j.contains("customerStrategyRef")) ? j.at("customerStrategyRef").get<std::string>() : "";

        o = Order(op);
    }

    void to_json(nlohmann::json& j, const Order& k) {
        j["betId"] = k.getBetId();
        j["orderType"] = Utils::to_string<BettingEnum::OrderType>(k.getOrderType());
        j["orderStatus"] = Utils::to_string<BettingEnum::OrderStatus>(k.getOrderStatus());
        j["persistenceType"] = Utils::to_string<BettingEnum::PersistenceType>(k.getPersistenceType());
        j["side"] = Utils::to_string<BettingEnum::Side>(k.getSide());
        j["price"] = k.getPrice();
        j["size"] = k.getSize();
        j["bspLiability"] = k.getBspLiability();
        j["placedDate"] = k.getPlacedDate().toIsoString();

        if (k.getAvgPriceMatched() >= 0) {
            j["avgPriceMatched"] = k.getAvgPriceMatched();
        }
        if (k.getSizeMatched() >= 0) {
            j["sizeMatched"] = k.getSizeMatched();
        }
        if (k.getSizeRemaining() >= 0) {
            j["sizeRemaining"] = k.getSizeRemaining();
        }
        if (k.getSizeLapsed() >= 0) {
            j["sizeLapsed"] = k.getSizeLapsed();
        }
        if (k.getSizeCancelled() >= 0) {
            j["sizeCancelled"] = k.getSizeCancelled();
        }
        if (k.getSizeVoided() >= 0) {
            j["sizeVoided"] = k.getSizeVoided();
        }
        if (!k.getCustomerOrderRef().empty()) {
            j["customerOrderRef"] = k.getCustomerOrderRef();
        }
        if (!k.getCustomerStrategyRef().empty()) {
            j["customerStrategyRef"] = k.getCustomerStrategyRef();
        }
    }

    void from_json(const nlohmann::json& j, MarketProfitLoss& m_pl) {
        std::string m_id = j.at("marketId").get<std::string>();
        
        double commision = (j.contains("commissionApplied")) ? j.at("commissionApplied").get<double>() : -1;
        std::vector<RunnerProfitLoss> r_pl;
        for(auto& i : j.at("profitAndLosses")) {
            r_pl.push_back(i.get<RunnerProfitLoss>());
        }
        
        m_pl = MarketProfitLoss(m_id,commision,r_pl);
    }

    void from_json(const nlohmann::json& j, RunnerProfitLoss& r_pl) {
        long s = j.at("selectionId").get<long>();
        double if_win = j.at("ifWin").get<double>();
        double if_lose = j.contains("ifLose") ? j.at("ifLose").get<double>() : 0;
        double if_place = j.contains("ifPlace") ? j.at("ifPlace").get<double>() : 0;

        r_pl = RunnerProfitLoss(s,if_win,if_lose,if_place);
    }

    void from_json(const nlohmann::json& j, CurrentOrderSummaryReport& k) {
        bool more = j.at("moreAvailable").get<bool>();
        
        std::vector<CurrentOrderSummary> summary = {};
        summary.reserve(j.at("currentOrders").size());

        for(auto& i : j.at("currentOrders")) {
            summary.push_back(i.get<CurrentOrderSummary>());
        }

        k = CurrentOrderSummaryReport(summary,more);
    }

    void to_json(nlohmann::json& j, const CurrentOrderSummaryReport& k) {
        j["moreAvailable"] = k.isMoreAvailable();
        j["currentOrders"] = nlohmann::json::array();

        for(auto& i : k.getCurrentOrders()) {
            j["currentOrders"].push_back(i);
        }
    }

    void from_json(const nlohmann::json& j, CurrentOrderSummary& k) {
        
        k = CurrentOrderSummary(
            j["betId"].get<std::string>(),
            j["marketId"].get<std::string>(),
            j["selectionId"].get<long>(),
            j["handicap"].get<double>(),
            j["priceSize"].get<PriceSize>(),
            j["bspLiability"].get<double>(),
            Utils::from_string<BettingEnum::Side>(j["side"].get<std::string>()),
            Utils::from_string<BettingEnum::OrderStatus>(j["status"].get<std::string>()),
            Utils::from_string<BettingEnum::PersistenceType>(j["persistenceType"].get<std::string>()),
            Utils::from_string<BettingEnum::OrderType>(j["orderType"].get<std::string>()),
            Utils::Date(j["placedDate"].get<std::string>()),
            Utils::Date(j["matchedDate"].get<std::string>())
        );
        
        //optional
        if(j.contains("averagePriceMatched")) {
            k.setAveragePriceMatched(j.at("averagePriceMatched").get<double>());
        }

        if(j.contains("sizeMatched")) {
            k.setSizeMatched(j.at("sizeMatched").get<double>());
        }

        if(j.contains("sizeRemaining")) {
            k.setSizeRemaining(j.at("sizeRemaining").get<double>());
        }

        if(j.contains("sizeLapsed")) {
            k.setSizeLapsed(j.at("sizeLapsed").get<double>());
        }
        
        if(j.contains("sizeCancelled")) {
            k.setSizeCancelled(j.at("sizeCancelled").get<double>());
        }
        
        if(j.contains("sizeVoided")) {
            k.setSizeVoided(j.at("sizeVoided").get<double>());
        }

        if(j.contains("regulatorAuthCode")) {
            k.setRegulatorAuthCode(j.at("regulatorAuthCode").get<std::string>());
        }

        if(j.contains("regulatorCode")) {
            k.setRegulatorCode(j.at("regulatorCode").get<std::string>());
        }

        if(j.contains("customerOrderRef")) {
            k.setCustomerOrderRef(j.at("customerOrderRef").get<std::string>());
        }

        if(j.contains("customerStrategyRef")) {
            k.setCustomerStrategyRef(j.at("customerStrategyRef").get<std::string>());
        }
        
        if(j.contains("currentItemDescription")) {
            k.setCurrentItemDescription(j.at("currentItemDescription").get<CurrentItemDescription>());
        }
        
        if(j.contains("sourceIdKey")) {
            k.setSourceIdKey(j.at("sourceIdKey").get<std::string>());
        }
        
        if(j.contains("sourceIdDescription")) {
            k.setSourceIdDescription(j.at("sourceIdDescription").get<std::string>());
        }
    }

    void to_json(nlohmann::json& j, const CurrentOrderSummary& k) {
        j["betId"] = k.getBetId();
        j["marketId"] = k.getMarketId();
        j["selectionId"] = k.getSelectionId();
        j["handicap"] = k.getHandicap();
        j["priceSize"] = k.getPriceSize();
        j["bspLiability"] = k.getBspLiability();
        j["side"] = Utils::to_string<BettingEnum::Side>(k.getSide());
        j["status"] = Utils::to_string<BettingEnum::OrderStatus>(k.getStatus());
        j["persistenceType"] = Utils::to_string<BettingEnum::PersistenceType>(k.getPersistenceType());
        j["orderType"] = Utils::to_string<BettingEnum::OrderType>(k.getOrderType());
        j["placedDate"] = k.getPlacedDate().toIsoString();
        j["matchedDate"] = k.getMatchedDate().toIsoString();

        if (k.getAveragePriceMatched() >= 0) {
            j["averagePriceMatched"] = k.getAveragePriceMatched();
        }
        if (k.getSizeMatched() >= 0) {
            j["sizeMatched"] = k.getSizeMatched();
        }
        if (k.getSizeRemaining() >= 0) {
            j["sizeRemaining"] = k.getSizeRemaining();
        }
        if (k.getSizeLapsed() >= 0) {
            j["sizeLapsed"] = k.getSizeLapsed();
        }
        if (k.getSizeCancelled() >= 0) {
            j["sizeCancelled"] = k.getSizeCancelled();
        }
        if (k.getSizeVoided() >= 0) {
            j["sizeVoided"] = k.getSizeVoided();
        }
        if (!k.getRegulatorAuthCode().empty()) {
            j["regulatorAuthCode"] = k.getRegulatorAuthCode();
        }
        if (!k.getRegulatorCode().empty()) {
            j["regulatorCode"] = k.getRegulatorCode();
        }
        if (!k.getCustomerOrderRef().empty()) {
            j["customerOrderRef"] = k.getCustomerOrderRef();
        }
        if (!k.getCustomerStrategyRef().empty()) {
            j["customerStrategyRef"] = k.getCustomerStrategyRef();
        }
        if (k.getCurrentItemDescription().getMarketVersion().getVersion() != 0) {
            j["currentItemDescription"] = k.getCurrentItemDescription();
        }
        if (!k.getSourceIdKey().empty()) {
            j["sourceIdKey"] = k.getSourceIdKey();
        }
        if (!k.getSourceIdDescription().empty()) {
            j["sourceIdDescription"] = k.getSourceIdDescription();
        }
    }

    void from_json(const nlohmann::json& j, CurrentItemDescription& k) {
        k = CurrentItemDescription(j.at("marketVersion").get<MarketVersion>());
    }

    void to_json(nlohmann::json& j, const CurrentItemDescription& k) {
        j["marketVersion"] = k.getMarketVersion();
    }

    void from_json(const nlohmann::json& j, MarketVersion& k) {
        k = MarketVersion(j.at("version").get<long>());
    }

    void to_json(nlohmann::json& j, const MarketVersion& k) {
        j["version"] = k.getVersion();
    }

    void from_json(const nlohmann::json& j, ClearedOrderSummaryReport& r) {
        bool more = j.at("moreAvailable").get<bool>();
        
        std::vector<ClearedOrderSummary> summary = {};
        summary.reserve(j.at("clearedOrders").size());

        for(auto& i : j.at("clearedOrders")) {
            summary.push_back(i.get<ClearedOrderSummary>());
        }

        r = ClearedOrderSummaryReport(summary,more);
    }

    void to_json(nlohmann::json& j, const ClearedOrderSummaryReport& k) {
        j["moreAvailable"] = k.isMoreAvailable();
        j["clearedOrders"] = nlohmann::json::array();

        for(auto& i : k.getClearedOrders()) {
            j["clearedOrders"].push_back(i);
        }
    }

    void from_json(const nlohmann::json& j, ClearedOrderSummary& r) {
        if(j.contains("eventTypeId")) {
            r.setEventTypeId(j.at("eventTypeId").get<std::string>());
        }

        if(j.contains("eventId")) {
            r.setEventId(j.at("eventId").get<std::string>());
        }

        if(j.contains("marketId")) {
            r.setMarketId(j.at("marketId").get<std::string>());
        }

        if(j.contains("selectionId")) {
            r.setSelectionId(j.at("selectionId").get<long>());
        }

        if(j.contains("handicap")) {
            r.setHandicap(j.at("handicap").get<double>());
        }

        if(j.contains("betId")) {
            r.setBetId(j.at("betId").get<std::string>());
        }

        if(j.contains("placedDate")) {
            r.setPlacedDate(Utils::Date(j.at("placedDate").get<std::string>()));
        }
        
        if(j.contains("persistenceType")) {
            r.setPersistenceType(Utils::from_string<BettingEnum::PersistenceType>(
                j.at("persistenceType").get<std::string>()
            ));
        }
        
        if(j.contains("orderType")) {
            r.setOrderType(Utils::from_string<BettingEnum::OrderType>(
                j.at("orderType").get<std::string>()
            ));
        }
        
        if(j.contains("side")) {
            r.setSide(Utils::from_string<BettingEnum::Side>(
                j.at("side").get<std::string>()
            ));
        }
        
        if(j.contains("itemDescription")) {
            r.setItemDescription(j.at("itemDescription").get<ItemDescription>());
        }
        
        if(j.contains("betOutcome")) {
            r.setBetOutcome(j.at("betOutcome").get<std::string>());
        }
        
        if(j.contains("priceRequested")) {
            r.setPriceRequested(j.at("priceRequested").get<double>());
        }
        
        if(j.contains("settledDate")) {
            r.setSettledDate(Utils::Date(j.at("settledDate").get<std::string>()));
        }

        if(j.contains("lastMatchedDate")) {
            r.setLastMatchedDate(Utils::Date(j.at("lastMatchedDate").get<std::string>()));
        }

        if(j.contains("betCount")) {
            r.setBetCount(j.at("betCount").get<int>());
        }

        if(j.contains("commission")) {
            r.setCommission(j.at("commission").get<double>());
        }

        if(j.contains("priceMatched")) {
            r.setPriceMatched(j.at("priceMatched").get<double>());
        }

        if(j.contains("priceReduced")) {
            r.setPriceReduced(j.at("priceReduced").get<bool>());
        }

        if(j.contains("sizeSettled")) {
            r.setSizeSettled(j.at("sizeSettled").get<double>());
        }

        if(j.contains("profit")) {
            r.setProfit(j.at("profit").get<double>());
        }

        if(j.contains("sizeCancelled")) {
            r.setSizeCancelled(j.at("sizeCancelled").get<double>());
        }

        if(j.contains("customerOrderRef")) {
            r.setCustomerOrderRef(j.at("customerOrderRef").get<std::string>());
        }

        if(j.contains("customerStrategyRef")) {
            r.setCustomerStrategyRef(j.at("customerStrategyRef").get<std::string>());
        }

        if(j.contains("sourceIdKey")) {
            r.setSourceIdKey(j.at("sourceIdKey").get<std::string>());
        }

        if(j.contains("sourceIdDescription")) {
            r.setSourceIdDescription(j.at("sourceIdDescription").get<std::string>());
        }
    }

    void to_json(nlohmann::json& j, const ClearedOrderSummary& k) {
        if (!k.getEventTypeId().empty()) {
            j["eventTypeId"] = k.getEventTypeId();
        }
        if (!k.getEventId().empty()) {
            j["eventId"] = k.getEventId();
        }
        if (!k.getMarketId().empty()) {
            j["marketId"] = k.getMarketId();
        }
        if (k.getSelectionId() != 0) {
            j["selectionId"] = k.getSelectionId();
        }
        if (k.getHandicap() != 0.0) {
            j["handicap"] = k.getHandicap();
        }
        if (!k.getBetId().empty()) {
            j["betId"] = k.getBetId();
        }
        if (k.getPlacedDate().isValid()) {
            j["placedDate"] = k.getPlacedDate().toIsoString();
        }

        if(k.getPersistenceType() != BettingEnum::PersistenceType::UNKNOWN) {
            std::cerr << "WTF\n";
            std::cerr << Utils::to_string<BettingEnum::PersistenceType>(k.getPersistenceType());
            
            j["persistenceType"] = Utils::to_string<BettingEnum::PersistenceType>(k.getPersistenceType());
        }

        if(k.getOrderType() != BettingEnum::OrderType::UNKNOWN) {
            j["orderType"] = Utils::to_string<BettingEnum::OrderType>(k.getOrderType());
        }

        if(k.getSide() != BettingEnum::Side::UNKNOWN) {
            j["side"] = Utils::to_string<BettingEnum::Side>(k.getSide());
        }

        if (!k.getItemDescription().getEventDesc().empty()) {
            j["itemDescription"] = k.getItemDescription();
        }

        if (!k.getBetOutcome().empty()) {
            j["betOutcome"] = k.getBetOutcome();
        }
        
        if (k.getPriceRequested() >= 0) {
            j["priceRequested"] = k.getPriceRequested();
        }
        
        if (k.getSettledDate().isValid()) {
            j["settledDate"] = k.getSettledDate().toIsoString();
        }
        
        if (k.getLastMatchedDate().isValid()) {
            j["lastMatchedDate"] = k.getLastMatchedDate().toIsoString();
        }
        
        if (k.getBetCount() >= 0) {
            j["betCount"] = k.getBetCount();
        }
        
        if (k.getCommission() >= 0) {
            j["commission"] = k.getCommission();
        }
        
        if (k.getPriceMatched() >= 0) {
            j["priceMatched"] = k.getPriceMatched();
        }
        
        if(k.getPriceReduced() >= 0) {
            j["priceReduced"] = k.getPriceReduced();
        }

        if (k.getSizeSettled() >= 0) {
            j["sizeSettled"] = k.getSizeSettled();
        }
        
        if (k.getProfit() >= 0) {
            j["profit"] = k.getProfit();
        }
        
        if (k.getSizeCancelled() >= 0) {
            j["sizeCancelled"] = k.getSizeCancelled();
        }
        
        if (!k.getCustomerOrderRef().empty()) {
            j["customerOrderRef"] = k.getCustomerOrderRef();
        }
        
        if (!k.getCustomerStrategyRef().empty()) {
            j["customerStrategyRef"] = k.getCustomerStrategyRef();
        }
        
        if (!k.getSourceIdKey().empty()) {
            j["sourceIdKey"] = k.getSourceIdKey();
        }
        
        if (!k.getSourceIdDescription().empty()) {
            j["sourceIdDescription"] = k.getSourceIdDescription();
        }
    }
    
    void from_json(const nlohmann::json& j, ItemDescription& k) {
        if(j.contains("eventTypeDesc")) {
            k.setEventTypeDesc(j.at("eventTypeDesc").get<std::string>());
        }

        if(j.contains("eventDesc")) {
            k.setEventDesc(j.at("eventDesc").get<std::string>());
        }

        if(j.contains("marketDesc")) {
            k.setMarketDesc(j.at("marketDesc").get<std::string>());
        }

        if(j.contains("marketType")) {
            k.setMarketType(j.at("marketType").get<std::string>());
        }

        if(j.contains("marketStartTime")) {
            k.setMarketStartTime(Utils::Date(j.at("marketStartTime").get<std::string>()));
        }

        if(j.contains("runnerDesc")) {
            k.setRunnerDesc(j.at("runnerDesc").get<std::string>());
        }

        if(j.contains("numberOfWinners")) {
            k.setNumberOfWinners(j.at("numberOfWinners").get<int>());
        }

        if(j.contains("eachWayDivisor")) {
            k.setEachWayDivisor(j.at("eachWayDivisor").get<double>());
        }
    }

    void to_json(nlohmann::json& j, const ItemDescription& k) {
        if (!k.getEventTypeDesc().empty()) {
            j["eventTypeDesc"] = k.getEventTypeDesc();
        }
        if (!k.getEventDesc().empty()) {
            j["eventDesc"] = k.getEventDesc();
        }
        if (!k.getMarketDesc().empty()) {
            j["marketDesc"] = k.getMarketDesc();
        }
        if (!k.getMarketType().empty()) {
            j["marketType"] = k.getMarketType();
        }
        if (k.getMarketStartTime().isValid()) {
            j["marketStartTime"] = k.getMarketStartTime().toIsoString();
        }
        if (!k.getRunnerDesc().empty()) {
            j["runnerDesc"] = k.getRunnerDesc();
        }
        if (k.getNumberOfWinners() >= 0) {
            j["numberOfWinners"] = k.getNumberOfWinners();
        }
        if (k.getEachWayDivisor() >= 0) {
            j["eachWayDivisor"] = k.getEachWayDivisor();
        }
    }

}
