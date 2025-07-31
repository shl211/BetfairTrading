#pragma once

#include "BetfairAPI/manager.h"
#include "imgui.h"
#include <memory>

namespace {
    void safe_string_copy(char* dest, size_t dest_size, const std::string& src) {
        size_t len = std::min(src.size(), dest_size - 1);
        src.copy(dest, len);
        dest[len] = '\0';
    }
}

#include <iostream>
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
                
                //ease development
                if (ImGui::Button("Dev Skip Login")) {
                    // Convert env vars to strings first (handles nulls safely)
                    std::string env_user = getenv("USERNAME") ? getenv("USERNAME") : "";
                    std::string env_pass = getenv("PASSWORD") ? getenv("PASSWORD") : "";
                    std::string env_token = getenv("APIKEYDELAY") ? getenv("APIKEYDELAY") : "";
                    
                    safe_string_copy(username_, sizeof(username_), env_user);
                    safe_string_copy(password_, sizeof(password_), env_pass);
                    safe_string_copy(api_token_, sizeof(api_token_), env_token);
                    
                    try {
                        betfair_manager_ = std::make_shared<BetfairAPI::BetfairManager>(username_,password_,api_token_);
                        success_ = true;
                    }
                    catch (const std::exception& ex) {
                        ImGui::Text("Login failed: %s", ex.what());
                    }
                }
                
                if (ImGui::Button("Login")) {
                    try {
                        betfair_manager_ = std::make_shared<BetfairAPI::BetfairManager>(username_,password_,api_token_);
                        success_ = true;
                    }
                    catch (const std::exception& ex) {
                        std::cout << ex.what();
                        ImGui::Text("Login failed: %s", ex.what());
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