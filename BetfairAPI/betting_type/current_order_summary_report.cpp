#include "current_order_summary_report.h"

namespace BetfairAPI::BettingType {
    
    CurrentOrderSummaryReport::CurrentOrderSummaryReport(std::vector<CurrentOrderSummary> orders,bool more_available)
        : current_orders_(orders), more_available_(more_available) {}

    const std::vector<CurrentOrderSummary>& CurrentOrderSummaryReport::getCurrentOrders() const {
        return current_orders_;
    }

    bool  CurrentOrderSummaryReport::isMoreAvailable() const {
        return more_available_;
    }
}