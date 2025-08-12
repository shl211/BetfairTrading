#pragma once

#include <string>
#include <optional>
#include <ostream>
#include <optional>

#include "BetfairAPI/date.h"

namespace BetfairAPI::StreamingType {
    struct MarketDefinition {
        std::optional<std::string> id;
        std::optional<std::string> venue;
        std::optional<std::string> raceType;
        std::optional<Date> settledTime;
        std::optional<std::string> timeZone;//
        std::optional<double> eachWayDivisor;
        std::optional<bool> bspMarket;//
        std::optional<bool> turnInPlayEnabled;//
        std::optional<std::string> priceLadderDefinition;
        std::optional<int> keyLineDefinition;
        std::optional<bool> persistenceEnabled;//
        std::optional<double> marketBaseRate;//
        std::optional<std::string> eventId;//
        std::optional<std::string> eventTypeId;
        std::optional<int> numberOfWinners;//
        std::optional<std::string> countryCode;
        std::optional<double> lineMaxUnit;
        std::optional<std::string> bettingType;//
        std::optional<std::string> marketType;//
        std::optional<Date> marketTime;//
        std::optional<Date> suspendTime;//
        std::optional<bool> bspReconciled;//
        std::optional<bool> complete;//
        std::optional<bool> inPlay;//
        std::optional<bool> crossMatching;//
        std::optional<bool> runnersVoidable;//
        std::optional<int> numberOfActiveRunners;//
        std::optional<double> lineMinUnit;
        std::optional<double> betDelay;//
        std::optional<std::string> status;//
        std::vector<std::string> regulators;//
        std::optional<bool> discountAllowed;//
        std::optional<Date> openDate;//
        std::optional<long> version;//
    };

    inline bool operator==(const MarketDefinition& lhs, const MarketDefinition& rhs) {
        return lhs.id == rhs.id &&
                lhs.venue == rhs.venue &&
                lhs.raceType == rhs.raceType &&
                lhs.settledTime == rhs.settledTime &&
                lhs.timeZone == rhs.timeZone &&
                lhs.eachWayDivisor == rhs.eachWayDivisor &&
                lhs.bspMarket == rhs.bspMarket &&
                lhs.turnInPlayEnabled == rhs.turnInPlayEnabled &&
                lhs.priceLadderDefinition == rhs.priceLadderDefinition &&
                lhs.keyLineDefinition == rhs.keyLineDefinition &&
                lhs.persistenceEnabled == rhs.persistenceEnabled &&
                lhs.marketBaseRate == rhs.marketBaseRate &&
                lhs.eventId == rhs.eventId &&
                lhs.eventTypeId == rhs.eventTypeId &&
                lhs.numberOfWinners == rhs.numberOfWinners &&
                lhs.countryCode == rhs.countryCode &&
                lhs.lineMaxUnit == rhs.lineMaxUnit &&
                lhs.bettingType == rhs.bettingType &&
                lhs.marketType == rhs.marketType &&
                lhs.marketTime == rhs.marketTime &&
                lhs.suspendTime == rhs.suspendTime &&
                lhs.bspReconciled == rhs.bspReconciled &&
                lhs.complete == rhs.complete &&
                lhs.inPlay == rhs.inPlay &&
                lhs.crossMatching == rhs.crossMatching &&
                lhs.runnersVoidable == rhs.runnersVoidable &&
                lhs.numberOfActiveRunners == rhs.numberOfActiveRunners &&
                lhs.lineMinUnit == rhs.lineMinUnit &&
                lhs.betDelay == rhs.betDelay &&
                lhs.status == rhs.status &&
                lhs.regulators == rhs.regulators &&
                lhs.discountAllowed == rhs.discountAllowed &&
                lhs.openDate == rhs.openDate &&
                lhs.version == rhs.version;
    }

