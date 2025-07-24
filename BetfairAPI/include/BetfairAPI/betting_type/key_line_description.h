#pragma once

#include <vector>
#include <ostream>
#include "BetfairAPI/betting_type/key_line_selection.h"

namespace BetfairAPI::BettingType {
    struct KeyLineDescription {
        std::vector<KeyLineSelection> keyLine;
    };

    inline bool operator==(const KeyLineDescription& lhs, const KeyLineDescription& rhs) {
        return lhs.keyLine == rhs.keyLine;
    }

    inline bool operator!=(const KeyLineDescription& lhs, const KeyLineDescription& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const KeyLineDescription& obj) {
        os << "KeyLineDescription{keyLine=[";
        for (size_t i = 0; i < obj.keyLine.size(); ++i) {
            os << obj.keyLine[i];
            if (i + 1 < obj.keyLine.size()) os << ", ";
        }
        os << "]}";
        return os;
    }
}