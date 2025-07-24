#pragma once

#include <string>
#include <ostream>
#include <optional>
#include "BetfairAPI/date.h"
#include "BetfairAPI/betting_type/event_type.h"
#include "BetfairAPI/betting_type/event.h"
#include "BetfairAPI/betting_type/competition.h"
#include "BetfairAPI/betting_type/market_description.h"
#include "BetfairAPI/betting_type/runner_catalog.h"

namespace BetfairAPI::BettingType {
    struct MarketCatalogue {
        std::string marketId;
        std::string marketName;
        std::optional<Date> marketStartTime;
        std::optional<MarketDescription> description;
        double totalMatched = 0;
        std::vector<RunnerCatalog> runners;
        std::optional<EventType> eventType;
        std::optional<Competition> competition;
        std::optional<Event> event;
    };

    inline bool operator==(const MarketCatalogue& lhs, const MarketCatalogue& rhs) {
        return lhs.marketId == rhs.marketId && 
        lhs.marketName == rhs.marketName &&
        lhs.marketStartTime == rhs.marketStartTime &&
        lhs.totalMatched == rhs.totalMatched &&
        lhs.description == rhs.description &&
        lhs.eventType == rhs.eventType &&
        lhs.competition == rhs.competition &&
        lhs.runners == rhs.runners &&
        lhs.event == rhs.event;
    }

    inline bool operator!=(const MarketCatalogue& lhs, const MarketCatalogue& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const MarketCatalogue& mc) {
        os << "Market catalogue: " << mc.marketName 
            << " (ID: " << mc.marketId << ")"
            << ", Starts " << (mc.marketStartTime ? mc.marketStartTime->getIsoString() : "N/A");
            
        if(mc.totalMatched > 0) os << ", Matched " << mc.totalMatched;
        if(mc.eventType) os << ", " << *(mc.eventType);
        if(mc.competition) os << ", " << *(mc.competition);
        if(mc.description) os << ", " << *(mc.description);
        if(!mc.runners.empty()) {
            os << ", First runner: " << mc.runners.front();
            if (mc.runners.size() > 1) os << ", etc.";
        }
        if(mc.event) os << ", " << *(mc.event);

        return os;    
    }
}