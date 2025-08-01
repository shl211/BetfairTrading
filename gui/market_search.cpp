#include <iostream>
#include "market_search.h"

namespace GUI {
    namespace {
        //requires getName() and getId() methods for FilterT and contain selected non-const bool
        template<typename FilterT>
        void renderFilterOptions(
            const std::string& filter_id,
            std::vector<FilterT>& filter_options,
            std::set<std::string>& inout_selected_ids
        ) {
            if (ImGui::TreeNode(filter_id.c_str())) {
                std::string child_id = "##" + filter_id + "_scroll";
                ImGui::BeginChild(child_id.c_str(), ImVec2(0, 150), true, ImGuiWindowFlags_HorizontalScrollbar);

                ImGuiListClipper clipper;
                clipper.Begin(static_cast<int>(filter_options.size()));
                while (clipper.Step()) {
                    for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++) {
                        auto& filter_opt = filter_options[i];
                        
                        // Assuming state change only occurs here
                        if(ImGui::Checkbox(filter_opt.getName().c_str(), &filter_opt.selected)) {
                            if(filter_opt.selected) {
                                inout_selected_ids.insert(filter_opt.getId());
                            }
                            else {
                                inout_selected_ids.erase(filter_opt.getId());
                            }
                        }
                    }
                }
                clipper.End();

                ImGui::EndChild();
                ImGui::TreePop();
            }
        }

        template<typename FilterT>
        void getDataFromBetfair(
            std::weak_ptr<BetfairAPI::BetfairManager> manager,
            std::vector<FilterT>& inout_filters
        ) {
            bool filter_need_loading = inout_filters.empty();
            if(auto m = manager.lock(); m && filter_need_loading) {
                //this mf needed to prevent api failure
                BetfairAPI::BettingType::MarketFilter mf;
                mf.inPlayOnly = false;
                        
                auto data_list = [&]() {
                    if constexpr (std::is_same_v<FilterT, EventTypeFilter>)
                        return m->getEventTypes(mf);
                    else if constexpr (std::is_same_v<FilterT, MarketTypeFilter>)
                        return m->getMarketTypeResults(mf);
                    else if constexpr (std::is_same_v<FilterT, CompetitionFilter>)
                        return m->getCompetitions(mf);
                }();

                inout_filters.reserve(data_list.size());
                for (auto& data : data_list) {
                    inout_filters.emplace_back(data, false);
                }
            }
        }
    }

    void MarketSearch::render(std::weak_ptr<BetfairAPI::BetfairManager> manager) {
        ImGui::Begin("Add Market", nullptr, ImGuiWindowFlags_AlwaysVerticalScrollbar);

        ImGui::InputText("##SearchInput", market_search_, IM_ARRAYSIZE(market_search_));

        ImGui::SameLine();
        if(ImGui::Button("Search")) {
            searchMarkets(manager);
        }
        
        //filter options
        loadFilterOptions(manager);
        renderFilterOptions("Competition",competitions_,competition_ids_);
        renderFilterOptions("Event Type",event_types_,event_type_ids_);
        renderFilterOptions("Market Type",market_types_,market_type_ids_);

        displayTable();
        ImGui::End();
    }

    void MarketSearch::searchMarkets(std::weak_ptr<BetfairAPI::BetfairManager> manager) {
        if(auto m = manager.lock(); m) {
            BetfairAPI::BettingType::MarketFilter filter;
            if(auto s = std::string(market_search_); !s.empty()) {
                filter.textQuery = std::move(s);
            }

            filter.eventTypeIds = event_type_ids_;
            filter.competitionIds = competition_ids_;
            filter.marketTypeCodes = market_type_ids_;

            using MarketProjection = BetfairAPI::BettingEnum::MarketProjection;
            market_info_ = m->getMarketCatalogues(
                std::move(filter),
                {MarketProjection::EVENT,
                    MarketProjection::EVENT_TYPE,
                    MarketProjection::RUNNER_DESCRIPTION,
                    MarketProjection::MARKET_START_TIME
                }
            );
        }
    }

    void MarketSearch::displayTable() {
        auto flags = ImGuiTableFlags_Resizable | ImGuiTableFlags_Borders;

        if (ImGui::BeginTable("MyTable", 6, flags)) {
            ImGui::TableSetupColumn("Event");
            ImGui::TableSetupColumn("Event Type");
            ImGui::TableSetupColumn("Market");
            ImGui::TableSetupColumn("Total Matched");
            ImGui::TableSetupColumn("Market Start Time");
            
            ImGui::TableHeadersRow();
            
            for (auto& info : market_info_) {
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::Text("%s", info.event ? info.event->name.c_str() : "N/A");

                ImGui::TableSetColumnIndex(1);
                ImGui::Text("%s", info.eventType ? info.eventType->name.c_str() : "N/A");

                ImGui::TableSetColumnIndex(2);
                ImGui::Text("%s", !info.marketName.empty() ? info.marketName.c_str() : "N/A");

                ImGui::TableSetColumnIndex(3);
                ImGui::Text("%.2f", info.totalMatched);

                ImGui::TableSetColumnIndex(4);
                ImGui::Text("%s", info.marketStartTime ? info.marketStartTime->getIsoString().c_str() : "N/A");
            }

            ImGui::EndTable();
        }
    }

    void MarketSearch::loadFilterOptions(std::weak_ptr<BetfairAPI::BetfairManager> manager) {
        getDataFromBetfair<CompetitionFilter>(manager,competitions_);
        getDataFromBetfair<EventTypeFilter>(manager,event_types_);
        getDataFromBetfair<MarketTypeFilter>(manager,market_types_);
    }

}