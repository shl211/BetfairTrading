#include "update_instruction_report.h"

namespace BetfairAPI::BettingType {

    UpdateInstructionReport::UpdateInstructionReport(
        BetfairAPI::BettingEnum::InstructionReportStatus status,
        BetfairAPI::BettingEnum::InstructionReportErrorCode error_code,
        UpdateInstruction instruction)
        : status_(status), error_code_(error_code), instruction_(std::move(instruction)) {}

    BetfairAPI::BettingEnum::InstructionReportStatus UpdateInstructionReport::getStatus() const {
        return status_;
    }

    BetfairAPI::BettingEnum::InstructionReportErrorCode UpdateInstructionReport::getErrorCode() const {
        return error_code_;
    }

    UpdateInstruction UpdateInstructionReport::getInstruction() const {
        return instruction_;
    }

}