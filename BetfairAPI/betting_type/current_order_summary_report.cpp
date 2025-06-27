#include "current_order_summary_report.h"

namespace BetfairAPI::BettingType {
    
    CurrentOrderSummaryReport::CurrentOrderSummaryReport(std::vector<CurrentOrderSummary> orders,bool more_available)
        : current_orders_(orders), more_available_(more_available) {}

    std::ostream& operator<<(std::ostream& os, const CurrentOrderSummaryReport& report) {
        os << "Current Order Summary Report: ";

        for(auto& r : report.current_orders_) {
            os << "\n     " << r;
        }

        os << "\n     More available: " << report.more_available_;
        
        return os;
    }


    const std::vector<CurrentOrderSummary>& CurrentOrderSummaryReport::getCurrentOrders() const {
        return current_orders_;
    }

    bool  CurrentOrderSummaryReport::isMoreAvailable() const {
        return more_available_;
    }
}