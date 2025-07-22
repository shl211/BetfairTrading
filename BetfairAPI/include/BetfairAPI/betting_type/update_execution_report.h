#pragma once

#include <string>
#include <optional>
#include <ostream>
#include <vector> 
#include "BetfairAPI/utils.h"
#include "BetfairAPI/betting_enum/execution_report_status.hpp"
#include "BetfairAPI/betting_enum/execution_report_error_code.hpp"
#include "update_instruction_report.h"

namespace BetfairAPI::BettingType {
    struct UpdateExecutionReport {
        BettingEnum::ExecutionReportStatus status;
        std::optional<std::string> customerRef;
        std::optional<BettingEnum::ExecutionReportErrorCode> errorCode;
        std::optional<std::string> marketId;
        std::vector<UpdateInstructionReport> instructionReports;
    };

    inline bool operator==(const UpdateExecutionReport& lhs, const UpdateExecutionReport& rhs) {
        return lhs.status == rhs.status &&
               lhs.customerRef == rhs.customerRef &&
               lhs.errorCode == rhs.errorCode &&
               lhs.marketId == rhs.marketId &&
               lhs.instructionReports == rhs.instructionReports;
    }

    inline bool operator!=(const UpdateExecutionReport& lhs, const UpdateExecutionReport& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const UpdateExecutionReport& report) {
        os << "UpdateExecutionReport{status=" << to_string(report.status);
        os << ", customerRef=";
        if (report.customerRef) os << *report.customerRef; else os << "nullopt";
        os << ", errorCode=";
        if (report.errorCode) os << to_string(*report.errorCode); else os << "nullopt";
        os << ", marketId=";
        if (report.marketId) os << *report.marketId; else os << "nullopt";
        os << ", instructionReports=[";
        for (size_t i = 0; i < report.instructionReports.size(); ++i) {
            os << report.instructionReports[i];
            if (i + 1 < report.instructionReports.size()) os << ", ";
        }
        os << "]}";
        return os;
    }
}