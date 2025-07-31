#pragma once

#include <memory>
#include <vector>
#include <string>
#include "imgui.h"
#include "BetfairAPI/manager.h"

namespace GUI {
    class MarketSearch {
        public:
            void render(std::weak_ptr<BetfairAPI::BetfairManager> manager) {
                ImGui::Begin("Add Market", nullptr, ImGuiWindowFlags_AlwaysVerticalScrollbar);

                ImGui::InputText("##SearchInput", market_search_, IM_ARRAYSIZE(market_search_));

                ImGui::SameLine();
                if(ImGui::Button("Search")) {
                    if(auto m = manager.lock(); m) {

                        BetfairAPI::BettingType::MarketFilter filter;
                        if(auto s = std::string(market_search_); !s.empty()) {
                            filter.textQuery = std::move(s);
                        }
                        
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

                displayTable();
                ImGui::End();
            }

            void displayTable() {
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

        private:
            char market_search_[32] = "";
            std::vector<BetfairAPI::BettingType::MarketCatalogue> market_info_;
    };
}