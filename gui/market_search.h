#pragma once

#include <memory>
#include <vector>
#include <string>
#include <set>
#include "imgui.h"
#include "BetfairAPI/manager.h"
#include "option_filter.hpp"

namespace GUI {
    class MarketSearch {
        public:
            void render(std::weak_ptr<BetfairAPI::BetfairManager> manager);

            
            private:
                struct MarketCatalogueSelection {
                    MarketCatalogueSelection(BetfairAPI::BettingType::MarketCatalogue&& m_cat)
                        : market_catalogue_(m_cat) {};
                    BetfairAPI::BettingType::MarketCatalogue market_catalogue_;
                    std::unique_ptr<BetfairAPI::BettingType::MarketBook> market_book_ = nullptr;
                    bool expanded_ = false;
                };
            
                char market_search_[32] = "";
                std::vector<MarketCatalogueSelection> market_info_;

                //store possible filter options
                std::vector<EventTypeFilter> event_types_;
                std::vector<CompetitionFilter> competitions_;
                std::vector<MarketTypeFilter> market_types_;
                std::vector<CountryCodeFilter> country_codes_;
                std::vector<VenueFilter> venue_;

                //active selection of filters
                std::set<std::string> event_type_ids_;
                std::set<std::string> competition_ids_;
                std::set<std::string> market_type_ids_;
                std::set<std::string> country_codes_ids_;
                std::set<std::string> venue_ids_;

                void searchMarkets(std::weak_ptr<BetfairAPI::BetfairManager> manager);
                void displayTable(std::weak_ptr<BetfairAPI::BetfairManager> manager);
                void loadFilterOptions(std::weak_ptr<BetfairAPI::BetfairManager> manager); //does not currently work
                void renderExtraInfo(int row, std::weak_ptr<BetfairAPI::BetfairManager> manager);
    };
}