#pragma once

#include <vector>
#include "current_order_summary.h"

namespace BetfairAPI::BettingType {
    struct CurrentOrderSummaryReport {
        std::vector<CurrentOrderSummary> currentOrders = {};
        bool moreAvailable = false;
    };

    inline bool operator==(const CurrentOrderSummaryReport& lhs, const CurrentOrderSummaryReport& rhs) {
        return lhs.currentOrders == rhs.currentOrders && lhs.moreAvailable == rhs.moreAvailable;
    }

    inline bool operator!=(const CurrentOrderSummaryReport& lhs, const CurrentOrderSummaryReport& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const CurrentOrderSummaryReport& obj) {
        os << "CurrentOrderSummaryReport{currentOrders=[";
        for (size_t i = 0; i < obj.currentOrders.size(); ++i) {
            os << obj.currentOrders[i];
            if (i + 1 < obj.currentOrders.size()) os << ", ";
        }
        os << "], moreAvailable=" << std::boolalpha << obj.moreAvailable << "}";
        return os;
    }
}