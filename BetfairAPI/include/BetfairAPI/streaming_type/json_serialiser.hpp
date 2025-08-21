#pragma once

#include <nlohmann/json.hpp>
#include <iostream>
#include "BetfairAPI/streaming_type/market_filter.h"
#include "BetfairAPI/streaming_type/market_data_filter.h"
#include "BetfairAPI/streaming_type/change_message.h"
#include "BetfairAPI/streaming_type/market_description.h"
#include "BetfairAPI/streaming_type/runner_change.h"
#include "BetfairAPI/streaming_type/market_change.h"
#include "BetfairAPI/streaming_type/market_change_message.h"
#include "BetfairAPI/utils.h"

namespace BetfairAPI::StreamingType {
    /**************************************************************************
    * MarketFilter 
    **************************************************************************/
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

    /**************************************************************************
    * MarketDataFilter
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const MarketDataFilter& mf) {
        if (!mf.fields.empty()) j["fields"] = BetfairAPI::to_string(mf.fields);
        if (mf.ladderLevels.has_value()) j["ladderLevels"] = static_cast<int>(mf.ladderLevels.value());
    }

    inline void from_json(const nlohmann::json& j, MarketDataFilter& mf) {
        if (j.contains("fields")) {
            auto tmp = j.at("fields").get<std::set<std::string>>();
            mf.fields = BetfairAPI::from_string<StreamingEnum::TradeField>(std::move(tmp));
        }
        if (j.contains("ladderLevels")) mf.ladderLevels = static_cast<MarketDataFilter::LadderLevel>(j.at("ladderLevels").get<int>());
    }

    /**************************************************************************
    * ChangeMessage
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const ChangeMessage& mf) {
        if (mf.changeType.has_value()) j["ct"] = BetfairAPI::to_string(mf.changeType.value());
        if (mf.segmentType.has_value()) j["segmentType"] = BetfairAPI::to_string(mf.segmentType.value());
        if (mf.conflateMs.has_value()) j["conflateMs"] = mf.conflateMs.value();
        if (mf.status.has_value()) j["status"] = mf.status.value();
        if (mf.heartbeatMs.has_value()) j["heartbeatMs"] = mf.heartbeatMs.value();
        if (mf.publishTime.has_value()) j["pt"] = iso8601ToUnix(mf.publishTime->getIsoString()) * 1000;
        if (mf.initialClk.has_value()) j["initialClk"] = mf.initialClk.value();
        if (mf.clk.has_value()) j["clk"] = mf.clk.value();
    }

    inline void from_json(const nlohmann::json& j, ChangeMessage& mf) {
        if (j.contains("ct")) {
            mf.changeType = BetfairAPI::from_string<StreamingEnum::ChangeType>(j.at("ct").get<std::string>());
        } else {
            mf.changeType = StreamingEnum::ChangeType::NULLTYPE;
        }

        if (j.contains("segmentType"))
            mf.segmentType = BetfairAPI::from_string<StreamingEnum::SegmentType>(j.at("segmentType").get<std::string>());
        if (j.contains("conflateMs")) mf.conflateMs = j.at("conflateMs").get<int>();
        if (j.contains("status")) mf.status = j.at("status").get<int>();
        if (j.contains("heartbeatMs")) mf.heartbeatMs = j.at("heartbeatMs").get<int>();
        if (j.contains("pt"))
            mf.publishTime = BetfairAPI::Date(unixToISO8601(j.at("pt").get<std::time_t>() / 1000));
        if (j.contains("initialClk")) mf.initialClk = j.at("initialClk").get<std::string>();
        if (j.contains("clk")) mf.clk = j.at("clk").get<std::string>();
    }
    
    /**************************************************************************
    * MarketDefinition
    **************************************************************************/
   inline void to_json(nlohmann::json& j, const MarketDefinition& mf) {
       if (mf.id.has_value()) j["id"] = mf.id.value();
       if (mf.venue.has_value()) j["venue"] = mf.venue.value();
       if (mf.raceType.has_value()) j["raceType"] = mf.raceType.value();
       if (mf.settledTime.has_value()) j["settledTime"] = mf.settledTime->getIsoString();
       if (mf.timeZone.has_value()) j["timeZone"] = mf.timeZone.value();
       if (mf.eachWayDivisor.has_value()) j["eachWayDivisor"] = mf.eachWayDivisor.value();
       if (mf.bspMarket.has_value()) j["bspMarket"] = mf.bspMarket.value();
       if (mf.turnInPlayEnabled.has_value()) j["turnInPlayEnabled"] = mf.turnInPlayEnabled.value();
       if (mf.priceLadderDefinition.has_value()) j["priceLadderDefinition"]["type"] = mf.priceLadderDefinition.value();
       if (mf.keyLineDefinition.has_value()) j["keyLineDefinition"] = mf.keyLineDefinition.value();
       if (mf.persistenceEnabled.has_value()) j["persistenceEnabled"] = mf.persistenceEnabled.value();
       if (mf.marketBaseRate.has_value()) j["marketBaseRate"] = mf.marketBaseRate.value();
       if (mf.eventId.has_value()) j["eventId"] = mf.eventId.value();
       if (mf.eventTypeId.has_value()) j["eventTypeId"] = mf.eventTypeId.value();
       if (mf.numberOfWinners.has_value()) j["numberOfWinners"] = mf.numberOfWinners.value();
       if (mf.countryCode.has_value()) j["countryCode"] = mf.countryCode.value();
       if (mf.lineMaxUnit.has_value()) j["lineMaxUnit"] = mf.lineMaxUnit.value();
       if (mf.bettingType.has_value()) j["bettingType"] = mf.bettingType.value();
       if (mf.marketType.has_value()) j["marketType"] = mf.marketType.value();
       if (mf.marketTime.has_value()) j["marketTime"] = mf.marketTime->getIsoString();
       if (mf.suspendTime.has_value()) j["suspendTime"] = mf.suspendTime->getIsoString();
       if (mf.bspReconciled.has_value()) j["bspReconciled"] = mf.bspReconciled.value();
       if (mf.complete.has_value()) j["complete"] = mf.complete.value();
       if (mf.inPlay.has_value()) j["inPlay"] = mf.inPlay.value();
       if (mf.crossMatching.has_value()) j["crossMatching"] = mf.crossMatching.value();
       if (mf.runnersVoidable.has_value()) j["runnersVoidable"] = mf.runnersVoidable.value();
       if (mf.numberOfActiveRunners.has_value()) j["numberOfActiveRunners"] = mf.numberOfActiveRunners.value();
       if (mf.lineMinUnit.has_value()) j["lineMinUnit"] = mf.lineMinUnit.value();
       if (mf.betDelay.has_value()) j["betDelay"] = mf.betDelay.value();
       if (mf.status.has_value()) j["status"] = mf.status.value();
       if (!mf.regulators.empty()) j["regulators"] = mf.regulators;
       if (mf.discountAllowed.has_value()) j["discountAllowed"] = mf.discountAllowed.value();
       if (mf.openDate.has_value()) j["openDate"] = mf.openDate->getIsoString();
       if (mf.version.has_value()) j["version"] = mf.version.value();
    }
    
