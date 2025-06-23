#pragma once

#include "betting_enum/instruction_report_status.hpp"
#include "betting_enum/instruction_report_error_code.hpp"
#include "cancel_instruction_report.h"
#include "place_instruction_report.h"

namespace BetfairAPI::BettingType {
    class ReplaceInstructionReport {
        public:
            explicit ReplaceInstructionReport(BetfairAPI::BettingEnum::InstructionReportStatus status);
            ~ReplaceInstructionReport() = default;
            ReplaceInstructionReport(const ReplaceInstructionReport&) = default;
            ReplaceInstructionReport(ReplaceInstructionReport&&) noexcept = default;
            ReplaceInstructionReport& operator=(const ReplaceInstructionReport&) = default;
            ReplaceInstructionReport& operator=(ReplaceInstructionReport&&) noexcept = default;

            void setErrorCode(BetfairAPI::BettingEnum::InstructionReportErrorCode e);
            void setCancelInstructionReport(CancelInstructionReport report);
            void setPlaceInstructionReport(PlaceInstructionReport report);
            
            BetfairAPI::BettingEnum::InstructionReportStatus getStatus() const;
            BetfairAPI::BettingEnum::InstructionReportErrorCode getErrorCode() const;
            const CancelInstructionReport& getCancelInstructionReport() const;
            const PlaceInstructionReport& getPlaceInstructionReport() const;

        private:
            BetfairAPI::BettingEnum::InstructionReportStatus status_;
            BetfairAPI::BettingEnum::InstructionReportErrorCode error_code_;
            CancelInstructionReport cancel_instruction_report_;
            PlaceInstructionReport place_instruction_report_;
    };
}