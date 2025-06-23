#pragma once

#include <string>
#include <utils/date_utils.h>

namespace BetfairAPI::BettingType {
    class ItemDescription {
        public:
            ItemDescription() = default;
            ~ItemDescription() = default;
            ItemDescription(const ItemDescription& other) = default;
            ItemDescription(ItemDescription&& other) noexcept = default;
            ItemDescription& operator=(const ItemDescription& other) = default;
            ItemDescription& operator=(ItemDescription&& other) noexcept = default;

            void setEventTypeDesc(const std::string& s);
            void setEventDesc(const std::string& s);
            void setMarketDesc(const std::string& s);
            void setMarketType(const std::string& s);
            void setMarketStartTime(BetfairAPI::Utils::Date time);
            void setRunnerDesc(const std::string& s);
            void setNumberOfWinners(int n);
            void setEachWayDivisor(double n);

            const std::string& getEventTypeDesc() const;
            const std::string& getEventDesc() const;
            const std::string& getMarketDesc() const;
            const std::string& getMarketType() const;
            const BetfairAPI::Utils::Date& getMarketStartTime() const;
            const std::string& getRunnerDesc() const;
            int getNumberOfWinners() const;
            double getEachWayDivisor() const;

        private:
            std::string event_type_desc_;
            std::string event_desc_;
            std::string market_desc_;
            std::string market_type_;
            BetfairAPI::Utils::Date market_start_time_;
            std::string runner_desc_;
            int number_of_winners_;
            double each_way_divisor_;
    };
}