
#include "EventResult.h"
#include <ostream>

namespace BetfairAPI {
    EventResult::EventResult(const int market_count,const int event_id,const std::string& country_code, 
            const std::string& timezone,const std::string& venue, const Date& date) : 
            market_count_(market_count),event_id_(event_id),country_code_(country_code),
            timezone_(timezone),venue_(venue),open_date_(date){}

    std::ostream& operator<<(std::ostream& os, const EventResult& event) {
        os << "EventResult { "
           << "Market Count: " << event.market_count_ << ", "
           << "Event ID: " << event.event_id_ << ", "
           << "Country Code: " << event.country_code_ << ", "
           << "Timezone: " << event.timezone_ << ", "
           << "Venue: " << event.venue_ << ", "
           << "Open Date: " << event.open_date_
           << " }";
        return os;
    }

}