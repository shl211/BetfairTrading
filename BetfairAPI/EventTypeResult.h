#ifndef EVENT_TYPE_RESULT_H
#define EVENT_TYPE_RESULT_H

#include <ostream> 
#include "EventTypeIds.hpp"

namespace BetfairAPI {
    class EventTypeResult {
    
    public:
        EventTypeResult(int event_id,int market_count);
        ~EventTypeResult();
        EventTypeResult(const EventTypeResult&) = default;
        EventTypeResult(EventTypeResult&&) noexcept = default;
        EventTypeResult& operator=(const EventTypeResult&) = default;
        EventTypeResult& operator=(EventTypeResult&&) noexcept = default;
    
        friend std::ostream& operator<<(std::ostream& os, const EventTypeResult& event);

    private:
        EventTypeIds eventType_;
        int marketCount_;

    };


}

#endif