#pragma once

#include <string>
#include "BetfairAPI/manager.h"

namespace GUI {

    //all option filters must inherit from here
    struct OptionFilter {
        std::string getName() const {return "";};
        std::string getId() const {return "";};
    };

    struct CompetitionFilter : public OptionFilter {
        CompetitionFilter(BetfairAPI::BettingType::CompetitionResult c, bool selected)
            : comp_result(std::move(c)), selected(selected) {};
        BetfairAPI::BettingType::CompetitionResult comp_result;
        mutable bool selected = false;
        
        std::string getName() const {return comp_result.competition.name;};
        std::string getId() const {return comp_result.competition.id;};
    };

    struct EventTypeFilter : public OptionFilter{
        EventTypeFilter(BetfairAPI::BettingType::EventTypeResult evt, bool selected)
        : ev_result(std::move(evt)), selected(selected) {};
        BetfairAPI::BettingType::EventTypeResult ev_result;
        mutable bool selected = false;

        std::string getName() const {return ev_result.eventType.name;};
        std::string getId() const {return ev_result.eventType.id;};
    };

    struct MarketTypeFilter : public OptionFilter {
        MarketTypeFilter(BetfairAPI::BettingType::MarketTypeResult mtr, bool selected)
            : mtr_result(std::move(mtr)), selected(selected) {};

        BetfairAPI::BettingType::MarketTypeResult mtr_result;
        mutable bool selected = false;

        std::string getName() const {return mtr_result.marketType;};
        std::string getId() const {return mtr_result.marketType;};
    };
}