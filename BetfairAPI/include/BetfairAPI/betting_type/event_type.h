#pragma once

#include <string>
#include <ostream>

namespace BetfairAPI::BettingType {
    struct EventType {
        std::string id;
        std::string name;
    };

    inline bool operator==(const EventType& lhs,const EventType& rhs) {
        return lhs.id == rhs.id && lhs.name == rhs.name;
    };

    inline bool operator!=(const EventType& lhs, const EventType& rhs) {
        return !(lhs == rhs);
    };

    inline std::ostream& operator<<(std::ostream& os,const EventType& e_type) {
        os << "Event type: " << e_type.name << " (ID:" << e_type.id << ")";
        return os;
    }
}