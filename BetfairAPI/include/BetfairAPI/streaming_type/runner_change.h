#pragma once

#include <optional>
#include <tuple>
#include <vector>
#include <string>

namespace BetfairAPI::StreamingType {
    using Level = int;
    using Price = double;
    using Size = double;
    using LadderInfo = std::tuple<Level,Price,Size>;
    using PriceSize = std::tuple<Price,Size>;

    struct RunnerValues {
        std::optional<double> tradedVolume; //tv
        std::optional<double> lastTradedPrice; //ltp
        std::optional<double> startingPriceNear; //spn
        std::optional<double> startingPriceFar; //spf
        std::optional<std::string> runnerId; //id
    };

    inline bool operator==(const RunnerValues& lhs, const RunnerValues& rhs) {
        return lhs.tradedVolume == rhs.tradedVolume &&
               lhs.lastTradedPrice == rhs.lastTradedPrice &&
               lhs.startingPriceNear == rhs.startingPriceNear &&
               lhs.startingPriceFar == rhs.startingPriceFar &&
               lhs.runnerId == rhs.runnerId;
    }

    inline bool operator!=(const RunnerValues& lhs, const RunnerValues& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const RunnerValues& rv) {
        os << "RunnerValues{";
        os << "tradedVolume=" << (rv.tradedVolume ? std::to_string(*rv.tradedVolume) : "null") << ", ";
        os << "lastTradedPrice=" << (rv.lastTradedPrice ? std::to_string(*rv.lastTradedPrice) : "null") << ", ";
        os << "startingPriceNear=" << (rv.startingPriceNear ? std::to_string(*rv.startingPriceNear) : "null") << ", ";
        os << "startingPriceFar=" << (rv.startingPriceFar ? std::to_string(*rv.startingPriceFar) : "null") << ", ";
        os << "runnerId=" << (rv.runnerId ? *rv.runnerId : "null");
        os << "}";
        return os;
    }

    struct LevelBasedLadder {
        std::vector<LadderInfo> bestAvailableToBack; //batb
        std::vector<LadderInfo> bestAvailableToLay; //batl
        std::vector<LadderInfo> bestAvailableToBackVirtual; //bdatb
        std::vector<LadderInfo> bestAvailableToLayVirtual; //bdatl
    };

    inline bool operator==(const LevelBasedLadder& lhs, const LevelBasedLadder& rhs) {
        return lhs.bestAvailableToBack == rhs.bestAvailableToBack &&
               lhs.bestAvailableToLay == rhs.bestAvailableToLay &&
               lhs.bestAvailableToBackVirtual == rhs.bestAvailableToBackVirtual &&
               lhs.bestAvailableToLayVirtual == rhs.bestAvailableToLayVirtual;
    }

    inline bool operator!=(const LevelBasedLadder& lhs, const LevelBasedLadder& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const LevelBasedLadder& lbl) {
        os << "LevelBasedLadder{";
        os << "bestAvailableToBack=[";
        for (size_t i = 0; i < lbl.bestAvailableToBack.size(); ++i) {
            if (i > 0) os << ", ";
            const auto& item = lbl.bestAvailableToBack[i];
            os << "(" << std::get<0>(item) << "," << std::get<1>(item) << "," << std::get<2>(item) << ")";
        }
        os << "], bestAvailableToLay=[";
        for (size_t i = 0; i < lbl.bestAvailableToLay.size(); ++i) {
            if (i > 0) os << ", ";
            const auto& item = lbl.bestAvailableToLay[i];
            os << "(" << std::get<0>(item) << "," << std::get<1>(item) << "," << std::get<2>(item) << ")";
        }
        os << "], bestAvailableToBackVirtual=[";
        for (size_t i = 0; i < lbl.bestAvailableToBackVirtual.size(); ++i) {
            if (i > 0) os << ", ";
            const auto& item = lbl.bestAvailableToBackVirtual[i];
            os << "(" << std::get<0>(item) << "," << std::get<1>(item) << "," << std::get<2>(item) << ")";
        }
        os << "], bestAvailableToLayVirtual=[";
        for (size_t i = 0; i < lbl.bestAvailableToLayVirtual.size(); ++i) {
            if (i > 0) os << ", ";
            const auto& item = lbl.bestAvailableToLayVirtual[i];
            os << "(" << std::get<0>(item) << "," << std::get<1>(item) << "," << std::get<2>(item) << ")";
        }
        os << "]";
        os << "}";
        return os;
    }
    
