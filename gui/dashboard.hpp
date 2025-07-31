#pragma once

#include <memory>
#include <optional>
#include <vector>
#include <iostream>
#include "imgui.h"
#include "current_order_table.h"
#include "cleared_order_table.h"
#include "market_search.h"
#include "BetfairAPI/manager.h"

namespace GUI {
    class DashboardFrame {
        public:
            void renderTopBar() {
                ImGui::SetNextWindowPos(ImVec2(0, 0));
                ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, 40));

                ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar |
                                        ImGuiWindowFlags_NoResize |
                                        ImGuiWindowFlags_NoMove |
                                        ImGuiWindowFlags_NoScrollbar;

                ImGui::Begin("TopBar", nullptr, flags);

                if (ImGui::Button("Dashboard")) {toggleDashboard();}
                ImGui::SameLine();
                if (ImGui::Button("Markets")) {toggleMarkets();};
                ImGui::SameLine();
                if (ImGui::Button("Positions")) {}
                ImGui::SameLine();

                ImGui::End();
            }

            void renderMainContent(std::weak_ptr<BetfairAPI::BetfairManager> manager) {
                ImGui::SetNextWindowPos(ImVec2(0, 40));
                ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x,
                                                ImGui::GetIO().DisplaySize.y - 40 - 30)); // leave space

                if(show_dashboard_) {
                    renderDashboardSummary(manager);
                }
                else if(show_markets_) {
                    market_search_.render(manager);
                }
            }

            void renderBottomBar(std::weak_ptr<BetfairAPI::BetfairManager> manager) {
                ImGui::SetNextWindowPos(ImVec2(0, ImGui::GetIO().DisplaySize.y - 30));
                ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, 30));

                ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar |
                                        ImGuiWindowFlags_NoResize |
                                        ImGuiWindowFlags_NoMove |
                                        ImGuiWindowFlags_NoScrollbar;

                ImGui::Begin("BottomBar", nullptr, flags);

                //limit api calls
                if(auto m = manager.lock(); !api_called_already) {
                    auto details = m->getAccountDetails();
                    auto funds = m->getAccountFunds();

                    cached_balance_ = *funds.availableToBetBalance;
                    cached_exposure_ = *funds.exposure;

                    api_called_already = true;
                }

                ImGui::Text("Betfair Trading Client");
                ImGui::SameLine();
                ImGui::Text("Available Balance: £%.2f", cached_balance_);
                ImGui::SameLine();
                ImGui::Text("Current Exposure: £%.2f", cached_exposure_);
                ImGui::SameLine();
                ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);

                ImGui::End();
            }

        private:
            bool api_called_already = false;
            float cached_balance_;
            float cached_exposure_;

            bool update_current_order_summary_ = true;
            GUI::CurrentOrderTable current_order_table_;
            GUI::ClearedOrderTable cleared_order_table_;
            GUI::MarketSearch market_search_;

            void renderDashboardSummary(std::weak_ptr<BetfairAPI::BetfairManager> manager) {
                ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse |
                                        ImGuiWindowFlags_NoMove |
                                        ImGuiWindowFlags_NoResize |
                                        ImGuiWindowFlags_NoBringToFrontOnFocus;

                ImGui::Begin("MainContent", nullptr, flags);
                
                if(ImGui::CollapsingHeader("Current Orders")) {
                    ImGui::Text("Current Orders on Betfair Exchange (Total: %d)", current_order_table_.currentOrderTotal());
                    
                    ImGui::SameLine();
                    if(ImGui::Button("Refresh")) {
                        current_order_table_.refresh();
                    }
                    
                    current_order_table_.render(manager);
                }

                ImGui::Separator();

                if(ImGui::CollapsingHeader("Cleared Orders")) {
                    ImGui::Text("Cleared Orders on Betfair Exchange (Total: %d)", cleared_order_table_.clearedOrderTotal());
                    cleared_order_table_.render(manager);
                }

                ImGui::End();
            }

            void toggleDashboard() {
                show_dashboard_ = true;
                show_markets_ = false;
            }

            void toggleMarkets() {
                show_markets_ = true;
                show_dashboard_ = false;
            }

            bool show_dashboard_ = true;
            bool show_markets_ = false;
    };
}