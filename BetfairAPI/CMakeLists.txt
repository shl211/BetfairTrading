file(GLOB SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/BettingType/*.cpp"
)

add_library(BetfairAPI STATIC
    ${SOURCES}
)

target_include_directories(BetfairAPI 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/BettingEnums
        ${CMAKE_CURRENT_SOURCE_DIR}/BettingType
)

target_link_libraries(BetfairAPI 
    PRIVATE 
        cpr::cpr
        nlohmann_json::nlohmann_json
        magic_enum
)