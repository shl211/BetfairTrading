#ifndef DATE_H
#define DATE_H

#include <string>
#include <ostream>

namespace BetfairAPI {
    enum class Month {
        January = 1,
        February,
        March,
        April,
        May,
        June,
        July,
        August,
        September,
        October,
        November,
        December,
    };

    inline std::string to_string(Month month) {
        switch (month) {
            case Month::January:   return "January";
            case Month::February:  return "February";
            case Month::March:     return "March";
            case Month::April:     return "April";
            case Month::May:       return "May";
            case Month::June:      return "June";
            case Month::July:      return "July";
            case Month::August:    return "August";
            case Month::September: return "September";
            case Month::October:   return "October";
            case Month::November:  return "November";
            case Month::December:  return "December";
            default:               return "Unknown";
        }
    }

    inline std::ostream& operator<<(std::ostream& os, Month month) {
        return os << to_string(month);
    }
    
    class Date {
        
    public:
        Date(int year, Month month, int day, int hour=0,int minute=0, int second=0, int millisecond=0);
        Date(std::string datetime);
        ~Date();
        Date(const Date&) = default;
        Date(Date&&) noexcept = default;
        Date& operator=(const Date&) = default;
        Date& operator=(Date&&) noexcept = default;

        friend std::ostream& operator<<(std::ostream& os, const Date& date);

    private:
        int day_;
        Month month_;
        int year_;
        int hour_;
        int minute_;
        int second_;
        int millisecond_;

        static bool isValidDate(int year, Month month, int day, int hour=0,int minute=0, int second=0, int millisecond=0);
        static bool isLeapYear(int year);

    };
}

#endif