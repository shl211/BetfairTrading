#ifndef TIME_RANGE_RESULT_H
#define TIME_RANGE_RESULT_H

#include <string>

namespace BetfairAPI {
    class TimeRangeResult {
        
    public:
        TimeRangeResult(int market_count,std::string time_from,std::string time_to);
        ~TimeRangeResult();
    
        friend std::ostream& operator<<(std::ostream& os, const TimeRangeResult& res);

    private:
        int market_count_;
        //these should be some sort of date object
        std::string time_from_;
        std::string time_to_;
    };
}

#endif