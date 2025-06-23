#pragma once

#include <string>

#include "betting_enum/instruction_report_status.hpp"
#include "betting_enum/instruction_report_error_code.hpp"
#include "betting_enum/order_status.hpp"
#include "place_instruction.h"
#include "utils/date_utils.h"

namespace BetfairAPI::BettingType {
    class PlaceInstructionReport {
        public:
            PlaceInstructionReport(BetfairAPI::BettingEnum::InstructionReportStatus status,
                PlaceInstruction instruction);
            PlaceInstructionReport() = default;
            ~PlaceInstructionReport() = default;
            PlaceInstructionReport(const PlaceInstructionReport&) = default;
            PlaceInstructionReport(PlaceInstructionReport&&) noexcept = default;
            PlaceInstructionReport& operator=(const PlaceInstructionReport&) = default;
            PlaceInstructionReport& operator=(PlaceInstructionReport&&) noexcept = default;

            void setErrorCode(BetfairAPI::BettingEnum::InstructionReportErrorCode e);
            void setOrderStatus(BetfairAPI::BettingEnum::OrderStatus status);
            void setBetId(std::string_view id);
            void setPlacedDate(BetfairAPI::Utils::Date date);
            void setAveragePriceMatched(double val);
            void setSizeMatched(double val);

            BetfairAPI::BettingEnum::InstructionReportStatus getStatus() const;
            BetfairAPI::BettingEnum::InstructionReportErrorCode getErrorCode() const;
            BetfairAPI::BettingEnum::OrderStatus getOrderStatus() const;
            const PlaceInstruction& getInstruction() const;
            const std::string& getBetId() const;
            const BetfairAPI::Utils::Date& getPlacedDate() const;
            double getAveragePriceMatched() const;
            double getSizeMatched() const;

        private:
            BetfairAPI::BettingEnum::InstructionReportStatus status_;
            BetfairAPI::BettingEnum::InstructionReportErrorCode error_code_;
            BetfairAPI::BettingEnum::OrderStatus order_status_;
            PlaceInstruction instruction_;
            std::string bet_id_;
            BetfairAPI::Utils::Date placed_date_;
            double average_price_matched_;
            double size_matched_;
    };
}