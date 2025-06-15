#include "match.h"

namespace BetfairAPI::BettingType {
    Match::Match(BetfairAPI::BettingEnum::Side side, double price, double size,
                std::string_view bet_id, std::string_view match_id, BetfairAPI::Utils::Date match_date)
        : side_(side), price_(price), size_(size), bet_id_(bet_id),
            match_id_(match_id), match_date_(std::move(match_date)) {}

    BetfairAPI::BettingEnum::Side Match::get_side() const {
        return side_;
    }

    double Match::get_price() const {
        return price_;
    }

    double Match::get_size() const {
        return size_;
    }

    std::string Match::get_bet_id() const {
        return std::string(bet_id_);
    }

    std::string Match::get_match_id() const {
        return std::string(match_id_);
    }

    BetfairAPI::Utils::Date Match::get_match_date() const {
        return match_date_;
    }
}