#pragma once

#include <string> 
#include <optional>
#include <ostream>
#include <magic_enum.hpp>
#include "BetfairAPI/betting_enum/instruction_report_status.hpp"
#include "BetfairAPI/betting_enum/instruction_report_error_code.hpp"
#include "BetfairAPI/betting_enum/order_status.hpp"
#include "place_instruction.h"
#include "BetfairAPI/date.h"


namespace BetfairAPI::BettingType {
    struct PlaceInstructionReport {
        BettingEnum::InstructionReportStatus status;
        std::optional<BettingEnum::InstructionReportErrorCode> errorCode;
        std::optional<BettingEnum::OrderStatus> orderStatus;
        PlaceInstruction instruction;
        std::optional<std::string> betId;
        std::optional<Date> placedDate;
        std::optional<double> averagePriceMatched;
        std::optional<double> sizeMatched;
    };

    inline bool operator==(const PlaceInstructionReport& lhs, const PlaceInstructionReport& rhs) {
        return lhs.status == rhs.status &&
               lhs.errorCode == rhs.errorCode &&
               lhs.orderStatus == rhs.orderStatus &&
               lhs.instruction == rhs.instruction &&
               lhs.betId == rhs.betId &&
               lhs.placedDate == rhs.placedDate &&
               lhs.averagePriceMatched == rhs.averagePriceMatched &&
               lhs.sizeMatched == rhs.sizeMatched;
    }

    inline bool operator!=(const PlaceInstructionReport& lhs, const PlaceInstructionReport& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const PlaceInstructionReport& report) {
        os << "PlaceInstructionReport{"
           << "status: " << magic_enum::enum_name(report.status)
           << ", errorCode: " << (report.errorCode ? magic_enum::enum_name(*report.errorCode) : "null")
           << ", orderStatus: " << (report.orderStatus ? magic_enum::enum_name(*report.orderStatus) : "null")
           << ", instruction: " << report.instruction
           << ", betId: " << (report.betId ? *report.betId : "null")
           << ", placedDate: " << (report.placedDate ? report.placedDate->getIsoString() : "null")
           << ", averagePriceMatched: " << (report.averagePriceMatched ? std::to_string(*report.averagePriceMatched) : "null")
           << ", sizeMatched: " << (report.sizeMatched ? std::to_string(*report.sizeMatched) : "null")
           << "}";
        return os;
    }
}

