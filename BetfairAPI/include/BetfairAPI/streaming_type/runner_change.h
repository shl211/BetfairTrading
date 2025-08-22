#pragma once

#include <vector>
#include <string>
#include <optional>
#include <ostream>

namespace BetfairAPI::StreamingType {
    struct RunnerValues {
        double tradedVolume;//tv
        double lastTradedPrice;//ltp
        double startingPriceNear;//spn
        double startingPriceFar;//spf
    };

    struct DepthLadder {
        int level;
        double price;
        double size;
    };

    struct PriceLadder {
        double price;
        double size;
    };
    
    struct RunnerChange {
        long runnerId;
        std::optional<bool> conflated;//con
        RunnerValues runnerValues;
        std::vector<DepthLadder> bestAvailableToBack;//batb
        std::vector<DepthLadder> bestAvailableToLay;//batl
        std::vector<DepthLadder> bestAvailableToBackVirtual;//bdatd
        std::vector<DepthLadder> bestAvailableToLayVirtual;//bdatl
        std::vector<PriceLadder> availableToBack;//atb
        std::vector<PriceLadder> availableToLay;//atl
        std::vector<PriceLadder> startingPriceBack;//spb
        std::vector<PriceLadder> startingPriceLay;//spl
        std::vector<PriceLadder> traded;//trd
    };

    inline bool operator==(const RunnerValues& lhs, const RunnerValues& rhs) {
        return lhs.tradedVolume == rhs.tradedVolume &&
               lhs.lastTradedPrice == rhs.lastTradedPrice &&
               lhs.startingPriceNear == rhs.startingPriceNear &&
               lhs.startingPriceFar == rhs.startingPriceFar;
    }

    inline bool operator!=(const RunnerValues& lhs, const RunnerValues& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const RunnerValues& values) {
        os << "Values(tradedVolume: " << values.tradedVolume
           << ", lastTradedPrice: " << values.lastTradedPrice
           << ", startingPriceNear: " << values.startingPriceNear
           << ", startingPriceFar: " << values.startingPriceFar << ")";
        return os;
    }

    inline bool operator==(const DepthLadder& lhs, const DepthLadder& rhs) {
        return lhs.level == rhs.level &&
               lhs.price == rhs.price &&
               lhs.size == rhs.size;
    }

    inline bool operator!=(const DepthLadder& lhs, const DepthLadder& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const DepthLadder& depthLadder) {
        os << "DepthLadder(level: " << depthLadder.level
           << ", price: " << depthLadder.price
           << ", size: " << depthLadder.size << ")";
        return os;
    }

    inline bool operator==(const PriceLadder& lhs, const PriceLadder& rhs) {
        return lhs.price == rhs.price &&
               lhs.size == rhs.size;
    }

    inline bool operator!=(const PriceLadder& lhs, const PriceLadder& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const PriceLadder& priceLadder) {
        os << "PriceLadder(price: " << priceLadder.price
           << ", size: " << priceLadder.size << ")";
        return os;
    }

    inline bool operator==(const RunnerChange& lhs, const RunnerChange& rhs) {
        return lhs.runnerId == rhs.runnerId &&
               lhs.conflated == rhs.conflated &&
               lhs.bestAvailableToBack == rhs.bestAvailableToBack &&
               lhs.bestAvailableToLay == rhs.bestAvailableToLay &&
               lhs.bestAvailableToBackVirtual == rhs.bestAvailableToBackVirtual &&
               lhs.bestAvailableToLayVirtual == rhs.bestAvailableToLayVirtual &&
               lhs.availableToBack == rhs.availableToBack &&
               lhs.availableToLay == rhs.availableToLay &&
               lhs.startingPriceBack == rhs.startingPriceBack &&
               lhs.startingPriceLay == rhs.startingPriceLay &&
               lhs.traded == rhs.traded;
    }

    inline bool operator!=(const RunnerChange& lhs, const RunnerChange& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const RunnerChange& runnerChange) {
        os << "RunnerChange(runnerId: " << runnerChange.runnerId
           << ", conflated: " << (runnerChange.conflated ? *runnerChange.conflated : false)
           << ", bestAvailableToBack: [";
        for (const auto& item : runnerChange.bestAvailableToBack) {
            os << item << ", ";
        }
        os << "], bestAvailableToLay: [";
        for (const auto& item : runnerChange.bestAvailableToLay) {
            os << item << ", ";
        }
        os << "], bestAvailableToBackVirtual: [";
        for (const auto& item : runnerChange.bestAvailableToBackVirtual) {
            os << item << ", ";
        }
        os << "], bestAvailableToLayVirtual: [";
        for (const auto& item : runnerChange.bestAvailableToLayVirtual) {
            os << item << ", ";
        }
        os << "], availableToBack: [";
        for (const auto& item : runnerChange.availableToBack) {
            os << item << ", ";
        }
        os << "], availableToLay: [";
        for (const auto& item : runnerChange.availableToLay) {
            os << item << ", ";
        }
        os << "], startingPriceBack: [";
        for (const auto& item : runnerChange.startingPriceBack) {
            os << item << ", ";
        }
        os << "], startingPriceLay: [";
        for (const auto& item : runnerChange.startingPriceLay) {
            os << item << ", ";
        }
        os << "], traded: [";
        for (const auto& item : runnerChange.traded) {
            os << item << ", ";
        }
        os << "])";
        return os;
    }
}