    struct PriceBasedLadder {
        std::vector<PriceSize> availableToBack; //atb
        std::vector<PriceSize> availableToLay; //atl
        std::vector<PriceSize> startingPriceAvailableToBack; //spb
        std::vector<PriceSize> startingPriceAvailableToLay; //spl
        std::vector<PriceSize> traded;//trd
    };

    inline bool operator==(const PriceBasedLadder& lhs, const PriceBasedLadder& rhs) {
        return lhs.availableToBack == rhs.availableToBack &&
               lhs.availableToLay == rhs.availableToLay &&
               lhs.startingPriceAvailableToBack == rhs.startingPriceAvailableToBack &&
               lhs.startingPriceAvailableToLay == rhs.startingPriceAvailableToLay &&
               lhs.traded == rhs.traded;
    }

    inline bool operator!=(const PriceBasedLadder& lhs, const PriceBasedLadder& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const PriceBasedLadder& pbl) {
        os << "PriceBasedLadder{";
        os << "availableToBack=[";
        for (size_t i = 0; i < pbl.availableToBack.size(); ++i) {
            if (i > 0) os << ", ";
            const auto& item = pbl.availableToBack[i];
            os << "(" << std::get<0>(item) << "," << std::get<1>(item) << ")";
        }
        os << "], availableToLay=[";
        for (size_t i = 0; i < pbl.availableToLay.size(); ++i) {
            if (i > 0) os << ", ";
            const auto& item = pbl.availableToLay[i];
            os << "(" << std::get<0>(item) << "," << std::get<1>(item) << ")";
        }
        os << "], startingPriceAvailableToBack=[";
        for (size_t i = 0; i < pbl.startingPriceAvailableToBack.size(); ++i) {
            if (i > 0) os << ", ";
            const auto& item = pbl.startingPriceAvailableToBack[i];
            os << "(" << std::get<0>(item) << "," << std::get<1>(item) << ")";
        }
        os << "], startingPriceAvailableToLay=[";
        for (size_t i = 0; i < pbl.startingPriceAvailableToLay.size(); ++i) {
            if (i > 0) os << ", ";
            const auto& item = pbl.startingPriceAvailableToLay[i];
            os << "(" << std::get<0>(item) << "," << std::get<1>(item) << ")";
        }
        os << "], traded=[";
        for (size_t i = 0; i < pbl.traded.size(); ++i) {
            if (i > 0) os << ", ";
            const auto& item = pbl.traded[i];
            os << "(" << std::get<0>(item) << "," << std::get<1>(item) << ")";
        }
        os << "]";
        os << "}";
        return os;
    }

    struct RunnerChange {
        bool replaceImage = false; //img
        double totalMatchedVolume = 0;//tv
        std::vector<RunnerValues> values;
        std::vector<LevelBasedLadder> lvlLadder;
        std::vector<PriceBasedLadder> priceLadder;
    };

    inline bool operator==(const RunnerChange& lhs, const RunnerChange& rhs) {
        return lhs.replaceImage == rhs.replaceImage &&
               lhs.totalMatchedVolume == rhs.totalMatchedVolume &&
               lhs.values == rhs.values &&
               lhs.lvlLadder == rhs.lvlLadder &&
               lhs.priceLadder == rhs.priceLadder;
    }

    inline bool operator!=(const RunnerChange& lhs, const RunnerChange& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const RunnerChange& rc) {
        os << "RunnerChange{";
        os << "replaceImage=" << (rc.replaceImage ? "true" : "false") << ", ";
        os << "totalMatchedVolume=" << rc.totalMatchedVolume << ", ";
        os << "values=[";
        for (size_t i = 0; i < rc.values.size(); ++i) {
            if (i > 0) os << ", ";
            os << rc.values[i];
        }
        os << "], lvlLadder=[";
        for (size_t i = 0; i < rc.lvlLadder.size(); ++i) {
            if (i > 0) os << ", ";
            os << rc.lvlLadder[i];
        }
        os << "], priceLadder=[";
        for (size_t i = 0; i < rc.priceLadder.size(); ++i) {
            if (i > 0) os << ", ";
            os << rc.priceLadder[i];
        }
        os << "]";
        os << "}";
        return os;
    }
}