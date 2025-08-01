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

    struct VenueFilter : public OptionFilter {
        VenueFilter(BetfairAPI::BettingType::VenueResult venue, bool selected)
            : venue_result(std::move(venue)), selected(selected) {};

        BetfairAPI::BettingType::VenueResult venue_result;
        mutable bool selected = false;

        std::string getName() const {return venue_result.venue;};
        std::string getId() const {return venue_result.venue;};
    };

    struct CountryCodeFilter : public OptionFilter {
        CountryCodeFilter(BetfairAPI::BettingType::CountryCodeResult country, bool selected)
            : country_result(std::move(country)), selected(selected) {};

        BetfairAPI::BettingType::CountryCodeResult country_result;
        mutable bool selected = false;

        std::string getName() const {return country_result.countryCode;};
        std::string getId() const {return country_result.countryCode;};
    };
}