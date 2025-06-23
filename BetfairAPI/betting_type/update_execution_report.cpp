#include "update_execution_report.h"

namespace BetfairAPI::BettingType {
    UpdateExecutionReport::UpdateExecutionReport(BetfairAPI::BettingEnum::ExecutionReportStatus status)
        : status_(status) {}

    void UpdateExecutionReport::setCustomerRef(std::string_view s) {
        customer_ref_ = std::string(s);
    }

    void UpdateExecutionReport::setErrorCode(BetfairAPI::BettingEnum::ExecutionReportErrorCode e) {
        error_code_ = e;
    }

    void UpdateExecutionReport::setMarketId(std::string_view s) {
        market_id_ = std::string(s);
    }

    void UpdateExecutionReport::addInstructionReport(UpdateInstructionReport report) {
        instruction_reports_.push_back(std::move(report));
    }

    const std::string& UpdateExecutionReport::getCustomerRef() const {
        return customer_ref_;
    }

    BetfairAPI::BettingEnum::ExecutionReportStatus UpdateExecutionReport::getStatus() const {
        return status_;
    }

    BetfairAPI::BettingEnum::ExecutionReportErrorCode UpdateExecutionReport::getErrorCode() const {
        return error_code_;
    }

    const std::string& UpdateExecutionReport::getMarketId() const {
        return market_id_;
    }
    
    const std::vector<UpdateInstructionReport>& UpdateExecutionReport::getInstructionReports() const {
        return instruction_reports_;
    }

}