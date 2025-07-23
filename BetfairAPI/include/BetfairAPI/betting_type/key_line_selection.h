#pragma once 

#include <optional>
#include <ostream>

namespace BetfairAPI::BettingType {
    struct KeyLineSelection {
        std::optional<long> selectionId;
        std::optional<double> handicap;
    };

    inline bool operator==(const KeyLineSelection& lhs, const KeyLineSelection& rhs) {
        return lhs.selectionId == rhs.selectionId && lhs.handicap == rhs.handicap;
    }

    inline bool operator!=(const KeyLineSelection& lhs, const KeyLineSelection& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const KeyLineSelection& kls) {
        os << "KeyLineSelection{selectionId=";
        if (kls.selectionId) os << *kls.selectionId;
        else os << "nullopt";
        os << ", handicap=";
        if (kls.handicap) os << *kls.handicap;
        else os << "nullopt";
        os << "}";
        return os;
    }
}