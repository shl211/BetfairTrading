#ifndef COMPETITION_RESULT_H
#define COMPETITION_RESULT_H

#include <string>

namespace BetfairAPI {
    class CompetitionResult {
    public:
        CompetitionResult(int competition_id,std::string competition_name, int market_count, std::string competition_region);
        ~CompetitionResult();
        CompetitionResult(const CompetitionResult&);
        CompetitionResult(CompetitionResult&&) noexcept;
        CompetitionResult& operator=(const CompetitionResult&);
        CompetitionResult& operator=(CompetitionResult&&) noexcept;
        
        
        friend std::ostream& operator<<(std::ostream& os, const CompetitionResult& res);

    private:
        int competition_id_;
        std::string competition_name_;
        int market_count_;
        std::string competition_region_;
    };
}

#endif