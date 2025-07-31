#pragma once

#include <vector>
#include <memory>
#include <unordered_map>
#include "imgui.h"
#include "BetfairAPI/manager.h"
#include "BetfairAPI/date.h"

namespace GUI {
    class ClearedOrderTable{
        public:

            void render(std::weak_ptr<BetfairAPI::BetfairManager> manager);

            bool isUpdated() const {return update_current_order_summary_;};
            int clearedOrderTotal() const {return cached_order_summary_.size();};
            void refresh() {update_current_order_summary_ = true;};

        private:
            bool update_current_order_summary_ = true;
            std::vector<BetfairAPI::BettingType::ClearedOrderSummary> cached_order_summary_;
            std::unordered_map<std::string,std::string> market_id_to_event_name_cache_;
            std::unordered_map<std::string,BetfairAPI::BettingType::MarketCatalogue> market_info_cache_;
            int api_counter_ = 0; //for debug purposes
    };
}