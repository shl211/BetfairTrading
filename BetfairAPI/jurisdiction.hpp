#pragma once
#include <string_view>

namespace BetfairAPI {
    enum class Jurisdiction {
        GLOBAL,
        AUSTRALIA,
        NEWZEALAND,
        ITALY,
        SPAIN,
        ROMANIA,
        SWEDEN,
    };

    namespace detail {
        inline constexpr std::string_view global_url {"https://identitysso.betfair.com/api/"};
        inline constexpr std::string_view new_zealand_australia_url {"https://identitysso.betfair.com.au/api/"};
        inline constexpr std::string_view italy_url {"https://identitysso.betfair.it/api/"};
        inline constexpr std::string_view spain_url {"https://identitysso.betfair.es/api/"};
        inline constexpr std::string_view romania_url {"https://identitysso.betfair.ro/api/"};
        inline constexpr std::string_view sweden_url {"https://identitysso.betfair.se/api/"}; 
    }

    constexpr std::string_view getBetfairUrl(Jurisdiction j) {
        switch (j) {
            case Jurisdiction::GLOBAL:
                return detail::global_url;
            case Jurisdiction::AUSTRALIA:
            case Jurisdiction::NEWZEALAND:
                return detail::new_zealand_australia_url;
            case Jurisdiction::ITALY:
                return detail::italy_url;
            case Jurisdiction::SPAIN:
                return detail::spain_url;
            case Jurisdiction::ROMANIA:
                return detail::romania_url;
            case Jurisdiction::SWEDEN:
                return detail::sweden_url;
            default:
                return detail::global_url;
        }
    }
}