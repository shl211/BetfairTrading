#pragma once

#include <string>

#include "competition.h"

namespace BetfairAPI::BettingType {
    class CompetitionResult {
        public:
            CompetitionResult(Competition competition,int market_count, std::string_view competition_region);
            CompetitionResult() = default;
            ~CompetitionResult() = default;
            CompetitionResult(const CompetitionResult&) = default;
            CompetitionResult(CompetitionResult&&) noexcept = default;
            CompetitionResult& operator=(const CompetitionResult&) = default;
            CompetitionResult& operator=(CompetitionResult&&) noexcept = default;
            
            friend std::ostream& operator<<(std::ostream& os, const CompetitionResult& competition);

            const Competition& getCompetition() const;
            int getMarketCount() const;
            std::string getCompetitionRegion() const;

        private:
            Competition competition_;
            int market_count_;
            std::string competition_region_;
    };
}