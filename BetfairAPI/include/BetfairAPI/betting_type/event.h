#pragma once

#include <string>
#include <ostream>
#include <optional>
#include "BetfairAPI/date.h"

namespace BetfairAPI::BettingType {
    struct Event {
        std::string id;
        std::string name;
        std::string countryCode;
        std::string timezone;
        std::string venue;
        std::optional<Date> openDate;
    };

    inline bool operator==(const Event& lhs, const Event& rhs) {
        return lhs.id == rhs.id &&
                lhs.name == rhs.name &&
                lhs.countryCode == rhs.countryCode &&
                lhs.timezone == rhs.timezone &&
                lhs.venue == rhs.venue &&
                lhs.openDate == rhs.openDate;
    }

    inline bool operator!=(const Event& lhs, const Event& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const Event& event) {
        os << "Event{id: " << event.id
            << ", name: " << event.name
            << ", countryCode: " << event.countryCode
            << ", timezone: " << event.timezone
            << ", venue: " << event.venue
            << ", openDate: " << (event.openDate ? event.openDate->getIsoString() : "N/A")
            << "}";
        return os;
    }
}