#ifndef MARKET_FILTER_H
#define MARKET_FILTER_H

#include <nlohmann/json.hpp>
#include "EventTypeIds.hpp"
#include "MarketBettingType.hpp"
#include "OrderStatus.hpp"
#include <vector>

namespace BetfairAPI {

    class MarketFilter {
    
    public:
        MarketFilter();
        ~MarketFilter();
    
        nlohmann::json getFilterJson() const;
        void setInPlayOnly(bool inPlayOnly);
        void setTurnInPlayEnabled(bool turnInPlayEnabled);
        void addEventTypeIds(const EventTypeIds& events);
        void addEventTypeIds(const std::vector<EventTypeIds>& events);
        void addMarketBettingType(const MarketBettingType& market);
        void addMarketBettingType(const std::vector<MarketBettingType>& market);
        void addOrderStatus(const OrderStatus& status);
        void addOrderStatus(const std::vector<OrderStatus>& status);


    private:
        
        //for boolean, need extra qualifier to denote whether user has specified or not
        bool includeInPlayOnly_ = false;
        bool inPlayOnly_ = false;

        bool includeTurnInPlayEnabled_ = false;
        bool turnInPlayEnabled_ = false;
        
        std::vector<EventTypeIds> eventTypeList_ {};
        std::vector<MarketBettingType> marketBettingTypeList_ {};
        std::vector<OrderStatus> orderStatusList_ {};

        //helper functions
        std::vector<int> getEventTypeFilterList_() const;


    };
}

#endif