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
        nlohmann::json j = {};
        
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

        //order status type
        if (!orderStatusList_.empty()) {
            j["withOrders"] = orderStatusList_;
        }


        //if nothing, return an empty json for payload:
        if (j.empty()) {
            j = {{"",""}};
        }

        return j;
    }

    void MarketFilter::setInPlayOnly(bool inPlayOnly) {
        includeInPlayOnly_ = true;
        inPlayOnly_ = inPlayOnly;
    }

    void MarketFilter::setTurnInPlayEnabled(bool turnInPlayEnabled) {
        includeTurnInPlayEnabled_ = true;
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

    void MarketFilter::addOrderStatus(const OrderStatus& status) {
        //pending and expired are not valid search criteria on MarkertFilter
        if (status != OrderStatus::PENDING and status != OrderStatus::EXPIRED) {
            orderStatusList_.push_back(status);
        }
    }
    
    void MarketFilter::addOrderStatus(const std::vector<OrderStatus>& status) {
        //pending and expired are not valid search criteria on MarkertFilter
        orderStatusList_.reserve(orderStatusList_.size() + orderStatusList_.size());
        for (auto& s : status) {
            //not all OrderStatus enums are valid, so call this one as it handles it
            addOrderStatus(s);
        }
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