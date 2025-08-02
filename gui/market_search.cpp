#include <iostream>
#include "market_search.h"

namespace GUI {
    namespace {
        //requires getName() and getId() methods for FilterT and contain selected non-const bool
        template<typename FilterT>
        void renderFilterOptions(
            const std::string& filter_id,
            std::vector<FilterT>& filter_options,
            std::set<std::string>& inout_selected_ids
        ) {
            if (ImGui::TreeNode(filter_id.c_str())) {
                std::string child_id = "##" + filter_id + "_scroll";
                ImGui::BeginChild(child_id.c_str(), ImVec2(0, 150), true, ImGuiWindowFlags_HorizontalScrollbar);

                ImGuiListClipper clipper;
                clipper.Begin(static_cast<int>(filter_options.size()));
                while (clipper.Step()) {
                    for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++) {
                        auto& filter_opt = filter_options[i];
                        
                        // Assuming state change only occurs here
                        if(ImGui::Checkbox(filter_opt.getName().c_str(), &filter_opt.selected)) {
                            if(filter_opt.selected) {
                                inout_selected_ids.insert(filter_opt.getId());
                            }
                            else {
                                inout_selected_ids.erase(filter_opt.getId());
                            }
                        }
                    }
                }
                clipper.End();

                ImGui::EndChild();
                ImGui::TreePop();
            }
        }

        template<typename FilterT>
        void getDataFromBetfair(
            std::weak_ptr<BetfairAPI::BetfairManager> manager,
            std::vector<FilterT>& inout_filters
        ) {
            bool filter_need_loading = inout_filters.empty();
            if(auto m = manager.lock(); m && filter_need_loading) {
                //this mf needed to prevent api failure
                BetfairAPI::BettingType::MarketFilter mf;
                mf.inPlayOnly = false;
                        
                auto data_list = [&]() {
                    //if editing this: have you ensured filters are being processed and included in api call of future queries in searchMarkets? 
                    if constexpr (std::is_same_v<FilterT, EventTypeFilter>)         return m->getEventTypes(std::move(mf));
                    else if constexpr (std::is_same_v<FilterT, MarketTypeFilter>)   return m->getMarketTypeResults(std::move(mf));
                    else if constexpr (std::is_same_v<FilterT, CompetitionFilter>)  return m->getCompetitions(std::move(mf));
                    else if constexpr (std::is_same_v<FilterT, VenueFilter>)        return m->getVenues(std::move(mf));
                    else if constexpr (std::is_same_v<FilterT, CountryCodeFilter>)  return m->getCountries(std::move(mf));
                }();

                inout_filters.reserve(data_list.size());
                for (auto& data : data_list) {
                    inout_filters.emplace_back(data, false);
                }
            }
        }

