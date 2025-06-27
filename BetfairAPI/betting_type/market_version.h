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

            bool operator==(const MarketVersion& other) const;
            bool operator!=(const MarketVersion& other) const;

            long getVersion() const;

        private:
            long version_;
    };
}