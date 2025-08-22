#include "BetfairAPI/market_type/market_data.h"

namespace BetfairAPI::MarketType {
    void MarketData::updateMarketData(StreamingType::MarketChange& mcm) {
        
        bool is_delta_update = mcm.image && mcm.image.value();

        if(mcm.marketDefinition) {
            market_definition_ = std::move(mcm.marketDefinition);
        }

        if(is_delta_update) {
            traded_volume_ += mcm.tradedVolume;
        } else {
            traded_volume_ = mcm.tradedVolume;
        }

        for(auto& runner : mcm.runnerChange) {
            auto id = runner.runnerId;
            if(runner_data_.find(id) == runner_data_.end()) {
                //key not yet exists
                runner_data_[id];
            }
            
            if(is_delta_update) {
                runner_data_[id].updateData(runner);
            } else {
                runner_data_[id].replaceData(runner);
            }
        }
    }
}