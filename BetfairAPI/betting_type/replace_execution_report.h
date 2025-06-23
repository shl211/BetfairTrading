#pragma once

#include <string>
#include <vector>

#include "betting_enum/execution_report_status.hpp"
#include "betting_enum/execution_report_error_code.hpp"
#include "replace_instruction_report.h"

namespace BetfairAPI::BettingType {
    class ReplaceExecutionReport {
        public:
            ReplaceExecutionReport(BetfairAPI::BettingEnum::ExecutionReportStatus status);
            ~ReplaceExecutionReport() = default;
            ReplaceExecutionReport(const ReplaceExecutionReport&) = default;
            ReplaceExecutionReport(ReplaceExecutionReport&&) noexcept = default;
            ReplaceExecutionReport& operator=(const ReplaceExecutionReport&) = default;
            ReplaceExecutionReport& operator=(ReplaceExecutionReport&&) noexcept = default;
        
            void setCustomerRef(std::string_view s);
            void setErrorCode(BetfairAPI::BettingEnum::ExecutionReportErrorCode e);
            void setMarketId(std::string_view s);
            void addInstructionReport(ReplaceInstructionReport report);

            const std::string& getCustomerRef() const;
            BetfairAPI::BettingEnum::ExecutionReportStatus getStatus() const;
            BetfairAPI::BettingEnum::ExecutionReportErrorCode getErrorCode() const;
            const std::string& getMarketId() const;
            const std::vector<ReplaceInstructionReport>& getInstructionReports() const;

        private:
            std::string customer_ref_;
            BetfairAPI::BettingEnum::ExecutionReportStatus status_;
            BetfairAPI::BettingEnum::ExecutionReportErrorCode error_code_;
            std::string market_id_;
            std::vector<ReplaceInstructionReport> instruction_reports_;
    };
}