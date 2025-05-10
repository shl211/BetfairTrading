#include "MarketFilter.h"
#include <iostream>
namespace BetfairAPI {
    MarketFilter::MarketFilter() {
        //do nothing
    }

    MarketFilter::~MarketFilter() {
        //do nothing
    }

    nlohmann::json MarketFilter::getFilterJson() const {
        nlohmann::json j = {{"",""}}; //initialise with empty json
        
        //boolean values
        if (includeInPlayOnly_) {
            j["inPlayOnly"] = inPlayOnly_;
        }

        if(includeTurnInPlayEnabled_) {
            j["turnInPlayEnabled"] = turnInPlayEnabled_;
        }

        //event type filter
        std::vector<int> eventTypeFilterList = getEventTypeFilterList_();
        if (!eventTypeFilterList.empty()) {
            j["eventTypeIds"] = eventTypeFilterList;
        }

        //market betting type
        if (!marketBettingTypeList_.empty()) {
            j["marketBettingTypes"] = marketBettingTypeList_;
        }

        return j;
    }


    void MarketFilter::setInPlayOnly(bool inPlayOnly) {
        includeInPlayOnly_ = true;
        inPlayOnly_ = inPlayOnly;
    }

    void MarketFilter::setTurnInPlayEnabled(bool turnInPlayEnabled) {
        includeInPlayOnly_ = true;
        turnInPlayEnabled_ = turnInPlayEnabled;
    }

    void MarketFilter::addEventTypeIds(const EventTypeIds& events) {
        eventTypeList_.push_back(events);
    }

    void MarketFilter::addEventTypeIds(const std::vector<EventTypeIds>& events) {
        eventTypeList_.reserve(eventTypeList_.size() + events.size());
        eventTypeList_.insert(eventTypeList_.end(),events.begin(),events.end());
    }

    void MarketFilter::addMarketBettingType(const MarketBettingType& marketBettingType) {
        marketBettingTypeList_.push_back(marketBettingType);
    }
    
    void MarketFilter::addMarketBettingType(const std::vector<MarketBettingType>& marketBettingType) {
        marketBettingTypeList_.reserve(marketBettingTypeList_.size() + marketBettingType.size());
        marketBettingTypeList_.insert(marketBettingTypeList_.end(),marketBettingType.begin(),marketBettingType.end());
    }

/*
* Helper funciton
*/

    std::vector<int> MarketFilter::getEventTypeFilterList_() const {
        std::vector<int> eventTypeFilterList;
        eventTypeFilterList.reserve(eventTypeList_.size());
        for (auto& event : eventTypeList_) {
            eventTypeFilterList.push_back(static_cast<int>(event));
        }
        return eventTypeFilterList;
    }

}