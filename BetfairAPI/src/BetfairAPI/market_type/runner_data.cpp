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
                data.size += new_data.size;
            }
        }

        void replaceBestDepth(const std::vector<StreamingType::DepthLadder>& input,
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

        template <typename Price, typename Size>
        void updatePriceLadder(const std::vector<BetfairAPI::StreamingType::PriceLadder>& input,
            std::map<Price,Size>& updateTarget    
        ) {
            for(auto& price_data : input) {
                auto price = price_data.price;
                auto size = price_data.size;

                if(size != 0) {
                    updateTarget[price] += size;
                } else {
                    updateTarget.erase(price);
                }
            }
        }

        template <typename Price, typename Size>
        void replacePriceLadder(const std::vector<BetfairAPI::StreamingType::PriceLadder>& input,
            std::map<Price,Size>& updateTarget    
        ) {
            for(auto& price_data : input) {
                auto price = price_data.price;
                auto size = price_data.size;

                if(size != 0) {
                    updateTarget[price] = size;
                } else {
                    updateTarget.erase(price);
                }
            }
        }
    }

    void RunnerData::updateData(StreamingType::RunnerChange& rc) {

        updateBestDepth(rc.bestAvailableToBack,best_available_to_back_);
        updateBestDepth(rc.bestAvailableToLay,best_available_to_lay_);
        updateBestDepth(rc.bestAvailableToBackVirtual,best_available_to_back_virtual_);
        updateBestDepth(rc.bestAvailableToLayVirtual,best_available_to_lay_virtual_);
        
        updatePriceLadder(rc.availableToBack,available_to_back_);
        updatePriceLadder(rc.availableToLay,available_to_lay_);
        updatePriceLadder(rc.startingPriceBack,starting_price_back_);
        updatePriceLadder(rc.startingPriceLay,starting_price_lay_);
    }

    void RunnerData::replaceData(StreamingType::RunnerChange& rc) {

        replaceBestDepth(rc.bestAvailableToBack,best_available_to_back_);
        replaceBestDepth(rc.bestAvailableToLay,best_available_to_lay_);
        replaceBestDepth(rc.bestAvailableToBackVirtual,best_available_to_back_virtual_);
        replaceBestDepth(rc.bestAvailableToLayVirtual,best_available_to_lay_virtual_);
        
        replacePriceLadder(rc.availableToBack,available_to_back_);
        replacePriceLadder(rc.availableToLay,available_to_lay_);
        replacePriceLadder(rc.startingPriceBack,starting_price_back_);
        replacePriceLadder(rc.startingPriceLay,starting_price_lay_);
    }

    std::vector<DepthBasedLadder> RunnerData::getBestPriceList(Side side, bool virtual_price) const {

        if(side == Side::BACK) {
            return virtual_price ? best_available_to_back_virtual_ : best_available_to_back_; 
        }

        return virtual_price ? best_available_to_lay_virtual_ : best_available_to_lay_; 
    }

    std::map<Price,Size> RunnerData::getPriceLadder(Side side, bool starting_price) const {

        if(side == Side::BACK) {
            return starting_price ? starting_price_back_ : available_to_back_;
        }

        return starting_price ? starting_price_lay_ : available_to_lay_;
    }

}
