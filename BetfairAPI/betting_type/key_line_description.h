#pragma once

#include <vector>
#include "key_line_selection.h"

namespace BetfairAPI::BettingType {
    class KeyLineDescription {
        public:
            template <typename Iterable>
            KeyLineDescription(const Iterable& key_line);

            KeyLineDescription(const std::vector<KeyLineSelection>& key_line);
            KeyLineDescription() = default;
            ~KeyLineDescription() = default;
            KeyLineDescription(const KeyLineDescription&) = default;
            KeyLineDescription(KeyLineDescription&&) noexcept = default;
            KeyLineDescription& operator=(const KeyLineDescription&) = default;
            KeyLineDescription& operator=(KeyLineDescription&&) noexcept = default;
            
            const std::vector<KeyLineSelection>& getKeyLine() const;
        
        private:
            std::vector<KeyLineSelection> key_line_;
    };
}