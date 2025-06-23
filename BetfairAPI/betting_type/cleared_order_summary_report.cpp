#include "cleared_order_summary_report.h"

namespace BetfairAPI::BettingType {

    ClearedOrderSummaryReport::ClearedOrderSummaryReport(const std::vector<ClearedOrderSummary>& cleared_orders, bool more_available)
        : cleared_orders_(cleared_orders), more_available_(more_available) {}

    const std::vector<ClearedOrderSummary>& ClearedOrderSummaryReport::GetClearedOrders() const {
        return cleared_orders_;
    }

    bool ClearedOrderSummaryReport::IsMoreAvailable() const {
        return more_available_;
    }

}