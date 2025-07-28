#include <sstream>
#include "BetfairAPI/date.h"

namespace BetfairAPI {
    
    Date::Date(const std::string& iso8601) {
        std::string input = iso8601;
        std::istringstream in;
        
        // Detect if input ends with 'Z' (Zulu time)
        if(iso8601.back() == 'Z') {
            in.str(input);
            in >> date::parse("%FT%T%Z",utc_time_);
        }
        // Detect presence of time zone offset (+ or -) after the 'T'
        else if (auto posT = iso8601.find('T');
                posT != std::string::npos && 
                (iso8601.find('+', posT) != std::string::npos || 
                iso8601.find('-', posT) != std::string::npos)) {
            
            in.str(input);
            in >> date::parse("%FT%T%z", utc_time_);
        }
        // No timezone information, assume UTC by appending 'Z'
        else {
            input += "Z";
            in.str(input);
            in >> date::parse("%FT%T%Z", utc_time_);
        }

        if (in.fail()) {
            throw std::runtime_error("Failed to parse ISO8601 date string " + iso8601);
        }
        
        // Normalize to seconds and reformat as ISO8601 UTC s tring
        auto tp = date::floor<std::chrono::seconds>(utc_time_);
        iso_8601_ = date::format("%FT%TZ", tp);
    }
}