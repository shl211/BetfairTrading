#pragma once

#include <optional>
#include <ostream>  
#include "BetfairAPI/betting_enum/price_ladder_type.hpp"
#include "BetfairAPI/utils.h"

namespace BetfairAPI::BettingType {
    struct PriceLadderDescription {
        std::optional<BettingEnum::PriceLadderType> type;
    };

    inline bool operator==(const PriceLadderDescription& lhs, const PriceLadderDescription& rhs) {
        return lhs.type == rhs.type;
    }

    inline bool operator!=(const PriceLadderDescription& lhs, const PriceLadderDescription& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const PriceLadderDescription& desc) {
        os << "PriceLadderDescription type: ";
        if (desc.type) {
            os << to_string(*desc.type); //replace with string at some point
        } else {
            os << "N/A";
        }
        return os;
    }
}