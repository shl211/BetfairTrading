#pragma once

#include <vector>
#include <nlohmann/json.hpp>
#include "betting_type/market_filter.h"
#include "betting_type/time_range.h"
#include "betting_type/event_type_results.h"
#include "betting_type/competition_result.h"
#include "betting_type/event_result.h"
#include "utils/date_utils.h"
#include "betting_type/market_type_result.h"
#include "betting_type/time_range_result.h"
#include "betting_type/country_code_result.h"
#include "betting_type/venue_result.h"
#include "betting_type/market_catalogue.h"
#include "betting_type/market_book.h"
#include "betting_type/market_profit_loss.h"

/*
For compatibility with nlohmann::json, define as
void from_json(const nlohmann::json& j, T& p)
void to_json(nlohmann::json& j, const T& p)

Then can just do nlohmann::json j = T to convert object to json
And can use T p = j.get<T>(); to convert json to object
T must be default constructible

Another way is to use adl_serializer??? More efficient apparently.

Ensure in same namespace as the objects
*/

namespace BetfairAPI::BettingType {
    void to_json(nlohmann::json& j, const MarketFilter& mf);
    void to_json(nlohmann::json& j, const TimeRange& t);
    void to_json(nlohmann::json& j, const KeyLineSelection& k);
    void to_json(nlohmann::json& j, const KeyLineDescription& k);
    void to_json(nlohmann::json& j, const MarketBook& k);
    void to_json(nlohmann::json& j, const Runner& k);
    void to_json(nlohmann::json& j, const PriceSize& k);
    void to_json(nlohmann::json& j, const StartingPrices& k);
    void to_json(nlohmann::json& j, const ExchangePrices& k);
    void to_json(nlohmann::json& j, const Match& k);
    void to_json(nlohmann::json& j, const Order& k);


    void from_json(const nlohmann::json& j, EventType& e);
    void from_json(const nlohmann::json& j, EventTypeResults& etype);
    void from_json(const nlohmann::json& j, Competition& c);
    void from_json(const nlohmann::json& j, CompetitionResult& c);
    void from_json(const nlohmann::json& j, Event& e);
    void from_json(const nlohmann::json& j, EventResult& e);
    void from_json(const nlohmann::json& j, MarketTypeResult& mt);
    void from_json(const nlohmann::json& j, TimeRange& t);
    void from_json(const nlohmann::json& j, TimeRangeResult& t);
    void from_json(const nlohmann::json& j, CountryCodeResult& t);
    void from_json(const nlohmann::json& j, VenueResult& t);
    void from_json(const nlohmann::json& j, MarketCatalogue& m);
    void from_json(const nlohmann::json& j, MarketLineRangeInfo& m);
    void from_json(const nlohmann::json& j, PriceLadderDescription& p);
    void from_json(const nlohmann::json& j, MarketDescription& p);
    void from_json(const nlohmann::json& j, RunnerCatalog& r);
    void from_json(const nlohmann::json& j, MarketBook& r);
    void from_json(const nlohmann::json& j, Runner& r);
    void from_json(const nlohmann::json& j, KeyLineSelection& k);
    void from_json(const nlohmann::json& j, KeyLineDescription& k);
    void from_json(const nlohmann::json& j, PriceSize& k);
    void from_json(const nlohmann::json& j, StartingPrices& k);
    void from_json(const nlohmann::json& j, ExchangePrices& k);
    void from_json(const nlohmann::json& j, Match& k);
    void from_json(const nlohmann::json& j, Order& k);
    void from_json(const nlohmann::json& j, MarketProfitLoss& k);
    void from_json(const nlohmann::json& j, RunnerProfitLoss& k);
}   