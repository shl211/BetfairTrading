#pragma once

#include <string>

namespace BetfairAPI::BettingType {
    struct EventType {
        std::string id;
        std::string name;
    };

    inline bool operator==(const EventType& lhs,const EventType& rhs) {
        return lhs.id == rhs.id && lhs.name == rhs.name;
    };

    inline bool operator!=(const EventType& lhs,const EventType& rhs) {
        return !(lhs == rhs);
    };
}