#include "current_order_table.h"
#include <iostream>


namespace GUI {
    void CurrentOrderTable::render(std::weak_ptr<BetfairAPI::BetfairManager> manager) {
        if(auto m = manager.lock(); update_current_order_summary_) {
            cached_current_order_summary_ = m->getCurrentOrders();
            update_current_order_summary_ = false;
        }

        auto flags = ImGuiTableFlags_Resizable | ImGuiTableFlags_Borders;

        if (ImGui::BeginTable("MyTable", 6, flags)) {
            ImGui::TableSetupColumn("Bet ID");
            ImGui::TableSetupColumn("Event");
            ImGui::TableSetupColumn("Runner");
            ImGui::TableSetupColumn("Side");
            ImGui::TableSetupColumn("Size Matched");
            ImGui::TableSetupColumn("Size Remaining");

            ImGui::TableHeadersRow();

            for (auto& order_summary : cached_current_order_summary_) {
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::Text("%s", order_summary.betId.c_str());

                ImGui::TableSetColumnIndex(1);
                ImGui::Text("%s", eventName(manager,order_summary.marketId).c_str());
                ImGui::TableSetColumnIndex(2);
                ImGui::Text("%s", runnerName(manager,order_summary.marketId,order_summary.selectionId).c_str());
                ImGui::TableSetColumnIndex(3);
                ImGui::Text("%s", order_summary.side == BetfairAPI::BettingEnum::Side::BACK ? "Back" : "Lay");
                ImGui::TableSetColumnIndex(4);
                ImGui::Text("%.2f", *order_summary.sizeMatched);
                ImGui::TableSetColumnIndex(5);
                ImGui::Text("%.2f", *order_summary.sizeRemaining);
                

            }

            ImGui::EndTable();
        }
    }


    void CurrentOrderTable::updateMarketInfo(std::weak_ptr<BetfairAPI::BetfairManager> manager, std::string marketId) {
        BetfairAPI::BettingType::MarketFilter mf;
        mf.marketIds.insert(marketId);

        auto m = manager.lock();
        using MarketProjection = BetfairAPI::BettingEnum::MarketProjection;
        auto market_info = m->getMarketCatalogues(
            std::move(mf),
            {MarketProjection::EVENT,MarketProjection::EVENT_TYPE,MarketProjection::RUNNER_DESCRIPTION}
        );

        assert(std::size(market_info) == 1);

        market_info_cache_[marketId] = std::move(market_info[0]);

        std::cout << ++api_counter_ << "\n";
    }

    std::string CurrentOrderTable::eventName(std::weak_ptr<BetfairAPI::BetfairManager> manager, std::string marketId) {
        //update cache if needed
        if(market_info_cache_.find(marketId) == market_info_cache_.end()) {
            updateMarketInfo(manager,marketId);
        }
        
        auto event = market_info_cache_[marketId].event;

        return event ? event->name : "N/A";
    }

    std::string CurrentOrderTable::runnerName(std::weak_ptr<BetfairAPI::BetfairManager> manager, std::string marketId, long selectionId) {
        //update cache if needed
        if(market_info_cache_.find(marketId) == market_info_cache_.end()) {
            updateMarketInfo(manager,marketId);
        }

        auto runner_info = market_info_cache_[marketId].runners;

        for(auto& runner : runner_info) {
            if(runner.selectionId == selectionId) {
                return runner.runnerName;
            }
        }

        return "N/A";
    }
}