#include <string_view>

namespace BetfairAPI {
    //enum values are the event type id in Betfair
    enum class EventTypeIds {
        Soccer = 1,
        Tennis = 2,
        Basketball = 7522,
        Golf = 3,
        IceHockey = 7524,
        Cricket = 4,
        RugbyLeague = 1477,
        RugbyUnion = 5,
        Boxing = 6,
        HorseRacing = 7,
        MotorSport = 8,
        Esports = 27454571,
        SpecialBets = 10,
        Cycling = 11,
        AustralianRules = 61420,
        Darts = 3503,
        GaelicGames = 2152880,
        MixedMartialArts = 26420387,
        GreyhoundRacing = 4339,
        Politics = 2378961,
        Snooker = 6422,
        Baseball = 7511,
        AmericanFootball = 6423,
    };

    constexpr std::string_view eventTypeIdsToString(EventTypeIds event) {
        switch(event) {
            case EventTypeIds::Soccer: return "Soccer";
            case EventTypeIds::Tennis: return "Tennis";
            case EventTypeIds::Basketball: return "Basketball";
            case EventTypeIds::Golf: return "Golf";
            case EventTypeIds::IceHockey: return "Ice Hockey";
            case EventTypeIds::Cricket: return "Cricket";
            case EventTypeIds::RugbyLeague: return "Rugby League";
            case EventTypeIds::RugbyUnion: return "Rugby Union";
            case EventTypeIds::Boxing: return "Boxing";
            case EventTypeIds::HorseRacing: return "Horse Racing";
            case EventTypeIds::MotorSport: return "Motor Sport";
            case EventTypeIds::Esports: return "Esports";
            case EventTypeIds::SpecialBets: return "Special Bets";
            case EventTypeIds::Cycling: return "Cycling";
            case EventTypeIds::AustralianRules: return "Australian Rules";
            case EventTypeIds::Darts: return "Darts";
            case EventTypeIds::GaelicGames: return "Gaelic Games";
            case EventTypeIds::MixedMartialArts: return "Mixed Martial Arts";
            case EventTypeIds::GreyhoundRacing: return "Greyhound Racing";
            case EventTypeIds::Politics: return "Politics";
            case EventTypeIds::Snooker: return "Snooker";
            case EventTypeIds::Baseball: return "Baseball";
            case EventTypeIds::AmericanFootball: return "American Football";
            default: return "UNKNOWN"; 
        }
    }
}    