#pragma once

#include <vector>
#include "cleared_order_summary.h"

namespace BetfairAPI::BettingType {
    class ClearedOrderSummaryReport {
        public:
            ClearedOrderSummaryReport(const std::vector<ClearedOrderSummary>& cleared_orders,bool more_available);
            ClearedOrderSummaryReport() = default;
            ~ClearedOrderSummaryReport() = default;
            ClearedOrderSummaryReport(const ClearedOrderSummaryReport&) = default;
            ClearedOrderSummaryReport(ClearedOrderSummaryReport&&) noexcept = default;
            ClearedOrderSummaryReport& operator=(const ClearedOrderSummaryReport&) = default;
            ClearedOrderSummaryReport& operator=(ClearedOrderSummaryReport&&) noexcept = default;

            friend std::ostream& operator<<(std::ostream& os, const ClearedOrderSummaryReport& report);

            const std::vector<ClearedOrderSummary>& getClearedOrders() const;
            bool isMoreAvailable() const;

        private:
            std::vector<ClearedOrderSummary> cleared_orders_;
            bool more_available_;
    };
}