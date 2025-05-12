#include "TimeRangeResult.h"
#include <ostream>

namespace BetfairAPI {
    TimeRangeResult::TimeRangeResult(int market_count,std::string time_from,std::string time_to) : 
        market_count_(market_count),
        time_from_(stringToDate(time_from)),
        time_to_(stringToDate(time_to)) {}

    TimeRangeResult::~TimeRangeResult() {};

    std::ostream& operator<<(std::ostream& os, const TimeRangeResult& res) {
        os << "Time: " << res.time_from_ << " to " << res.time_to_ << " has " << res.market_count_ <<
            " markets";

        return os;
    }

    Date TimeRangeResult::stringToDate(std::string datetime) {
        //assume format 2025-05-16T00:00:00.000
        int year = std::stoi(datetime.substr(0, 4));
        int month = std::stoi(datetime.substr(5, 2));
        int day = std::stoi(datetime.substr(8, 2));
        int hour = std::stoi(datetime.substr(11, 2));
        int minute = std::stoi(datetime.substr(14, 2));
        int second = std::stoi(datetime.substr(17, 2));
        int millisecond = std::stoi(datetime.substr(20, 3));

        return Date(year,static_cast<Month>(month),day,hour,minute,second,millisecond);
    }
}