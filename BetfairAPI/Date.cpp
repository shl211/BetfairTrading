#include "Date.h"

#include <stdexcept>
#include <array>
#include <iomanip>

namespace BetfairAPI {
    Date::Date(int year,Month month,int day,int hour, int minute,int second,int millisecond) :
        day_(day), month_(month), year_(year), hour_(hour), minute_(minute), second_(second), millisecond_(millisecond) {

        if (!isValidDate(year_,month_,day_,hour_,minute_,second_,millisecond_)) {
            throw std::invalid_argument("Invalid date");
        }

    }

    Date::~Date() {};

    std::ostream& operator<<(std::ostream& os, const Date& date) {
        os << date.year_ << "-"
            << std::setw(2) << std::setfill('0') << static_cast<int>(date.month_) << "-"
            << std::setw(2) << std::setfill('0') << date.day_ << "T"
            << std::setw(2) << std::setfill('0') << date.hour_ << ":"
            << std::setw(2) << std::setfill('0') << date.minute_ << ":"
            << std::setw(2) << std::setfill('0') << date.second_ << "."
            << std::setw(3) << std::setfill('0') << date.millisecond_;

        return os;
    }

    bool Date::isValidDate(int year, Month month, int day,int hour,int minute, int second, int millisecond) {

        if (hour < 0 || hour >=24) return false;
        if(minute < 0 || minute >= 60) return false;
        if(second < 0 || second >= 60) return false;
        if(millisecond < 0 || millisecond >= 1000) return false;

        static const std::array<int,12> daysInMonth = {
            31,28,31,30,31,30,31,31,30,31,30,31
        };

        int monthIndex = static_cast<int>(month) - 1;
        if (monthIndex < 0 || monthIndex >= 12) return false;

        int maxDay = daysInMonth[monthIndex];
        if (month == Month::February && isLeapYear(year)) {
            maxDay = 29;
        }

        return day >= 1 && day <= maxDay;
    }

    bool Date::isLeapYear(int year) {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }
}