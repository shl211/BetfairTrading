#pragma once

#include <memory>
#include <optional>
#include <vector>
#include <iostream>
#include "imgui.h"
#include "current_order_table.h"
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

                if (ImGui::Button("Dashboard")) {}
                ImGui::SameLine();
                if (ImGui::Button("Orders")) {}
                ImGui::SameLine();
                if (ImGui::Button("Positions")) {}
                ImGui::SameLine();

                ImGui::End();
            }

            void renderMainContent(std::weak_ptr<BetfairAPI::BetfairManager> manager) {
                ImGui::SetNextWindowPos(ImVec2(0, 40));
                ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x,
                                                ImGui::GetIO().DisplaySize.y - 40 - 30)); // leave space

                ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse |
                                        ImGuiWindowFlags_NoMove |
                                        ImGuiWindowFlags_NoResize |
                                        ImGuiWindowFlags_NoBringToFrontOnFocus;

                ImGui::Begin("MainContent", nullptr, flags);
                
                ImGui::Text("Current Orders on Betfair Exchange (Total: %d)", current_order_table_.currentOrderTotal());
                
                ImGui::SameLine();
                if(ImGui::Button("Refresh")) {
                    current_order_table_.refresh();
                }

                current_order_table_.render(manager);

                ImGui::Separator();
                ImGui::Text("You can add charts, order book, positions here.");

                ImGui::End();
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
            std::vector<BetfairAPI::BettingType::CurrentOrderSummary> cached_current_order_summary_;
            GUI::CurrentOrderTable current_order_table_;
    };
}