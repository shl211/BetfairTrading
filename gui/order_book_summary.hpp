#pragma once

#include <vector>
#include <map>
#include <string>
#include <tuple>
#include "imgui.h"
#include "BetfairAPI/manager.h"

namespace GUI {
    class OrderBookSummary {
        public: 
            void insert(long runner_id, std::string runner_name, BetfairAPI::BettingType::ExchangePrices price_data) {
                runner_price_data_[runner_id] = std::make_tuple(std::move(runner_name),std::move(price_data));
            };

            void clear() {
                runner_price_data_.clear();
            };

            void render() {
                auto flags = ImGuiTableFlags_Resizable | ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg ;

                if (ImGui::BeginTable("MyTable", 7, flags)) {
                    ImGui::TableSetupColumn("Runner");
                    ImGui::TableSetupColumn("B3");
                    ImGui::TableSetupColumn("B2");
                    ImGui::TableSetupColumn("B1");
                    ImGui::TableSetupColumn("L1");
                    ImGui::TableSetupColumn("L2");
                    ImGui::TableSetupColumn("L3");

                    ImGui::TableHeadersRow();

                    for (const auto& [runner_id, runner_info] : runner_price_data_) {
                        auto& [runner_name, price_data] = runner_info;
                        ImGui::TableNextRow();
                        ImGui::TableSetColumnIndex(0);
                        ImGui::Text("%s",runner_name.c_str());

                        //back prices
                        for(int i = ladder_levels_to_show_ - 1; i >= 0; --i) {
                            ImGui::TableNextColumn();
                            bool data_is_available = price_data.availableToBack.size() >= i+1;
                            
                            float price = data_is_available 
                                        ? price_data.availableToBack[i].price 
                                        : 0.0f;

                            float size = data_is_available ? price_data.availableToBack[i].size : 0.0f;

                            if (price == 0.0f) {
                                ImGui::TextColored(green_, "-");
                                ImGui::Separator();
                                ImGui::Text("£-");
                            }
                            else {
                                ImGui::TextColored(green_, "%.2f", price);
                                ImGui::Separator();
                                ImGui::Text("£%.2f",size);
                            }
                        }

                        //lay prices
                        for(int i = 0; i < ladder_levels_to_show_; ++i) {
                            ImGui::TableNextColumn();
                            bool data_is_available = price_data.availableToLay.size() >= i+1;
                            
                            float price = data_is_available 
                                        ? price_data.availableToLay[i].price 
                                        : 0.0f;

                            float size = data_is_available ? price_data.availableToLay[i].size : 0.0f;

                            if (price == 0.0f) {
                                ImGui::TextColored(red_, "-");
                                ImGui::Separator();
                                ImGui::Text("£-");
                            }
                            else {
                                ImGui::TextColored(red_, "%.2f", price);
                                ImGui::Separator();
                                ImGui::Text("£%.2f",size);
                            }
                        }

                    }

                    ImGui::EndTable();
                }
            }

            

        private:
            using RunnerId = long;
            using RunnerName = std::string;
            using RunnerInfo = std::tuple<RunnerName,BetfairAPI::BettingType::ExchangePrices>;

            std::map<RunnerId,RunnerInfo> runner_price_data_;
            const int ladder_levels_to_show_ = 3;
            ImVec4 green_ = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
            ImVec4 red_ = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    };
}