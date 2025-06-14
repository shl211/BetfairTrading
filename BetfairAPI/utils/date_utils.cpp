#include "date_utils.h"

#include <sstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>

namespace BetfairAPI::Utils {
    Date::Date(std::string_view iso8601) 
        : zoned_time_(iso8601){}

    std::string Date::toIsoString() const {
        return zoned_time_;
    }
}