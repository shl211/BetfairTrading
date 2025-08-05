#pragma once

#include <string>
#include <iostream>
#include <chrono>
#include "date/date.h"
#include "date/tz.h"

namespace BetfairAPI {
    
    class Date {
        public:
            explicit Date(const std::string& iso8601);
            ~Date() = default;

            const std::string& getIsoString() const {return iso_8601_;};

            friend bool operator==(const Date& lhs,const Date& rhs);
            friend bool operator!=(const Date& lhs,const Date& rhs);
            friend bool operator<(const Date& lhs,const Date& rhs);
            friend bool operator>(const Date& lhs,const Date& rhs);
            friend bool operator<=(const Date& lhs,const Date& rhs);
            friend bool operator>=(const Date& lhs,const Date& rhs);

        private:
            std::chrono::system_clock::time_point utc_time_;
            std::string iso_8601_;
    };

    inline bool operator==(const Date& lhs,const Date& rhs) {
        return lhs.utc_time_ == rhs.utc_time_;
    }

    inline  bool operator!=(const Date& lhs, const Date& rhs) {
        return !(lhs == rhs);
    }

    inline bool operator<(const Date& lhs,const Date& rhs) {
        return lhs.utc_time_ < rhs.utc_time_;
    }

    inline bool operator>(const Date& lhs,const Date& rhs) {
        return rhs < lhs;
    }

    inline bool operator<=(const Date& lhs, const Date& rhs) {
        return !(rhs < lhs);
    }

    inline bool operator>=(const Date& lhs, const Date& rhs) {
        return !(lhs < rhs);
    }
}