    inline void from_json(const nlohmann::json& j, MarketDefinition& mf) {
        if (j.contains("id")) mf.id = j.at("id").get<std::string>();
        if (j.contains("venue")) mf.venue = j.at("venue").get<std::string>();
        if (j.contains("raceType")) mf.raceType = j.at("raceType").get<std::string>();
        if (j.contains("settledTime")) mf.settledTime = BetfairAPI::Date(j.at("settledTime").get<std::string>());
        if (j.contains("timeZone")) mf.timeZone = j.at("timeZone").get<std::string>();
        if (j.contains("eachWayDivisor")) mf.eachWayDivisor = j.at("eachWayDivisor").get<double>();
        if (j.contains("bspMarket")) mf.bspMarket = j.at("bspMarket").get<bool>();
        if (j.contains("turnInPlayEnabled")) mf.turnInPlayEnabled = j.at("turnInPlayEnabled").get<bool>();
        if (j.contains("priceLadderDefinition")) mf.priceLadderDefinition = j.at("priceLadderDefinition").at("type").get<std::string>();
        if (j.contains("keyLineDefinition")) mf.keyLineDefinition = j.at("keyLineDefinition").get<int>();
        if (j.contains("persistenceEnabled")) mf.persistenceEnabled = j.at("persistenceEnabled").get<bool>();
        if (j.contains("marketBaseRate")) mf.marketBaseRate = j.at("marketBaseRate").get<double>();
        if (j.contains("eventId")) mf.eventId = j.at("eventId").get<std::string>();
        if (j.contains("eventTypeId")) mf.eventTypeId = j.at("eventTypeId").get<std::string>();
        if (j.contains("numberOfWinners")) mf.numberOfWinners = j.at("numberOfWinners").get<int>();
        if (j.contains("countryCode")) mf.countryCode = j.at("countryCode").get<std::string>();
        if (j.contains("lineMaxUnit")) mf.lineMaxUnit = j.at("lineMaxUnit").get<double>();
        if (j.contains("bettingType")) mf.bettingType = j.at("bettingType").get<std::string>();
        if (j.contains("marketType")) mf.marketType = j.at("marketType").get<std::string>();
        if (j.contains("marketTime")) mf.marketTime = BetfairAPI::Date(j.at("marketTime").get<std::string>());
        if (j.contains("suspendTime")) mf.suspendTime = BetfairAPI::Date(j.at("suspendTime").get<std::string>());
        if (j.contains("bspReconciled")) mf.bspReconciled = j.at("bspReconciled").get<bool>();
        if (j.contains("complete")) mf.complete = j.at("complete").get<bool>();
        if (j.contains("inPlay")) mf.inPlay = j.at("inPlay").get<bool>();
        if (j.contains("crossMatching")) mf.crossMatching = j.at("crossMatching").get<bool>();
        if (j.contains("runnersVoidable")) mf.runnersVoidable = j.at("runnersVoidable").get<bool>();
        if (j.contains("numberOfActiveRunners")) mf.numberOfActiveRunners = j.at("numberOfActiveRunners").get<int>();
        if (j.contains("lineMinUnit")) mf.lineMinUnit = j.at("lineMinUnit").get<double>();
        if (j.contains("betDelay")) mf.betDelay = j.at("betDelay").get<double>();
        if (j.contains("status")) mf.status = j.at("status").get<std::string>();
        if (j.contains("regulators")) mf.regulators = j.at("regulators").get<std::vector<std::string>>();
        if (j.contains("discountAllowed")) mf.discountAllowed = j.at("discountAllowed").get<bool>();
        if (j.contains("openDate")) mf.openDate = BetfairAPI::Date(j.at("openDate").get<std::string>());
        if (j.contains("version")) mf.version = j.at("version").get<long long>();
    }
    
