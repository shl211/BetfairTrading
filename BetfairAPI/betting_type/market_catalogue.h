#pragma once

#include <string>
#include <vector>
#include "utils/date_utils.h"
#include "market_description.h"
#include "runner_catalog.h"
#include "event_type.h"
#include "competition.h"
#include "event.h"

namespace BetfairAPI::BettingType {
    class MarketCatalogue {
        public:
            MarketCatalogue(std::string market_id,std::string market_name,
                        BetfairAPI::Utils::Date market_start_time, MarketDescription description,
                        double total_matched, std::vector<RunnerCatalog> runners,
                        EventType event_type,Competition competition,Event event);
            ~MarketCatalogue() = default;
            MarketCatalogue(const MarketCatalogue&) = default;
            MarketCatalogue(MarketCatalogue&&) noexcept = default;
            MarketCatalogue& operator=(const MarketCatalogue&) = default;
            MarketCatalogue& operator=(MarketCatalogue&&) noexcept = default;

            const std::string& market_id() const;
            const std::string& market_name() const;
            const BetfairAPI::Utils::Date& market_start_time() const;
            const MarketDescription& description() const;
            double total_matched() const;
            const std::vector<RunnerCatalog>& runners() const;
            const EventType& event_type() const;
            const Competition& competition() const;
            const Event& event() const;

        private:
            std::string market_id_;
            std::string market_name_;
            BetfairAPI::Utils::Date market_start_time_;
            MarketDescription description_;
            double total_matched_;
            std::vector<RunnerCatalog> runners_;
            EventType event_type_;
            Competition competition_;
            Event event_;

    };
}