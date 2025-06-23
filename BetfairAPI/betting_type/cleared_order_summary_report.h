#pragma once

#include <vector>
#include "cleared_order_summary.h"

namespace BetfairAPI::BettingType {
    class ClearedOrderSummaryReport {
        public:
            ClearedOrderSummaryReport(const std::vector<ClearedOrderSummary>& cleared_orders,bool more_available);
            ~ClearedOrderSummaryReport() = default;
            ClearedOrderSummaryReport(const ClearedOrderSummaryReport&) = default;
            ClearedOrderSummaryReport(ClearedOrderSummaryReport&&) noexcept = default;
            ClearedOrderSummaryReport& operator=(const ClearedOrderSummaryReport&) = default;
            ClearedOrderSummaryReport& operator=(ClearedOrderSummaryReport&&) noexcept = default;

            const std::vector<ClearedOrderSummary>& GetClearedOrders() const;
            bool IsMoreAvailable() const;

        private:
            std::vector<ClearedOrderSummary> cleared_orders_;
            bool more_available_;
    };
}