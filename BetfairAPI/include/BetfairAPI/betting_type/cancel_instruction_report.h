#pragma once

#include <string>
#include <optional>
#include <ostream>
#include "BetfairAPI/utils.h"
#include "BetfairAPI/betting_type/cancel_instruction.h"
#include "BetfairAPI/date.h"
#include "BetfairAPI/betting_enum/instruction_report_error_code.hpp"
#include "BetfairAPI/betting_enum/instruction_report_status.hpp"

namespace BetfairAPI::BettingType {
    struct CancelInstructionReport {
        BettingEnum::InstructionReportStatus status;
        std::optional<BettingEnum::InstructionReportErrorCode> errorCode;
        CancelInstruction instruction;
        double sizeCancelled;
        std::optional<Date> cancelledDate;
    };

    inline bool operator==(const CancelInstructionReport& lhs,const CancelInstructionReport& rhs) {
        return lhs.status == rhs.status &&
            lhs.errorCode == rhs.errorCode &&
            lhs.instruction == rhs.instruction &&
            lhs.sizeCancelled == rhs.sizeCancelled &&
            lhs.cancelledDate == rhs.cancelledDate;
    }
    
    inline bool operator!=(const CancelInstructionReport& lhs,const CancelInstructionReport& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const CancelInstructionReport& obj) {
        os << "CancelInstructionReport{ Status: " << to_string(obj.status) <<
            "errorCode: " << (obj.errorCode ? to_string(*obj.errorCode) : "null") <<
            "instruction: " << obj.instruction <<
            "sizeCancelled: " << std::to_string(obj.sizeCancelled) <<
            "cancelledDate: " << (obj.cancelledDate ? obj.cancelledDate->getIsoString() : "null");

        return os;
    }
}