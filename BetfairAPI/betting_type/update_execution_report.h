#pragma once

#include <string> 
#include <vector>
#include "betting_enum/execution_report_status.hpp"
#include "betting_enum/execution_report_error_code.hpp"
#include "update_instruction_report.h"

namespace BetfairAPI::BettingType {
    class UpdateExecutionReport {
        public:
            UpdateExecutionReport(BetfairAPI::BettingEnum::ExecutionReportStatus status);
            ~UpdateExecutionReport() = default;
            UpdateExecutionReport(const UpdateExecutionReport&) = default;
            UpdateExecutionReport(UpdateExecutionReport&&) noexcept = default;
            UpdateExecutionReport& operator=(const UpdateExecutionReport&) = default;
            UpdateExecutionReport& operator=(UpdateExecutionReport&&) noexcept = default;

            void setCustomerRef(std::string_view s);
            void setErrorCode(BetfairAPI::BettingEnum::ExecutionReportErrorCode e);
            void setMarketId(std::string_view s);
            void addInstructionReport(UpdateInstructionReport report);

            const std::string& getCustomerRef() const;
            BetfairAPI::BettingEnum::ExecutionReportStatus getStatus() const;
            BetfairAPI::BettingEnum::ExecutionReportErrorCode getErrorCode() const;
            const std::string& getMarketId() const;
            const std::vector<UpdateInstructionReport>& getInstructionReports() const;

        private:
            std::string customer_ref_;
            BetfairAPI::BettingEnum::ExecutionReportStatus status_;
            BetfairAPI::BettingEnum::ExecutionReportErrorCode error_code_;
            std::string market_id_;
            std::vector<UpdateInstructionReport> instruction_reports_;
    };
}