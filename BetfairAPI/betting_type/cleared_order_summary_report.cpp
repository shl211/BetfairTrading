#include "cleared_order_summary_report.h"
#include <ostream>

namespace BetfairAPI::BettingType {

    ClearedOrderSummaryReport::ClearedOrderSummaryReport(const std::vector<ClearedOrderSummary>& cleared_orders, bool more_available)
        : cleared_orders_(cleared_orders), more_available_(more_available) {}

    std::ostream& operator<<(std::ostream& os, const ClearedOrderSummaryReport& report) {
        os << "Cleared Order Summary Report: ";

        for(auto& r : report.cleared_orders_) {
            os << "\n     " << r;
        }

        os << "\n     More available: " << report.more_available_;
        
        return os;

    }


    const std::vector<ClearedOrderSummary>& ClearedOrderSummaryReport::getClearedOrders() const {
        return cleared_orders_;
    }

    bool ClearedOrderSummaryReport::isMoreAvailable() const {
        return more_available_;
    }

}