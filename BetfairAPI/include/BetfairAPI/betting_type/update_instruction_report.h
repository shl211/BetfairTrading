#pragma once

#include <optional>
#include <ostream>
#include <magic_enum.hpp>
#include "update_instruction.h"
#include "BetfairAPI/betting_enum/instruction_report_status.hpp"
#include "BetfairAPI/betting_enum/instruction_report_error_code.hpp"

namespace BetfairAPI::BettingType {
    struct UpdateInstructionReport {
        BettingEnum::InstructionReportStatus status;
        UpdateInstruction instruction;
        std::optional<BettingEnum::InstructionReportErrorCode> errorCode;
    };

    inline bool operator==(const UpdateInstructionReport& lhs, const UpdateInstructionReport& rhs) {
        return lhs.status == rhs.status &&
               lhs.instruction == rhs.instruction &&
               lhs.errorCode == rhs.errorCode;
    }

    inline bool operator!=(const UpdateInstructionReport& lhs, const UpdateInstructionReport& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const UpdateInstructionReport& report) {
        os << "UpdateInstructionReport{status=" << magic_enum::enum_name(report.status)
           << ", instruction=" << report.instruction;
        if (report.errorCode) {
            os << ", errorCode=" << magic_enum::enum_name(*report.errorCode);
        } else {
            os << ", errorCode=nullopt";
        }
        os << "}";
        return os;
    }
}