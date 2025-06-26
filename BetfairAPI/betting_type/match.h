#pragma once

#include <string>

#include "utils/date_utils.h"
#include "betting_enum/side.hpp"

namespace BetfairAPI::BettingType {
    class Match {
        public:
            Match(BetfairAPI::BettingEnum::Side side, double price, double size,
                std::string_view bet_id, std::string_view match_id, BetfairAPI::Utils::Date match_date);
            Match() = default;
            ~Match() = default;
            Match(const Match&) = default;
            Match(Match&&) noexcept = default;
            Match& operator=(const Match&) = default;
            Match& operator=(Match&&) noexcept = default;

            BetfairAPI::BettingEnum::Side getSide() const;
            double getPrice() const;
            double getSize() const;
            std::string getBetId() const;
            std::string getMatchId() const;
            BetfairAPI::Utils::Date getMatchDate() const;

        private:
            BetfairAPI::BettingEnum::Side side_;
            double price_;
            double size_;
            std::string bet_id_;
            std::string match_id_;
            BetfairAPI::Utils::Date match_date_;
    };
}