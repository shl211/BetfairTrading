#pragma once

#include <string>
#include <vector>

#include "betting_enum/market_betting_type.hpp"
#include "betting_enum/order_status.hpp"
#include "time_range.h"

namespace BetfairAPI::BettingType {
    class MarketFilter {
        public:
            MarketFilter();
            ~MarketFilter() = default;
            MarketFilter(const MarketFilter&) = default;
            MarketFilter(MarketFilter&&) noexcept = default;
            MarketFilter& operator=(const MarketFilter&) = default;
            MarketFilter& operator=(MarketFilter&&) noexcept = default;

            void setQuery(std::string_view text_query);
            void addEventTypeId(std::string_view event_type_id);
            void addEventId(std::string_view event_id);
            void addCompetitionId(std::string_view competition_id);
            void addMarketId(std::string_view market_id);
            void addVenue(std::string_view venue);
            void setBspOnly(bool bsp_only);
            void setTurnInPlayEnabled(bool turn_in_play_enabled);
            void setInPlayOnly(bool in_play_only);
            void addMarketBettingType(BetfairAPI::BettingEnum::MarketBettingType market_betting_type);
            void addMarketCountry(std::string_view market_countries);
            void addMarketTypeCode(std::string_view market_type_code);
            void setMarketStartTime(TimeRange time_range);
            void addOrder(BetfairAPI::BettingEnum::OrderStatus order);
            void addRaceType(std::string_view race_type);

            std::string getQuery() const;
            const std::vector<std::string>& getEventTypeIds() const;
            const std::vector<std::string>& getEventIds() const;
            const std::vector<std::string>& getCompetitionIds() const;
            const std::vector<std::string>& getMarketIds() const;
            const std::vector<std::string>& getVenues() const;
            bool isBspOnly() const;
            bool isTurnInPlayEnabled() const;
            bool isInPlayOnly() const;
            const std::vector<BetfairAPI::BettingEnum::MarketBettingType>& getMarketBettingTypes() const;
            const std::vector<std::string>& getMarketCountries() const;
            const std::vector<std::string>& getMarketTypeCodes() const;
            const TimeRange& getMarketStartTime() const;
            const std::vector<BetfairAPI::BettingEnum::OrderStatus>& getOrders() const;
            const std::vector<std::string>& getRaceTypes() const;

        private:
            std::string text_query_;
            std::vector<std::string> event_type_ids_;
            std::vector<std::string> event_ids_;
            std::vector<std::string> competition_ids_;
            std::vector<std::string> market_ids_;
            std::vector<std::string> venues_ids_;
            bool bsp_only_;
            bool turn_in_play_enabled_;
            bool in_play_only_;
            std::vector<BetfairAPI::BettingEnum::MarketBettingType> market_betting_types_;
            std::vector<std::string> market_countries_;
            std::vector<std::string> market_type_codes_;
            TimeRange market_start_time_;
            std::vector<BetfairAPI::BettingEnum::OrderStatus> with_orders_;
            std::vector<std::string> race_types_;
    };
}