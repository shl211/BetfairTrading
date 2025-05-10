#ifndef MARKET_FILTER_H
#define MARKET_FILTER_H

#include <nlohmann/json.hpp>
#include "EventTypeIds.hpp"
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
        


    private:
        
        //for boolean, need extra qualifier to denote whether user has specified or not
        bool includeInPlayOnly_ = false;
        bool inPlayOnly_ = false;

        bool includeTurnInPlayEnabled_ = false;
        bool turnInPlayEnabled_ = false;
        
        std::vector<EventTypeIds> eventTypeList_ {};
        

        //helper functions
        std::vector<int> getEventTypeFilterList_() const;


    };
}

#endif