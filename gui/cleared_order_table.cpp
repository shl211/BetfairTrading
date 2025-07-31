#include "cleared_order_table.h"
#include <iostream>
#include <algorithm>


namespace GUI {
    namespace {
        constexpr int BET_ID_COL = 0;
        constexpr int EVENT_COL = 1;
        constexpr int RUNNER_COL = 2;
        constexpr int SIDE_COL = 3;
        constexpr int OUTCOME_COL = 4;
        constexpr int PROFIT_COL = 5;
    }


    void ClearedOrderTable::render(std::weak_ptr<BetfairAPI::BetfairManager> manager) {
        if(auto m = manager.lock(); update_current_order_summary_) {
            bool include_item_description = true;
            cached_order_summary_ = m->getClearedOrders(
                BetfairAPI::BettingEnum::BetStatus::SETTLED,
                std::nullopt,
                {},
                {},
                {},
                {},
                {},
                std::nullopt,
                std::nullopt,
                include_item_description
            );
            update_current_order_summary_ = false;
        }

        auto flags = ImGuiTableFlags_Resizable | ImGuiTableFlags_Borders;

        if (ImGui::BeginTable("MyTable", 6, flags)) {
            ImGui::TableSetupColumn("Bet ID");
            ImGui::TableSetupColumn("Event");
            ImGui::TableSetupColumn("Runner");
            ImGui::TableSetupColumn("Side");
            ImGui::TableSetupColumn("Outcome");
            ImGui::TableSetupColumn("Profit");
            
            ImGui::TableHeadersRow();
            
            for (auto& order_summary : cached_order_summary_) {
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(BET_ID_COL);
                ImGui::Text("%s", order_summary.betId ? order_summary.betId->c_str() : "N/A");
                
                auto items = order_summary.itemDescription;
                bool itemExists = items.has_value();
                ImGui::TableSetColumnIndex(EVENT_COL);
                ImGui::Text("%s", items && items->eventDesc ? items->eventDesc->c_str() : "N/A");

                ImGui::TableSetColumnIndex(RUNNER_COL);
                ImGui::Text("%s", items && items-> runnerDesc ? items->runnerDesc->c_str() : "N/A");

                ImGui::TableSetColumnIndex(SIDE_COL);
                ImGui::Text("%s", *order_summary.side == BetfairAPI::BettingEnum::Side::BACK ? "Back" : "Lay");

                ImGui::TableSetColumnIndex(OUTCOME_COL);
                ImGui::Text("%s", order_summary.betOutcome ? order_summary.betOutcome->c_str() : "N/A");

                ImGui::TableSetColumnIndex(PROFIT_COL);
                ImGui::Text("%.2f", order_summary.profit ? *order_summary.profit : 0);
            }
            ImGui::EndTable();
        }
    }
}