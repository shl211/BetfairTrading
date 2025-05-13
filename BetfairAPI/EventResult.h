
#ifndef EVENT_RESULT_H
#define EVENT_RESULT_H

#include <string>
#include "Date.h"

namespace BetfairAPI {
    class EventResult {
        
    public:
        EventResult(const int market_count,const int event_id,const std::string& country_code, 
            const std::string& timezone,const std::string& venue, const Date& date);
        ~EventResult()=default;

        friend std::ostream& operator<<(std::ostream& os, const EventResult& event);

    private:
        int market_count_;
        int event_id_;
        std::string country_code_;
        std::string timezone_;
        std::string venue_;
        Date open_date_;
    };
}

#endif