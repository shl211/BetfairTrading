#include "market_search.h"

namespace GUI {
    void MarketSearch::render(std::weak_ptr<BetfairAPI::BetfairManager> manager) {
        ImGui::Begin("Add Market", nullptr, ImGuiWindowFlags_AlwaysVerticalScrollbar);

        ImGui::InputText("##SearchInput", market_search_, IM_ARRAYSIZE(market_search_));

        ImGui::SameLine();
        if(ImGui::Button("Search")) {
            searchMarkets(manager);
        }
        
        //filter options
        loadFilterOptions(manager);
        if (ImGui::TreeNode("Competition")) {
            ImGui::BeginChild("##comp_scroll", ImVec2(0, 150), true, ImGuiWindowFlags_HorizontalScrollbar);

            ImGuiListClipper clipper;
            clipper.Begin(competitions_.size());
            while (clipper.Step()) {
                for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++) {
                    auto& comp = competitions_[i];
                    if(ImGui::Checkbox(comp.comp_result.competition.name.c_str(), &comp.selected)) {
                        if(comp.selected) {
                            competition_ids_.insert(comp.comp_result.competition.id);
                        } else {
                            competition_ids_.erase(comp.comp_result.competition.id);
                        }
                    }
                }
            }
            clipper.End();

            ImGui::EndChild();
            ImGui::TreePop();
        }

        if (ImGui::TreeNode("Event Type")) {
            ImGui::BeginChild("##eventtype_scroll", ImVec2(0, 150), true, ImGuiWindowFlags_HorizontalScrollbar);

            ImGuiListClipper clipper;
            clipper.Begin(event_types_.size());
            while (clipper.Step()) {
                for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++) {
                    auto& ev = event_types_[i];
                    std::string label = ev.ev_result.eventType.name + "##" + std::to_string(i);
                    if(ImGui::Checkbox(label.c_str(), &ev.selected)) {
                        if(ev.selected) {
                            event_type_ids_.insert(ev.ev_result.eventType.id);
                        } else {
                            event_type_ids_.erase(ev.ev_result.eventType.id);
                        }
                    }
                }
            }
            clipper.End();

            ImGui::EndChild();
            ImGui::TreePop();
        }
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
        bool event_type_filter_options_already_obtained = !event_types_.empty();
        bool competition_filter_options_already_obtained = !competitions_.empty();
        
        bool need_to_load_filter = !event_type_filter_options_already_obtained || !competition_filter_options_already_obtained;
        if(auto m = manager.lock(); m && need_to_load_filter) {
            BetfairAPI::BettingType::MarketFilter mf;
            mf.inPlayOnly = false;

            //mf needed to prevent api failure
            auto ev_type_res_list = m->getEventTypes(mf);
            event_types_.reserve(ev_type_res_list.size());

            for(auto ev : ev_type_res_list) {
                event_types_.emplace_back(ev,false);
            };
            
            auto comp_res_list = m->getCompetitions(std::move(mf));
            competitions_.reserve(comp_res_list.size());

            for(auto comp : comp_res_list) {
                competitions_.emplace_back(comp,false);
            }
        }
    }

}