    /**************************************************************************
    * RunnerValues
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const RunnerValues& v) {
        j["tv"] = v.tradedVolume;
        j["ltp"] = v.lastTradedPrice;
        j["spn"] = v.startingPriceNear;
        j["spf"] = v.startingPriceFar;
    }
    
    inline void from_json(const nlohmann::json& j, RunnerValues& v) {
        if (j.contains("tv")) v.tradedVolume = j.at("tv").get<double>();
        if (j.contains("ltp")) v.lastTradedPrice = j.at("ltp").get<double>();
        if (j.contains("spn")) v.startingPriceNear = j.at("spn").get<double>();
        if (j.contains("spf")) v.startingPriceFar = j.at("spf").get<double>();
    }
    
    /**************************************************************************
    * DepthLadder
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const DepthLadder& d) {
        j = nlohmann::json::array({d.level,d.price,d.size});
    }

    inline void from_json(const nlohmann::json& j, DepthLadder& d) {
        if (j.is_array() && j.size() == 3) {
            d.level = j.at(0).get<int>();
            d.price = j.at(1).get<double>();
            d.size = j.at(2).get<double>();
        }
    }
    
    /**************************************************************************
    * PriceLadder
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const PriceLadder& d) {
        j = nlohmann::json::array({d.price,d.size});
    }

    inline void from_json(const nlohmann::json& j, PriceLadder& d) {
        if (j.is_array() && j.size() == 2) {
            d.price = j.at(0).get<double>();
            d.size = j.at(1).get<double>();
        }
    }

    /**************************************************************************
    * RunnerChange
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const RunnerChange& rc) {
        j = rc.runnerValues;
        j["id"] = rc.runnerId;
        if(rc.conflated) j["con"] = *rc.conflated;

        if(!rc.bestAvailableToBack.empty()) j["batb"] = rc.bestAvailableToBack;
        if(!rc.bestAvailableToLay.empty()) j["batl"] = rc.bestAvailableToLay;
        if(!rc.bestAvailableToBackVirtual.empty()) j["bdatb"] = rc.bestAvailableToBackVirtual;
        if(!rc.bestAvailableToLayVirtual.empty()) j["bdatl"] = rc.bestAvailableToLayVirtual;
        if(!rc.availableToBack.empty()) j["atb"] = rc.availableToBack;
        if(!rc.availableToLay.empty()) j["atl"] = rc.availableToLay;
        if(!rc.startingPriceBack.empty()) j["spb"] = rc.startingPriceBack;
        if(!rc.startingPriceLay.empty()) j["spl"] = rc.startingPriceLay;
        if(!rc.traded.empty()) j["trd"] = rc.traded;
    }

    inline void from_json(const nlohmann::json& j, RunnerChange& rc) {
        if (j.contains("id")) rc.runnerId = j.at("id").get<long>();
        if (j.contains("con")) rc.conflated = j.at("con").get<bool>();

        rc.runnerValues = j.get<RunnerValues>();
        if (j.contains("batb")) rc.bestAvailableToBack = j.at("batb").get<std::vector<DepthLadder>>();
        if (j.contains("batl")) rc.bestAvailableToLay = j.at("batl").get<std::vector<DepthLadder>>();
        if (j.contains("bdatb")) rc.bestAvailableToBackVirtual = j.at("bdatb").get<std::vector<DepthLadder>>();
        if (j.contains("bdatl")) rc.bestAvailableToLayVirtual = j.at("bdatl").get<std::vector<DepthLadder>>();
        if (j.contains("atb")) rc.availableToBack = j.at("atb").get<std::vector<PriceLadder>>();
        if (j.contains("atl")) rc.availableToLay = j.at("atl").get<std::vector<PriceLadder>>();
        if (j.contains("spb")) rc.startingPriceBack = j.at("spb").get<std::vector<PriceLadder>>();
        if (j.contains("spl")) rc.startingPriceLay = j.at("spl").get<std::vector<PriceLadder>>();
        if (j.contains("trd")) rc.traded = j.at("trd").get<std::vector<PriceLadder>>();
    }

    /**************************************************************************
    * MarketChange
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const MarketChange& mc) {
        j["id"] = mc.marketId;
        j["tv"] = mc.tradedVolume;
        j["rc"] = mc.runnerChange;
        if(mc.image) j["img"] = *mc.image;
        if(mc.marketDefinition) j["marketDefinition"] = *mc.marketDefinition;
    }
    inline void from_json(const nlohmann::json& j, MarketChange& mc) {
        if (j.contains("id")) mc.marketId = j.at("id").get<std::string>();
        if (j.contains("tv")) mc.tradedVolume = j.at("tv").get<double>();
        if (j.contains("img")) mc.image = j.at("img").get<bool>();
        if (j.contains("marketDefinition")) mc.marketDefinition = std::make_unique<MarketDefinition>(
            j.at("marketDefinition").get<MarketDefinition>()
        );
        if(j.contains("rc")) mc.runnerChange = j.at("rc").get<std::vector<RunnerChange>>();
    }

    /**************************************************************************
    * MarketChangeMessage
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const MarketChangeMessage& mc) {
        j = static_cast<const ChangeMessage&>(mc);
        j["mc"] = mc.marketChange;
    }

    inline void from_json(const nlohmann::json& j, MarketChangeMessage& mc) {
        j.get_to(static_cast<ChangeMessage&>(mc));
        if (j.contains("mc")) mc.marketChange = j.at("mc").get<std::vector<MarketChange>>();
    }
}