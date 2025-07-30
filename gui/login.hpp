#pragma once

#include "BetfairAPI/manager.h"
#include "imgui.h"
#include <memory>

namespace GUI {
    class LoginFrame {
        public:
            LoginFrame() = default;
            ~LoginFrame() = default;

            void render() {
                ImGui::SetNextWindowSize(ImVec2(300, 200), ImGuiCond_Always);
                ImGui::SetNextWindowPos(ImGui::GetMainViewport()->GetCenter(),
                            ImGuiCond_Always, ImVec2(0.5f, 0.5f));
                
                ImGui::Begin("Login", nullptr,
                            ImGuiWindowFlags_NoResize |
                            ImGuiWindowFlags_NoCollapse |
                            ImGuiWindowFlags_NoMove);

                ImGui::NewLine();
                ImGui::InputText("Username", username_, IM_ARRAYSIZE(username_));
                ImGui::InputText("Password", password_, IM_ARRAYSIZE(password_), ImGuiInputTextFlags_Password);
                ImGui::InputText("API Token", api_token_, IM_ARRAYSIZE(api_token_));

                if(ImGui::Button("Debug Skip Login")) {
                    success_ = true;
                }

                if (ImGui::Button("Login")) {
                    try {
                        betfair_manager_ = std::make_shared<BetfairAPI::BetfairManager>(username_,password_,api_token_);
                        success_ = true;
                    }
                    catch (...) {
                        ImGui::Text("Login failed. Try again");
                    }
                }
                ImGui::SameLine();
                if (ImGui::Button("Exit")) {
                    exit(0);
                }
                ImGui::End();
            }

            bool isLoggedIn() const {return success_;};
            std::weak_ptr<BetfairAPI::BetfairManager> BetfairManager() const noexcept {return betfair_manager_;};

        private:
            bool success_ = false;
            char username_[64] = "";
            char password_[64] = "";
            char api_token_[64] = "";
            std::shared_ptr<BetfairAPI::BetfairManager> betfair_manager_ = nullptr;
    };
}