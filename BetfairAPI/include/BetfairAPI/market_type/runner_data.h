#pragma once

#include <mutex>
#include <vector>
#include "BetfairAPI/market_type/price_ladders.h"
#include "BetfairAPI/streaming_type/market_change_message.h"

namespace BetfairAPI::MarketType {    
    enum class Side {BACK,LAY};
    
    class RunnerData {
    public:
        RunnerData() = default;
        ~RunnerData() = default;

        void updateData(StreamingType::RunnerChange rc);

        std::vector<DepthBasedLadder> getBestPrice(Side side, bool virtual_price = false) const;

    private:
        mutable std::mutex mtx_;
        std::vector<DepthBasedLadder> best_available_to_back_;
        std::vector<DepthBasedLadder> best_available_to_lay_;
        std::vector<DepthBasedLadder> best_available_to_back_virtual_;
        std::vector<DepthBasedLadder> best_available_to_lay_virtual_;

        

    };
}