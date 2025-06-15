#pragma once

#include "betting_enum/instruction_report_error_code.hpp"
#include "betting_enum/instruction_report_status.hpp"
#include "update_instruction.h"

namespace BetfairAPI::BettingType {
    class UpdateInstructionReport {
        public:
            UpdateInstructionReport(BetfairAPI::BettingEnum::InstructionReportStatus status,
                BetfairAPI::BettingEnum::InstructionReportErrorCode error_code,
                UpdateInstruction instruction);
            ~UpdateInstructionReport() = default;
            UpdateInstructionReport(const UpdateInstructionReport&) = default;
            UpdateInstructionReport(UpdateInstructionReport&&) noexcept = default;
            UpdateInstructionReport& operator=(const UpdateInstructionReport&) = default;
            UpdateInstructionReport& operator=(UpdateInstructionReport&&) noexcept = default;

            BetfairAPI::BettingEnum::InstructionReportStatus getStatus() const;
            BetfairAPI::BettingEnum::InstructionReportErrorCode getErrorCode() const;
            UpdateInstruction getInstruction() const;

        private:
            BetfairAPI::BettingEnum::InstructionReportStatus status_;
            BetfairAPI::BettingEnum::InstructionReportErrorCode error_code_;
            UpdateInstruction instruction_;
    };
}