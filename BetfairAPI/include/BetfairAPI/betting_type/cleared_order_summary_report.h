#pragma once

#include <vector>
#include <ostream>
#include "cleared_order_summary.h"

namespace BetfairAPI::BettingType {
    struct ClearedOrderSummaryReport {
        std::vector<ClearedOrderSummary> clearedOrders;
        bool moreAvailable = false;
    };

    inline bool operator==(const ClearedOrderSummaryReport& lhs, const ClearedOrderSummaryReport& rhs) {
        return lhs.clearedOrders == rhs.clearedOrders && lhs.moreAvailable == rhs.moreAvailable;
    }

    inline bool operator!=(const ClearedOrderSummaryReport& lhs, const ClearedOrderSummaryReport& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const ClearedOrderSummaryReport& report) {
        os << "ClearedOrderSummaryReport { clearedOrders: [";
        for (size_t i = 0; i < report.clearedOrders.size(); ++i) {
            os << report.clearedOrders[i];
            if (i + 1 < report.clearedOrders.size()) os << ", ";
        }
        os << "], moreAvailable: " << std::boolalpha << report.moreAvailable << " }";
        return os;
    }
}