#pragma once

#include <string>
#include <ostream>

namespace BetfairAPI::BettingType {
    struct Competition {
        std::string id;
        std::string name;
    };

    inline bool operator==(const Competition& lhs,const Competition& rhs) {
        return lhs.id == rhs.id && lhs.name == rhs.name;
    };

    inline bool operator!=(const Competition& lhs,const Competition& rhs) {
        return !(lhs == rhs);
    };

    inline std::ostream& operator<<(std::ostream& os, const Competition& comp) {
        os << "Competition: " << comp.name << " (ID:" << comp.id << ")";
        return os;
    }
}