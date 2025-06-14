#include "date_utils.h"

#include <sstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>

namespace BetfairAPI::Utils {
    Date::Date(std::string_view iso8601) 
        : zoned_time_(iso8601){}

    bool Date::operator==(const Date& other) const {
        return zoned_time_ == other.zoned_time_;
    }

    bool Date::operator!=(const Date& other) const {
        return !(*this == other);
    }

    std::string Date::toIsoString() const {
        return zoned_time_;
    }
}