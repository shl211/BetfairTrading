#ifndef TIME_RANGE_RESULT_H
#define TIME_RANGE_RESULT_H

#include <string>
#include "Date.h"

namespace BetfairAPI {
    class TimeRangeResult {
        
    public:
        TimeRangeResult(int market_count,std::string time_from,std::string time_to);
        ~TimeRangeResult();
    
        friend std::ostream& operator<<(std::ostream& os, const TimeRangeResult& res);

    private:
        int market_count_;
        //these should be some sort of date object
        Date time_from_;
        Date time_to_;

        static Date stringToDate(std::string datetime);
    };
}

#endif