#pragma once

namespace BetfairAPI::BettingType {
    class KeyLineSelection {
        public:
            KeyLineSelection(long selection_id,double handicap);
            KeyLineSelection() = default;
            ~KeyLineSelection() = default;
            KeyLineSelection(const KeyLineSelection&) = default;
            KeyLineSelection(KeyLineSelection&&) noexcept = default;
            KeyLineSelection& operator=(const KeyLineSelection&) = default;
            KeyLineSelection& operator=(KeyLineSelection&&) noexcept = default;

            bool operator==(const KeyLineSelection& other) const;
            bool operator!=(const KeyLineSelection& other) const;

            long getSelectionId() const;
            double getHandicap() const;

        private:
            long selection_id_;
            double handicap_;
    };
}