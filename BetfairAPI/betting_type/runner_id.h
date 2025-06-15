#pragma once

#include <string>

namespace BetfairAPI::BettingType {
    class RunnerId {
        public:
            RunnerId(std::string_view market_id, std::string_view selection_id,
                        double handicap);
            ~RunnerId() = default;
            RunnerId(const RunnerId&) = default;
            RunnerId(RunnerId&&) noexcept = default;
            RunnerId& operator=(const RunnerId&) = default;
            RunnerId& operator=(RunnerId&&) noexcept = default;

            bool operator==(const RunnerId& other) const;
            bool operator!=(const RunnerId& other) const;

            const std::string& getMarketId() const;
            const std::string& getSelectionId() const;
            double getHandicap() const;

        private:
            std::string market_id_;
            std::string selection_id_;
            double handicap_; 
    };
}