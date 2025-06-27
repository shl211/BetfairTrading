#pragma once

#include <vector>
#include <ostream>
#include "current_order_summary.h"

namespace BetfairAPI::BettingType {
    class CurrentOrderSummaryReport {
        public:
            CurrentOrderSummaryReport(std::vector<CurrentOrderSummary> orders,bool more_available);
            CurrentOrderSummaryReport() = default;
            ~CurrentOrderSummaryReport() = default;
            CurrentOrderSummaryReport(const CurrentOrderSummaryReport&) = default;
            CurrentOrderSummaryReport(CurrentOrderSummaryReport&&) noexcept = default;
            CurrentOrderSummaryReport& operator=(const CurrentOrderSummaryReport&) = default;
            CurrentOrderSummaryReport& operator=(CurrentOrderSummaryReport&&) noexcept = default;
        
            friend std::ostream& operator<<(std::ostream& os, const CurrentOrderSummaryReport& report);

            const std::vector<CurrentOrderSummary>& getCurrentOrders() const;
            bool isMoreAvailable() const;

            private:
            std::vector<CurrentOrderSummary> current_orders_;
            bool more_available_;
    };
}