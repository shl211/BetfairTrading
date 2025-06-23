#pragma once

#include <string>
#include <vector>

#include "betting_enum/execution_report_status.hpp"
#include "betting_enum/execution_report_error_code.hpp"
#include "place_instruction_report.h"

namespace BetfairAPI::BettingType {
    class PlaceExecutionReport {
        public:
            PlaceExecutionReport(BetfairAPI::BettingEnum::ExecutionReportStatus status);
            ~PlaceExecutionReport() = default;
            PlaceExecutionReport(const PlaceExecutionReport&) = default;
            PlaceExecutionReport(PlaceExecutionReport&&) noexcept = default;
            PlaceExecutionReport& operator=(const PlaceExecutionReport&) = default;
            PlaceExecutionReport& operator=(PlaceExecutionReport&&) noexcept = default;
    
            void setCustomerRef(std::string_view s);
            void setErrorCode(BetfairAPI::BettingEnum::ExecutionReportErrorCode e);
            void setMarketId(std::string_view s);
            void addInstructionReports(PlaceInstructionReport report);

            const std::string& getCustomerRef() const;
            BetfairAPI::BettingEnum::ExecutionReportStatus getStatus() const;
            BetfairAPI::BettingEnum::ExecutionReportErrorCode getErrorCode() const;
            const std::string& getMarketId() const;
            const std::vector<PlaceInstructionReport>& getInstructionReports() const;


        private:
            std::string customer_ref_;
            BetfairAPI::BettingEnum::ExecutionReportStatus status_;
            BetfairAPI::BettingEnum::ExecutionReportErrorCode error_code_;
            std::string market_id_;
            std::vector<PlaceInstructionReport> instruction_reports_; 

    };
}