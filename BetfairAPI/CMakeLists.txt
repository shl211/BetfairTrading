file(GLOB SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
#    "${CMAKE_CURRENT_SOURCE_DIR}/betting_type/*.cpp"
#    "${CMAKE_CURRENT_SOURCE_DIR}/utils/*.cpp"
)

add_library(BetfairAPI STATIC
    ${SOURCES}
)

target_include_directories(BetfairAPI 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}
#        ${CMAKE_CURRENT_SOURCE_DIR}/betting_enum
#        ${CMAKE_CURRENT_SOURCE_DIR}/betting_type
#        ${CMAKE_CURRENT_SOURCE_DIR}/utils
)

target_link_libraries(BetfairAPI 
    PRIVATE 
        cpr::cpr
    PUBLIC
        nlohmann_json::nlohmann_json
        magic_enum
#        date::date
)