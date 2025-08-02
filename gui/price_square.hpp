#pragma once

#include <vector>
#include <string>
#include "imgui.h"
#include "BetfairAPI/manager.h"

namespace GUI {
    class PriceSizeSquare {
        public:
            void render() {
                ImGui::Text("%s",runner_name_.c_str());
                ImGui::SameLine();
                ImGui::Text("Back");
                
                for(int i = ladder_levels_to_show_ - 1; i >= 0; --i) {
                    ImGui::SameLine();
                    float price = (price_size_data_.availableToBack.size() >= i+1) 
                                ? price_size_data_.availableToBack[i].price 
                                : 0.0f;

                    if (price == 0.0f) {
                        ImGui::TextColored(green_, "-");
                    }
                    else {
                        ImGui::TextColored(green_, "%.2f", price);
                    }
                }

                for(int i = 0; i < ladder_levels_to_show_; ++i) {
                    ImGui::SameLine();
                    float price = (price_size_data_.availableToLay.size() >= i+1) 
                                ? price_size_data_.availableToLay[i].price 
                                : 0.0f;

                    if (price == 0.0f) {
                        ImGui::TextColored(red_, "-");
                    }
                    else {
                        ImGui::TextColored(red_, "%.2f", price);
                    }
                }

                ImGui::SameLine();
                ImGui::Text("Lay");
            }

            void updatePriceSizeData(BetfairAPI::BettingType::ExchangePrices exp) {
                price_size_data_ = exp;
            }

            void updateRunnerName(const std::string& runner_name) {
                runner_name_ = runner_name;
            }

        private:
            BetfairAPI::BettingType::ExchangePrices price_size_data_;
            std::string runner_name_ = "N/A";
            const int ladder_levels_to_show_ = 3;
            ImVec4 green_ = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
            ImVec4 red_ = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);

    };
}