        BetfairAPI::BettingType::ExchangePrices lookupBackLayPrice(long runner_id,const BetfairAPI::BettingType::MarketBook& m_book) {
            auto& runners = m_book.runners;

            for(auto& runner : runners) {
                if(runner.selectionId == runner_id) {
                    return *runner.ex;
                }
            }

            return {};
        }
    }

    void MarketSearch::render(std::weak_ptr<BetfairAPI::BetfairManager> manager) {
        ImGui::Begin("Add Market", nullptr, ImGuiWindowFlags_AlwaysVerticalScrollbar);

        ImGui::InputText("##SearchInput", market_search_, IM_ARRAYSIZE(market_search_));

        ImGui::SameLine();
        if(ImGui::Button("Search")) {
            searchMarkets(manager);
        }
        
        //filter options
        //if editing this: have you loaded all filters in loadFilterOptions?
        loadFilterOptions(manager);
        renderFilterOptions("Competition",competitions_,competition_ids_);
        renderFilterOptions("Event Type",event_types_,event_type_ids_);
        renderFilterOptions("Market Type",market_types_,market_type_ids_);
        renderFilterOptions("Countries",country_codes_,country_codes_ids_);
        renderFilterOptions("Venues",venue_,venue_ids_);


        displayTable(manager);
        ImGui::End();
    }

    void MarketSearch::searchMarkets(std::weak_ptr<BetfairAPI::BetfairManager> manager) {
        if(auto m = manager.lock(); m) {
            BetfairAPI::BettingType::MarketFilter filter;
            if(auto s = std::string(market_search_); !s.empty()) {
                filter.textQuery = std::move(s);
            }

            //if editing this: have you displayed the available options in render?
            filter.eventTypeIds = event_type_ids_;
            filter.competitionIds = competition_ids_;
            filter.marketTypeCodes = market_type_ids_;
            filter.marketCountries = country_codes_ids_;
            filter.venues = venue_ids_;

            using MarketProjection = BetfairAPI::BettingEnum::MarketProjection;
            auto market_cat = m->getMarketCatalogues(
                std::move(filter),
                {MarketProjection::EVENT,
                    MarketProjection::EVENT_TYPE,
                    MarketProjection::RUNNER_DESCRIPTION,
                    MarketProjection::MARKET_START_TIME
                }
            );

            market_info_.clear();
            market_info_.reserve(market_cat.size());
            for(auto& m_cat : market_cat) {
                market_info_.emplace_back(std::move(m_cat));
            }
        }
    }

    void MarketSearch::displayTable(std::weak_ptr<BetfairAPI::BetfairManager> manager) {
        auto flags = ImGuiTableFlags_Resizable | ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg ;

        if (ImGui::BeginTable("MyTable", 6, flags)) {
            ImGui::TableSetupColumn("Event");
            ImGui::TableSetupColumn("Event Type");
            ImGui::TableSetupColumn("Market");
            ImGui::TableSetupColumn("Total Matched");
            ImGui::TableSetupColumn("Market Start Time");
            
            ImGui::TableHeadersRow();
            
            for (int row = 0; row < market_info_.size(); row++) {
                auto& selected_market_info = market_info_[row];
                auto& info = selected_market_info.market_catalogue_;

                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);

                //make whole row selectable
                bool row_selected = false;
                std::string label = "##row_market_search_table" + std::to_string(row);
                if (ImGui::Selectable(label.c_str(), &row_selected, ImGuiSelectableFlags_SpanAllColumns)) {
                    // Toggle expansion
                    selected_market_info.expanded_ = !selected_market_info.expanded_;
                }

                ImGui::SameLine();
                ImGui::Text("%s", info.event ? info.event->name.c_str() : "N/A");

                ImGui::TableSetColumnIndex(1);
                ImGui::Text("%s", info.eventType ? info.eventType->name.c_str() : "N/A");

                ImGui::TableSetColumnIndex(2);
                ImGui::Text("%s", !info.marketName.empty() ? info.marketName.c_str() : "N/A");

                ImGui::TableSetColumnIndex(3);
                ImGui::Text("%.2f", info.totalMatched);

                ImGui::TableSetColumnIndex(4);
                ImGui::Text("%s", info.marketStartTime ? info.marketStartTime->getIsoString().c_str() : "N/A");
            
                if (selected_market_info.expanded_) {
                    renderExtraInfo(row,manager);
                }
            }

            ImGui::EndTable();
        }
    }

    void MarketSearch::renderExtraInfo(int row, std::weak_ptr<BetfairAPI::BetfairManager> manager) {

        // Add a new row for the expanded info
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        
        auto& selected_market_info = market_info_[row];
        auto& market_cat = selected_market_info.market_catalogue_;
        
        if(auto m = manager.lock(); m && market_cat.runners.empty()) {
            BetfairAPI::BettingType::MarketFilter filter;
            filter.marketIds.insert(market_cat.marketId);//this is a global identifier
            
            auto updated_m_cat_list = m->getMarketCatalogues(
                std::move(filter),
                {BetfairAPI::BettingEnum::MarketProjection::RUNNER_DESCRIPTION}
            );
            
            assert(std::size(updated_m_cat_list) == 1);//should only get one from global id
            
            //replace only runners for now
            market_cat.runners = std::move(updated_m_cat_list[0].runners);
        }

        if(auto m = manager.lock(); m && !selected_market_info.market_book_) {
            //load market book if not already done so
            BetfairAPI::BettingType::PriceProjection pp;
            pp.virtualise = true;
            pp.priceData.insert(BetfairAPI::BettingEnum::PriceData::EX_BEST_OFFERS);

            auto data = m->getMarketBook(
                {market_cat.marketId},
                std::move(pp)
            );

            assert(std::size(data) == 1);
            
            selected_market_info.market_book_ = std::make_unique<BetfairAPI::BettingType::MarketBook>(std::move(data[0]));

            //instantiate pricing widget upon new market book data
            if(!selected_market_info.price_size_widget_) {
                selected_market_info.price_size_widget_ = std::make_unique<PriceSizeSquare>();
            }
        }
        
        ImGui::Text("Runners: ");
        
        //need to create a nerw class with new frame rendering
        for(auto& runner : market_cat.runners) {
            if(selected_market_info.price_size_widget_) {
                auto data = lookupBackLayPrice(runner.selectionId,*selected_market_info.market_book_);
                
                //refactor so update occurs upon state change??
                selected_market_info.price_size_widget_->updatePriceSizeData(std::move(data));
                selected_market_info.price_size_widget_->updateRunnerName(runner.runnerName);

                selected_market_info.price_size_widget_->render();
            }
        }
    }
    
    void MarketSearch::loadFilterOptions(std::weak_ptr<BetfairAPI::BetfairManager> manager) {
        //if editing this: have you defined the correct Filter in the if constepxr of getDataFromBetfair for correct api call?
        getDataFromBetfair<CompetitionFilter>(manager,competitions_);
        getDataFromBetfair<EventTypeFilter>(manager,event_types_);
        getDataFromBetfair<MarketTypeFilter>(manager,market_types_);
        getDataFromBetfair<CountryCodeFilter>(manager,country_codes_);
        getDataFromBetfair<VenueFilter>(manager,venue_);
    }

}