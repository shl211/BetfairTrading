#include "CompetitionResult.h"

#include <ostream>

namespace BetfairAPI {
    CompetitionResult::CompetitionResult(int competition_id,std::string competition_name,
        int market_count, std::string competition_region) :
            competition_id_(competition_id),
            competition_name_(std::string(competition_name)),
            market_count_(market_count),
            competition_region_(std::string(competition_name_)) {};

    CompetitionResult::~CompetitionResult() {};

    CompetitionResult::CompetitionResult(const CompetitionResult& other) : 
        competition_id_(other.competition_id_),
        competition_name_(other.competition_name_),
        competition_region_(other.competition_region_),
        market_count_(other.market_count_) {};

    CompetitionResult::CompetitionResult(CompetitionResult&& other) noexcept : 
        competition_id_(std::move(other.competition_id_)),
        competition_name_(std::move(other.competition_name_)),
        competition_region_(std::move(other.competition_region_)),
        market_count_(std::move(other.market_count_)) {
        
        //reset state in other
        other.market_count_ = 0;
        other.competition_id_ = 0;
    }

    CompetitionResult& CompetitionResult::operator=(const CompetitionResult& other) {
        if (this != &other) {
            competition_id_ = other.competition_id_;
            competition_name_ = other.competition_name_;
            competition_region_ = other.competition_region_;
            market_count_ = other.market_count_;
        }
    
        return *this;
    }

    CompetitionResult& CompetitionResult::operator=(CompetitionResult&& other) noexcept {
        if (this != &other) {
            competition_id_ = other.competition_id_;
            competition_name_ = std::move(other.competition_name_);
            competition_region_ = std::move(other.competition_region_);
            market_count_ = other.market_count_;
        }
    
        return *this;
    }

    std::ostream& operator<<(std::ostream& os, const CompetitionResult& res) {
        os << "Competition ID: " << res.competition_id_ << "(" << res.competition_name_ << ")";

        return os;
    }


}