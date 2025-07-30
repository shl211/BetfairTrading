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

    struct LevelBasedLadder {
        std::vector<LadderInfo> bestAvailableToBack; //batb
        std::vector<LadderInfo> bestAvailableToLay; //batl
        std::vector<LadderInfo> bestAvailableToBackVirtual; //bdatb
        std::vector<LadderInfo> bestAvailableToLayVirtual; //bdatl
    };
    
    struct PriceBasedLadder {
        std::vector<PriceSize> availableToBack; //atb
        std::vector<PriceSize> availableToLay; //atl
        std::vector<PriceSize> startingPriceAvailableToBack; //spb
        std::vector<PriceSize> startingPriceAvailableToLay; //spl
        std::vector<PriceSize> traded;//trd
    };

    struct RunnerChange {
        bool replaceImage = false; //img
        double totalMatchedVolume = 0;//tv
        std::vector<RunnerValues> values;
        std::vector<LevelBasedLadder> lvlLadder;
        std::vector<PriceBasedLadder> priceLadder;
    };
}