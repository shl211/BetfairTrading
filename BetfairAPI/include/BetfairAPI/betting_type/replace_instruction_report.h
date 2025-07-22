#pragma once

#include <optional>
#include "cancel_instruction_report.h"
#include "place_instruction_report.h"
#include "BetfairAPI/betting_enum/instruction_report_status.hpp"
#include "BetfairAPI/utils.h"
#include "BetfairAPI/betting_enum/instruction_report_error_code.hpp"

namespace BetfairAPI::BettingType {
    struct ReplaceInstructionReport {
        BettingEnum::InstructionReportStatus status;
        std::optional<BettingEnum::InstructionReportErrorCode> errorCode;
        std::optional<CancelInstructionReport> cancelInstructionReport;
        std::optional<PlaceInstructionReport> placeInstructionReport;
    };

    inline bool operator==(const ReplaceInstructionReport& lhs, const ReplaceInstructionReport& rhs) {
        return lhs.status == rhs.status &&
               lhs.errorCode == rhs.errorCode &&
               lhs.cancelInstructionReport == rhs.cancelInstructionReport &&
               lhs.placeInstructionReport == rhs.placeInstructionReport;
    }

    inline bool operator!=(const ReplaceInstructionReport& lhs, const ReplaceInstructionReport& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const ReplaceInstructionReport& report) {
        os << "ReplaceInstructionReport{status=" << to_string(report.status)
           << ", errorCode=";
        if (report.errorCode) os << to_string(*report.errorCode);
        else os << "nullopt";
        os << ", cancelInstructionReport=";
        if (report.cancelInstructionReport) os << *report.cancelInstructionReport;
        else os << "nullopt";
        os << ", placeInstructionReport=";
        if (report.placeInstructionReport) os << *report.placeInstructionReport;
        else os << "nullopt";
        os << "}";
        return os;
    }
}