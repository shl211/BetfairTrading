#pragma once

#include <optional>
#include <string> 
#include <vector> 
#include "BetfairAPI/utils.h"
#include "BetfairAPI/betting_enum/execution_report_status.hpp"
#include "BetfairAPI/betting_enum/execution_report_error_code.hpp"
#include "BetfairAPI/betting_type/place_instruction_report.h"

namespace BetfairAPI::BettingType {
    struct PlaceExecutionReport {
        BettingEnum::ExecutionReportStatus status;
        std::optional<std::string> customerRef;
        std::optional<BettingEnum::ExecutionReportErrorCode> errorCode;
        std::optional<std::string> marketId;
        std::vector<PlaceInstructionReport> instructionReports;
    };

    inline bool operator==(const PlaceExecutionReport& lhs, const PlaceExecutionReport& rhs) {
        return lhs.status == rhs.status &&
               lhs.customerRef == rhs.customerRef &&
               lhs.errorCode == rhs.errorCode &&
               lhs.marketId == rhs.marketId &&
               lhs.instructionReports == rhs.instructionReports;
    }

    inline bool operator!=(const PlaceExecutionReport& lhs, const PlaceExecutionReport& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const PlaceExecutionReport& report) {
        os << "PlaceExecutionReport{status=" << to_string(report.status)
           << ", customerRef=" << (report.customerRef ? *report.customerRef : "null")
           << ", errorCode=";
        if (report.errorCode)
            os << to_string(*report.errorCode);
        else
            os << "null";
        os << ", marketId=" << (report.marketId ? *report.marketId : "null")
           << ", instructionReports=[";
        for (size_t i = 0; i < report.instructionReports.size(); ++i) {
            os << report.instructionReports[i];
            if (i + 1 < report.instructionReports.size())
                os << ", ";
        }
        os << "]}";
        return os;
    }
}