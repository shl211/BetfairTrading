#pragma once

#include <string>
#include <vector>
#include <map>
#include "BetfairAPI/market_type/runner_data.h"
#include "BetfairAPI/streaming_type/market_change.h"

namespace BetfairAPI::MarketType {
    class MarketData {
        public:
        void updateMarketData(StreamingType::MarketChange& mcm);
        std::map<long,RunnerData> getRunnerData() const {return runner_data_;};
        
        private:
        std::string market_id_;
        std::map<long,RunnerData> runner_data_;
        std::unique_ptr<StreamingType::MarketDefinition> market_definition_;
        double traded_volume_;
    };
}