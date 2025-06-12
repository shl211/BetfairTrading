add_library(BetfairAPI STATIC
    placeholder.cpp
)

target_link_libraries(BetfairAPI 
    PRIVATE 
        cpr::cpr
        nlohmann_json::nlohmann_json)