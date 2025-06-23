#include "replace_execution_report.h"

namespace BetfairAPI::BettingType {
    
    ReplaceExecutionReport::ReplaceExecutionReport(BetfairAPI::BettingEnum::ExecutionReportStatus status)
        : status_(status) {}

    void ReplaceExecutionReport::setCustomerRef(std::string_view s) {
        customer_ref_ = std::string(s);
    }

    void ReplaceExecutionReport::setErrorCode(BetfairAPI::BettingEnum::ExecutionReportErrorCode e) {
        error_code_ = e;
    }

    void ReplaceExecutionReport::setMarketId(std::string_view s) {
        market_id_ = std::string(s);
    }

    void ReplaceExecutionReport::addInstructionReport(ReplaceInstructionReport report) {
        instruction_reports_.push_back(std::move(report));
    }

    const std::string& ReplaceExecutionReport::getCustomerRef() const {
        return customer_ref_;
    }
    
    BetfairAPI::BettingEnum::ExecutionReportStatus ReplaceExecutionReport::getStatus() const {
        return status_;
    }

    BetfairAPI::BettingEnum::ExecutionReportErrorCode ReplaceExecutionReport::getErrorCode() const {
        return error_code_;
    }

    const std::string& ReplaceExecutionReport::getMarketId() const {
        return market_id_;
    }

    const std::vector<ReplaceInstructionReport>& ReplaceExecutionReport::getInstructionReports() const {
        return instruction_reports_;
    }

}