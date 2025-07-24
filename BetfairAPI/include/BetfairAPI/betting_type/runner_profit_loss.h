#pragma once

#include <ostream>
#include <optional>

namespace BetfairAPI::BettingType {
    struct RunnerProfitAndLoss {
        std::optional<long> selectionId;
        std::optional<double> ifWin;
        std::optional<double> ifLose;
        std::optional<double> ifPlace;
    };

    inline bool operator==(const RunnerProfitAndLoss& lhs, const RunnerProfitAndLoss& rhs) {
        return lhs.selectionId == rhs.selectionId &&
                lhs.ifWin == rhs.ifWin &&
                lhs.ifLose == rhs.ifLose &&
                lhs.ifPlace == rhs.ifPlace;
    }

    inline bool operator!=(const RunnerProfitAndLoss& lhs, const RunnerProfitAndLoss& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const RunnerProfitAndLoss& rpl) {
        os << "RunnerProfitAndLoss{";
        os << "selectionId=";
        if (rpl.selectionId) os << *rpl.selectionId; else os << "nullopt";
        os << ", ifWin=";
        if (rpl.ifWin) os << *rpl.ifWin; else os << "nullopt";
        os << ", ifLose=";
        if (rpl.ifLose) os << *rpl.ifLose; else os << "nullopt";
        os << ", ifPlace=";
        if (rpl.ifPlace) os << *rpl.ifPlace; else os << "nullopt";
        os << "}";
        return os;
    }
}