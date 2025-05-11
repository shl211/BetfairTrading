#include "TimeRangeResult.h"
#include <ostream>

namespace BetfairAPI {
    TimeRangeResult::TimeRangeResult(int market_count,std::string time_from,std::string time_to) : 
        market_count_(market_count),
        time_from_(time_from),
        time_to_(time_to) {}

    TimeRangeResult::~TimeRangeResult() {};

    std::ostream& operator<<(std::ostream& os, const TimeRangeResult& res) {
        os << "Time: " << res.time_from_ << " to " << res.time_to_ << " has " << res.market_count_ <<
            " markets";

        return os;
    }
}