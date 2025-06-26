#include "match.h"

namespace BetfairAPI::BettingType {
    Match::Match(BetfairAPI::BettingEnum::Side side, double price, double size,
                std::string_view bet_id, std::string_view match_id, BetfairAPI::Utils::Date match_date)
        : side_(side), price_(price), size_(size), bet_id_(bet_id),
            match_id_(match_id), match_date_(std::move(match_date)) {}

    BetfairAPI::BettingEnum::Side Match::getSide() const {
        return side_;
    }

    double Match::getPrice() const {
        return price_;
    }

    double Match::getSize() const {
        return size_;
    }

    std::string Match::getBetId() const {
        return std::string(bet_id_);
    }

    std::string Match::getMatchId() const {
        return std::string(match_id_);
    }

    BetfairAPI::Utils::Date Match::getMatchDate() const {
        return match_date_;
    }
}