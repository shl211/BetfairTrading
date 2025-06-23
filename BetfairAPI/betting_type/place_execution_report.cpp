#include "place_execution_report.h"

namespace BetfairAPI::BettingType {
    PlaceExecutionReport::PlaceExecutionReport(BetfairAPI::BettingEnum::ExecutionReportStatus status)
        : status_(status) {}

    void PlaceExecutionReport::setCustomerRef(std::string_view s) {
        customer_ref_ = std::string(s);
    }

    void PlaceExecutionReport::setErrorCode(BetfairAPI::BettingEnum::ExecutionReportErrorCode e) {
        error_code_ = e;
    }

    void PlaceExecutionReport::setMarketId(std::string_view s) {
        market_id_ = std::string(s);
    }

    void PlaceExecutionReport::addInstructionReports(PlaceInstructionReport report) {
        instruction_reports_.push_back(std::move(report));
    }

    const std::string& PlaceExecutionReport::getCustomerRef() const {
        return customer_ref_;
    }

    BetfairAPI::BettingEnum::ExecutionReportStatus PlaceExecutionReport::getStatus() const {
        return status_;
    }

    BetfairAPI::BettingEnum::ExecutionReportErrorCode PlaceExecutionReport::getErrorCode() const {
        return error_code_;
    }

    const std::string& PlaceExecutionReport::getMarketId() const {
        return market_id_;
    }

    const std::vector<PlaceInstructionReport>& PlaceExecutionReport::getInstructionReports() const {
        return instruction_reports_;
    }


}