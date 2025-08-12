#include "BetfairAPI/market_type/runner_data.h"

namespace BetfairAPI::MarketType {
    namespace {

        void expandDepthLadder(std::vector<DepthBasedLadder>& v,int new_size) {
            auto old_size = v.size();
            v.resize(new_size);

            for(std::size_t i = old_size; i < new_size; ++i) {
                v[i].level = i;
            }
        }

        void updateBestDepth(const std::vector<StreamingType::DepthLadder>& input,
            std::vector<DepthBasedLadder>& updateTarget
        ) {
            for(auto it = input.rbegin(); it != input.rend(); ++it) {
                const auto& new_data = *it;
                
                int level_idx = new_data.level; // Assuming 0-based

                if (level_idx >= static_cast<int>(updateTarget.size())) {
                    expandDepthLadder(updateTarget, level_idx + 1);
                }

                auto& data = updateTarget[level_idx];
                data.level = new_data.level;
                data.price = new_data.price;
                data.size = new_data.size;
            }
        }
    }

    void RunnerData::updateData(StreamingType::RunnerChange rc) {

        std::scoped_lock<std::mutex> lock(mtx_);
        updateBestDepth(rc.bestAvailableToBack,best_available_to_back_);
        updateBestDepth(rc.bestAvailableToLay,best_available_to_lay_);
        updateBestDepth(rc.bestAvailableToBackVirtual,best_available_to_back_virtual_);
        updateBestDepth(rc.bestAvailableToLayVirtual,best_available_to_lay_virtual_);
    }

    std::vector<DepthBasedLadder> RunnerData::getBestPrice(Side side, bool virtual_price) const {
        std::scoped_lock<std::mutex> lock(mtx_);

        if(side == Side::BACK) {
            return virtual_price ? best_available_to_back_virtual_ : best_available_to_back_; 
        }

        return virtual_price ? best_available_to_lay_virtual_ : best_available_to_lay_; 
    }
}
