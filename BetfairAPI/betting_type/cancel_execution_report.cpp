#include "cancel_execution_report.h"

namespace BetfairAPI::BettingType {
    CancelExecutionReport::CancelExecutionReport(BetfairAPI::BettingEnum::ExecutionReportStatus status)
        : status_(status) {}

    void CancelExecutionReport::addCustomerRef(std::string_view s) {
        customer_ref_ = std::string(s);
    }

    void CancelExecutionReport::addErrorCode(BetfairAPI::BettingEnum::ExecutionReportErrorCode e) {
        error_code_ = e;
    }

    void CancelExecutionReport::addMarketId(std::string_view s) {
        market_id_ = std::string(s);
    }

    void CancelExecutionReport::addInstructionReport(CancelInstructionReport report) {
        instruction_reports_.push_back(std::move(report));
    }

    const std::string& CancelExecutionReport::getCustomerRef() const {
        return customer_ref_;
    }

    BetfairAPI::BettingEnum::ExecutionReportStatus CancelExecutionReport::getStatus() const {
        return status_;
    }

    BetfairAPI::BettingEnum::ExecutionReportErrorCode CancelExecutionReport::getErrorCode() const {
        return error_code_;
    }

    const std::string& CancelExecutionReport::getMarketId() const {
        return market_id_;
    }

    const std::vector<CancelInstructionReport>& CancelExecutionReport::getInstructionReports() const {
        return instruction_reports_;
    }
}