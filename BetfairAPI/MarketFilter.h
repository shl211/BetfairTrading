#ifndef MARKET_FILTER_H
#define MARKET_FILTER_H

#include <nlohmann/json.hpp>

namespace BetfairAPI {
    class MarketFilter {
    
    public:
        MarketFilter();
        ~MarketFilter();
    
        nlohmann::json getFilterJson() const;
        void setInPlay(bool inPlayOnly);


    private:
        bool includeInPlayOnly = false;
        bool inPlayOnly = true;
    };
}

#endif