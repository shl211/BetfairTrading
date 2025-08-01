#pragma once

#include <memory>
#include <vector>
#include <string>
#include <set>
#include "imgui.h"
#include "BetfairAPI/manager.h"
#include "option_filter.hpp"

namespace GUI {
    class MarketSearch {
        public:
            void render(std::weak_ptr<BetfairAPI::BetfairManager> manager);

            
            private:
            char market_search_[32] = "";
            std::vector<BetfairAPI::BettingType::MarketCatalogue> market_info_;

            std::vector<EventTypeFilter> event_types_;
            std::vector<CompetitionFilter> competitions_;
            std::vector<MarketTypeFilter> market_types_;
            std::set<std::string> event_type_ids_;
            std::set<std::string> competition_ids_;
            std::set<std::string> market_type_ids_;

            void searchMarkets(std::weak_ptr<BetfairAPI::BetfairManager> manager);
            void displayTable();
            void loadFilterOptions(std::weak_ptr<BetfairAPI::BetfairManager> manager); //does not currently work
    };
}