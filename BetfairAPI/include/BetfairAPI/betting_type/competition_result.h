#pragma once

#include <string>
#include <ostream>
#include "competition.h"

namespace BetfairAPI::BettingType {
    struct CompetitionResult {
        Competition competition;
        int marketCount = 0;
        std::string competitionRegion;
    };

    inline bool operator==(const CompetitionResult& lhs,const CompetitionResult& rhs) {
        return lhs.competition == rhs.competition && 
            lhs.marketCount == rhs.marketCount && 
            lhs.competitionRegion == rhs.competitionRegion;
    }

    inline bool operator!=(const CompetitionResult& lhs,const CompetitionResult& rhs) {
        return !(lhs==rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const CompetitionResult& comp_res) {
        os << "Competition result: " << comp_res.competition << 
            " with market count " << comp_res.marketCount <<
            " located in " << comp_res.competitionRegion;
        return os;
    }
}