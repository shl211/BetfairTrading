#pragma once

#include <mutex>
#include <vector>
#include <map>
#include "BetfairAPI/market_type/price_ladders.h"
#include "BetfairAPI/streaming_type/market_change_message.h"

namespace BetfairAPI::MarketType {    
    enum class Side {BACK,LAY};
    
    class RunnerData {
    public:
        RunnerData() = default;
        ~RunnerData() = default;
        
        void updateData(StreamingType::RunnerChange& rc);
        void replaceData(StreamingType::RunnerChange& rc);

        std::vector<DepthBasedLadder> getBestPriceList(Side side, bool virtual_price = false) const;
        std::map<Price,Size> getPriceLadder(Side side, bool starting_price = false) const;

    private:
        std::vector<DepthBasedLadder> best_available_to_back_;
        std::vector<DepthBasedLadder> best_available_to_lay_;
        std::vector<DepthBasedLadder> best_available_to_back_virtual_;
        std::vector<DepthBasedLadder> best_available_to_lay_virtual_;

        std::map<Price,Size> available_to_back_;
        std::map<Price,Size> available_to_lay_;
        std::map<Price,Size> starting_price_back_;
        std::map<Price,Size> starting_price_lay_;
    };
}