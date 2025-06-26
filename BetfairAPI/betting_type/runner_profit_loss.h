#pragma once
#include <ostream>

namespace BetfairAPI::BettingType {
    class RunnerProfitLoss {
        public:
            RunnerProfitLoss(long selection_id,double if_win, double if_lose, double if_place);
            RunnerProfitLoss() = default;
            ~RunnerProfitLoss() = default;
            RunnerProfitLoss(const RunnerProfitLoss&) = default;
            RunnerProfitLoss(RunnerProfitLoss&&) noexcept = default;
            RunnerProfitLoss& operator=(const RunnerProfitLoss&) = default;
            RunnerProfitLoss& operator=(RunnerProfitLoss&&) noexcept = default;
            
            bool operator==(const RunnerProfitLoss& other) const;
            bool operator!=(const RunnerProfitLoss& other) const;
            friend std::ostream& operator<<(std::ostream& os, const RunnerProfitLoss& rpl);

            long getSelectionId() const;
            double getIfWin() const;
            double getIfLose() const;
            double getIfPlace() const;

        private:
            long selection_id_;//assume to be long
            double if_win_;
            double if_lose_;
            double if_place_;
    };
}