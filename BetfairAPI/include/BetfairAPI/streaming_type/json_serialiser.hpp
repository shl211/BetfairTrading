#pragma once

#include <nlohmann/json.hpp>
#include "BetfairAPI/streaming_type/market_filter.h"
#include "BetfairAPI/utils.h"

namespace BetfairAPI::StreamingType {
    inline void to_json(nlohmann::json& j, const MarketFilter& mf) {
        if (!mf.marketIds.empty()) j["marketIds"] = mf.marketIds;
        if (mf.bspMarket.has_value()) j["bspMarket"] = mf.bspMarket.value();
        if (!mf.bettingTypes.empty()) j["bettingTypes"] = BetfairAPI::to_string(mf.bettingTypes);
        if (!mf.eventTypeIds.empty()) j["eventTypeIds"] = mf.eventTypeIds;
        if (!mf.eventIds.empty()) j["eventIds"] = mf.eventIds;
        if (mf.turnInPlayEnabled.has_value()) j["turnInPlayEnabled"] = mf.turnInPlayEnabled.value();
        if (!mf.marketTypes.empty()) j["marketTypes"] = mf.marketTypes;
        if (!mf.venues.empty()) j["venues"] = mf.venues;
        if (!mf.countryCodes.empty()) j["countryCodes"] = mf.countryCodes;
        if (!mf.raceTypes.empty()) j["raceTypes"] = mf.raceTypes;
    }

    inline void from_json(const nlohmann::json& j, MarketFilter& mf) {
        if (j.contains("marketIds")) j.at("marketIds").get_to(mf.marketIds);
        if (j.contains("bspMarket")) mf.bspMarket = j.at("bspMarket").get<bool>();
        if (j.contains("bettingTypes")) {
            auto tmp = j.at("bettingTypes").get<std::set<std::string>>();
            mf.bettingTypes = BetfairAPI::from_string<StreamingEnum::BettingType>(std::move(tmp));
        }
        if (j.contains("eventTypeIds")) j.at("eventTypeIds").get_to(mf.eventTypeIds);
        if (j.contains("eventIds")) j.at("eventIds").get_to(mf.eventIds);
        if (j.contains("turnInPlayEnabled")) mf.turnInPlayEnabled = j.at("turnInPlayEnabled").get<bool>();
        if (j.contains("marketTypes")) j.at("marketTypes").get_to(mf.marketTypes);
        if (j.contains("venues")) j.at("venues").get_to(mf.venues);
        if (j.contains("countryCodes")) j.at("countryCodes").get_to(mf.countryCodes);
        if (j.contains("raceTypes")) j.at("raceTypes").get_to(mf.raceTypes);
    }
}