#include <ostream>
#include "competition_result.h"
namespace BetfairAPI::BettingType {
    CompetitionResult::CompetitionResult(Competition competition,int market_count, std::string_view competition_region) 
        : competition_(std::move(competition)), market_count_(market_count), competition_region_(competition_region) {}

    const Competition& CompetitionResult::getCompetition() const {
        return competition_;
    }

    std::ostream& operator<<(std::ostream& os, const CompetitionResult& competition) {
        os << "Competition" << competition.competition_
            << ", marketCount=" << competition.market_count_
            << ", competitionRegion=" << competition.competition_region_
            << "}";
        return os;
    }

    int CompetitionResult::getMarketCount() const {
        return market_count_;
    }

    std::string CompetitionResult::getCompetitionRegion() const {
        return competition_region_;
    }
}