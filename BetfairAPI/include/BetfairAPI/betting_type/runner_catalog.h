#pragma once

#include <string>
#include <ostream>
#include <map>

namespace BetfairAPI::BettingType {
    struct RunnerCatalog {
        long selectionId;
        std::string runnerName;
        double handicap;
        int sortPriority;
        std::map<std::string,std::string> metadata;
    };

    inline bool operator==(const RunnerCatalog& lhs, const RunnerCatalog& rhs) {
        return lhs.selectionId == rhs.selectionId &&
                lhs.runnerName == rhs.runnerName &&
                lhs.handicap == rhs.handicap &&
                lhs.sortPriority == rhs.sortPriority &&
                lhs.metadata == rhs.metadata;
    }

    inline bool operator!=(const RunnerCatalog& lhs, const RunnerCatalog& rhs) {
        return !(lhs == rhs);
    }

    #include <ostream>
    inline std::ostream& operator<<(std::ostream& os, const RunnerCatalog& rc) {
        os << "RunnerCatalog{selectionId=" << rc.selectionId
            << ", runnerName=\"" << rc.runnerName
            << "\", handicap=" << rc.handicap
            << ", sortPriority=" << rc.sortPriority
            << ", metadata={";
        bool first = true;
        for (const auto& kv : rc.metadata) {
            if (!first) os << ", ";
            os << "\"" << kv.first << "\":\"" << kv.second << "\"";
            first = false;
        }
        os << "}}";
        return os;
    }
}