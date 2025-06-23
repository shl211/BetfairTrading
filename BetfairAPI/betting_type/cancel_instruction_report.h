#pragma once
#include <optional>

#include "betting_enum/instruction_report_status.hpp"
#include "betting_enum/instruction_report_error_code.hpp"
#include "utils/date_utils.h"
#include "cancel_instruction.h"

namespace BetfairAPI::BettingType {
    class CancelInstructionReport {
        public:
            CancelInstructionReport(BetfairAPI::BettingEnum::InstructionReportStatus status, double size_cancelled);
            CancelInstructionReport() = default;
            ~CancelInstructionReport() = default;
            CancelInstructionReport(const CancelInstructionReport&) = default;
            CancelInstructionReport(CancelInstructionReport&&) noexcept = default;
            CancelInstructionReport& operator=(const CancelInstructionReport&) = default;
            CancelInstructionReport& operator=(CancelInstructionReport&&) noexcept = default;

            void setErrorCode(BetfairAPI::BettingEnum::InstructionReportErrorCode e);
            void setInstruction(CancelInstruction instruction);
            void setCancelledDate(BetfairAPI::Utils::Date date);

            BetfairAPI::BettingEnum::InstructionReportStatus getStatus() const;
            BetfairAPI::BettingEnum::InstructionReportErrorCode getErrorCode() const;
            const std::optional<CancelInstruction>& getInstruction() const;
            double getSizeCancelled() const;
            const BetfairAPI::Utils::Date& getCancelledDate() const;

        private:
            BetfairAPI::BettingEnum::InstructionReportStatus status_;
            BetfairAPI::BettingEnum::InstructionReportErrorCode error_code_;
            std::optional<CancelInstruction> instruction_;
            double size_cancelled_;
            BetfairAPI::Utils::Date cancelled_date_;

    };
}