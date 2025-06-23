#pragma once

#include <vector>
#include <string>

#include "betting_enum/execution_report_error_code.hpp"
#include "betting_enum/execution_report_status.hpp"
#include "cancel_instruction_report.h"

namespace BetfairAPI::BettingType {
    class CancelExecutionReport {
        public:
            CancelExecutionReport(BetfairAPI::BettingEnum::ExecutionReportStatus status);
            ~CancelExecutionReport() = default;
            CancelExecutionReport(const CancelExecutionReport&) = default;
            CancelExecutionReport(CancelExecutionReport&&) noexcept = default;
            CancelExecutionReport& operator=(const CancelExecutionReport&) = default;
            CancelExecutionReport& operator=(CancelExecutionReport&&) noexcept = default;

            void addCustomerRef(std::string_view s);
            void addErrorCode(BetfairAPI::BettingEnum::ExecutionReportErrorCode e);
            void addMarketId(std::string_view s);
            void addInstructionReport(CancelInstructionReport report);

            const std::string& getCustomerRef() const;
            BetfairAPI::BettingEnum::ExecutionReportStatus getStatus() const;
            BetfairAPI::BettingEnum::ExecutionReportErrorCode getErrorCode() const;
            const std::string& getMarketId() const;
            const std::vector<CancelInstructionReport>& getInstructionReports() const;

        private:
            std::string customer_ref_;
            BetfairAPI::BettingEnum::ExecutionReportStatus status_;
            BetfairAPI::BettingEnum::ExecutionReportErrorCode error_code_;
            std::string market_id_;
            std::vector<CancelInstructionReport> instruction_reports_;

    };
}