#include "item_description.h"

namespace BetfairAPI::BettingType {

    void ItemDescription::setEventTypeDesc(const std::string& s) { 
        event_type_desc_ = s; 
    }

    void ItemDescription::setEventDesc(const std::string& s) { 
        event_desc_ = s; 
    }

    void ItemDescription::setMarketDesc(const std::string& s) { 
        market_desc_ = s; 
    }

    void ItemDescription::setMarketType(const std::string& s) { 
        market_type_ = s; 
    }

    void ItemDescription::setMarketStartTime(BetfairAPI::Utils::Date time) { 
        market_start_time_ = time; 
    }

    void ItemDescription::setRunnerDesc(const std::string& s) { 
        runner_desc_ = s; 
    }

    void ItemDescription::setNumberOfWinners(int n) { 
        number_of_winners_ = n; 
    }

    void ItemDescription::setEachWayDivisor(double n) { 
        each_way_divisor_ = n; 
    }
    const std::string& ItemDescription::getEventTypeDesc() const { 
        return event_type_desc_; 
    }

    const std::string& ItemDescription::getEventDesc() const { 
        return event_desc_; 
    }

    const std::string& ItemDescription::getMarketDesc() const { 
        return market_desc_; 
    }

    const std::string& ItemDescription::getMarketType() const { 
        return market_type_; 
    }

    const BetfairAPI::Utils::Date& ItemDescription::getMarketStartTime() const { 
        return market_start_time_; 
    }

    const std::string& ItemDescription::getRunnerDesc() const { 
        return runner_desc_; 
    }

    int ItemDescription::getNumberOfWinners() const { 
        return number_of_winners_; 
    }

    double ItemDescription::getEachWayDivisor() const { 
        return each_way_divisor_; 
    }
}