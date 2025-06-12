file(GLOB SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_library(BetfairAPI STATIC
    ${SOURCES}
)

target_include_directories(BetfairAPI 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/BettingEnums
)

target_link_libraries(BetfairAPI 
    PRIVATE 
        cpr::cpr
        nlohmann_json::nlohmann_json
        magic_enum
)