    inline bool operator!=(const MarketDefinition& lhs, const MarketDefinition& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const MarketDefinition& md) {
        os << "MarketDefinition{";
        os << "id=" << (md.id ? *md.id : "null") << ", ";
        os << "venue=" << (md.venue ? *md.venue : "null") << ", ";
        os << "raceType=" << (md.raceType ? *md.raceType : "null") << ", ";
        os << "settledTime=" << (md.settledTime ? md.settledTime->getIsoString() : "null") << ", ";
        os << "timeZone=" << (md.timeZone ? *md.timeZone : "null") << ", ";
        os << "eachWayDivisor=" << (md.eachWayDivisor ? std::to_string(*md.eachWayDivisor) : "null") << ", ";
        os << "bspMarket=" << (md.bspMarket ? (*md.bspMarket ? "true" : "false") : "null") << ", ";
        os << "turnInPlayEnabled=" << (md.turnInPlayEnabled ? (*md.turnInPlayEnabled ? "true" : "false") : "null") << ", ";
        os << "priceLadderDefinition=" << (md.priceLadderDefinition ? *md.priceLadderDefinition : "null") << ", ";
        os << "keyLineDefinition=" << (md.keyLineDefinition ? std::to_string(*md.keyLineDefinition) : "null") << ", ";
        os << "persistenceEnabled=" << (md.persistenceEnabled ? (*md.persistenceEnabled ? "true" : "false") : "null") << ", ";
        os << "marketBaseRate=" << (md.marketBaseRate ? std::to_string(*md.marketBaseRate) : "null") << ", ";
        os << "eventId=" << (md.eventId ? *md.eventId : "null") << ", ";
        os << "eventTypeId=" << (md.eventTypeId ? *md.eventTypeId : "null") << ", ";
        os << "numberOfWinners=" << (md.numberOfWinners ? std::to_string(*md.numberOfWinners) : "null") << ", ";
        os << "countryCode=" << (md.countryCode ? *md.countryCode : "null") << ", ";
        os << "lineMaxUnit=" << (md.lineMaxUnit ? std::to_string(*md.lineMaxUnit) : "null") << ", ";
        os << "bettingType=" << (md.bettingType ? *md.bettingType : "null") << ", ";
        os << "marketType=" << (md.marketType ? *md.marketType : "null") << ", ";
        os << "marketTime=" << (md.marketTime ? md.marketTime->getIsoString() : "null") << ", ";
        os << "suspendTime=" << (md.suspendTime ? md.suspendTime->getIsoString() : "null") << ", ";
        os << "bspReconciled=" << (md.bspReconciled ? (*md.bspReconciled ? "true" : "false") : "null") << ", ";
        os << "complete=" << (md.complete ? (*md.complete ? "true" : "false") : "null") << ", ";
        os << "inPlay=" << (md.inPlay ? (*md.inPlay ? "true" : "false") : "null") << ", ";
        os << "crossMatching=" << (md.crossMatching ? (*md.crossMatching ? "true" : "false") : "null") << ", ";
        os << "runnersVoidable=" << (md.runnersVoidable ? (*md.runnersVoidable ? "true" : "false") : "null") << ", ";
        os << "numberOfActiveRunners=" << (md.numberOfActiveRunners ? std::to_string(*md.numberOfActiveRunners) : "null") << ", ";
        os << "lineMinUnit=" << (md.lineMinUnit ? std::to_string(*md.lineMinUnit) : "null") << ", ";
        os << "betDelay=" << (md.betDelay ? (*md.betDelay ? "true" : "false") : "null") << ", ";
        os << "status=" << (md.status ? *md.status : "null") << ", ";
        os << "regulators=[";
        for (size_t i = 0; i < md.regulators.size(); ++i) {
            os << md.regulators[i];
            if (i < md.regulators.size() - 1) {
            os << ", ";
            }
        }
        os << "], ";
        os << "discountAllowed=" << (md.discountAllowed ? (*md.discountAllowed ? "true" : "false") : "null") << ", ";
        os << "openDate=" << (md.openDate ? md.openDate->getIsoString() : "null") << ", ";
        os << "version=" << (md.version ? std::to_string(*md.version) : "null");
        os << "}";
        return os;
    }
}