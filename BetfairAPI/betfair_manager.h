#ifndef BETFAIR_MANAGER_H
#define BETFAIR_MANAGER_H

#include <nlohmann/json.hpp>
#include "betting_type/market_filter.h"
#include "betting_type/event_type_results.h"
#include "betting_type/competition_result.h"
#include "betting_type/event_result.h"
#include "betting_type/market_type_result.h"
#include "betting_type/time_range_result.h"
#include "betting_enum/time_granularity.hpp"

namespace BetfairAPI {
    class BetfairManager {
    
    public:
        BetfairManager(std::string username, std::string password, std::string api_key);
        BetfairManager(const BetfairManager&) = delete;
        BetfairManager(BetfairManager&& other) noexcept;
        BetfairManager& operator=(const BetfairManager&) = delete;
        BetfairManager& operator=(BetfairManager&&) noexcept;
        ~BetfairManager();
    
        double getAccountBalance() const;
        std::vector<BettingType::EventTypeResults> listEventTypes(const BettingType::MarketFilter& mf,const std::string& locale="en") const;
        std::vector<BettingType::CompetitionResult> listCompetitions(const BettingType::MarketFilter& mf,const std::string& locale="en") const;
        std::vector<BettingType::EventResult> listEvents(const BettingType::MarketFilter& mf,const std::string& locale="en") const;
        std::vector<BettingType::MarketTypeResult> listMarketTypes(const BettingType::MarketFilter& mf, const std::string& locale="en") const;
        std::vector<BettingType::TimeRangeResult> listTimeRanges(const BettingType::MarketFilter& mf, BettingEnum::TimeGranularity granularity) const;

    private:
        std::string session_token_;
        std::string application_token_;
    
        double balance_;
        double discount_rate_;
        double exposure_;
        double exposure_limit_;
    
        void assignAccountInformation(const nlohmann::json& account_balance_response);
    };
}

#endif