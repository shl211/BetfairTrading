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

    void from_json(const nlohmann::json& j, EventType& e);
    void from_json(const nlohmann::json& j, EventTypeResults& etype);
    void from_json(const nlohmann::json& j, Competition& c);
    void from_json(const nlohmann::json& j, CompetitionResult& c);
    void from_json(const nlohmann::json& j, Event& e);
    void from_json(const nlohmann::json& j, EventResult& e);
    void from_json(const nlohmann::json& j, MarketTypeResult& mt);
    void from_json(const nlohmann::json& j, TimeRange& t);
    void from_json(const nlohmann::json& j, TimeRangeResult& t);
}