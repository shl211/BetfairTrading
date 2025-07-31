#pragma once

#include <memory>
#include <vector>
#include <string>
#include <set>
#include "imgui.h"
#include "BetfairAPI/manager.h"

namespace GUI {
    struct CompetitionFilter{
        CompetitionFilter(BetfairAPI::BettingType::CompetitionResult c, bool selected)
            : comp_result(std::move(c)), selected(selected) {};
        BetfairAPI::BettingType::CompetitionResult comp_result;
        bool selected = false;
    };
    struct EventTypeFilter{
        EventTypeFilter(BetfairAPI::BettingType::EventTypeResult evt, bool selected)
            : ev_result(std::move(evt)), selected(selected) {};
        BetfairAPI::BettingType::EventTypeResult ev_result;
        bool selected = false;
    };

    class MarketSearch {
        public:
            void render(std::weak_ptr<BetfairAPI::BetfairManager> manager);

            
            private:
            char market_search_[32] = "";
            std::vector<BetfairAPI::BettingType::MarketCatalogue> market_info_;

            std::vector<EventTypeFilter> event_types_;
            std::vector<CompetitionFilter> competitions_;
            std::set<std::string> event_type_ids_;
            std::set<std::string> competition_ids_;

            void searchMarkets(std::weak_ptr<BetfairAPI::BetfairManager> manager);
            void displayTable();
            void loadFilterOptions(std::weak_ptr<BetfairAPI::BetfairManager> manager); //does not currently work
    };
}