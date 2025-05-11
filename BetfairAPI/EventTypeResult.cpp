#include "EventTypeResult.h"

namespace BetfairAPI {
    EventTypeResult::EventTypeResult(int event_id,int market_count) : 
        eventType_(static_cast<EventTypeIds>(event_id)),
        marketCount_(market_count) {}

    EventTypeResult::~EventTypeResult() {
        //do nothing
    }

    std::ostream& operator<<(std::ostream& os, const EventTypeResult& event) {        
        os << "Event Type ID: " << static_cast<int>(event.eventType_) << " (" << 
        eventTypeIdsToString(event.eventType_) << "), Market Count: " << event.marketCount_;
    
        return os;
    }
    
}