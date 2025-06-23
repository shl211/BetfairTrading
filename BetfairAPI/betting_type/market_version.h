#pragma once

namespace BetfairAPI::BettingType {
    class MarketVersion {
        
        public: 
            explicit MarketVersion(long version);
            MarketVersion() = default;
            ~MarketVersion() = default;
            MarketVersion(const MarketVersion&) = default;
            MarketVersion(MarketVersion&&) noexcept = default;
            MarketVersion& operator=(const MarketVersion&) = default;
            MarketVersion& operator=(MarketVersion&&) noexcept = default;

            long getVersion();

        private:
            long version_;
    };
}