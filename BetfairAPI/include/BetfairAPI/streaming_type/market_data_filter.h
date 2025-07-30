#pragma once

#include <set>
#include <ostream>
#include <optional>
#include "BetfairAPI/streaming_type/trade_field.hpp"
#include "BetfairAPI/utils.h"

namespace BetfairAPI::StreamingType {
    struct MarketDataFilter {
        enum LadderLevel {
            ONE=1,
            TWO=2,
            THREE=3,
            FOUR=4,
            FIVE=5,
            SIX=6,
            SEVEN=7,
            EIGHT=8,
            NINE=9,
            TEN=10,
        };

        std::set<StreamingEnum::TradeField> fields;
        std::optional<LadderLevel> ladderLevels;
    };

    inline bool operator==(const MarketDataFilter& lhs, const MarketDataFilter& rhs) {
        return lhs.fields == rhs.fields && lhs.ladderLevels == rhs.ladderLevels;
    }

    inline bool operator!=(const MarketDataFilter& lhs, const MarketDataFilter& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const MarketDataFilter& mdf) {
        os << "MarketDataFilter{fields={";
        bool first = true;
        for (const auto& field : mdf.fields) {
            if (!first) os << ", ";
            os << to_string(field);
            first = false;
        }
        os << "}, ladderLevels=";
        if (mdf.ladderLevels) {
            os << *mdf.ladderLevels;
        } else {
            os << "nullopt";
        }
        os << "}";
        return os;
    }
}