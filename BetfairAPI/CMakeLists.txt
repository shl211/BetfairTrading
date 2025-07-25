file(GLOB SOURCES CONFIGURE_DEPENDS
    "src/*.cpp"
    "src/betting_type/*.cpp"
    "src/account_type/*.cpp"
)

# Add Howard Hinnant date tz.cpp source explicitly
set(DATE_TZ_SRC "${date_SOURCE_DIR}/src/tz.cpp")

add_library(BetfairAPI STATIC
    ${SOURCES}
    ${DATE_TZ_SRC}            # add tz.cpp here
)

target_include_directories(BetfairAPI 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${date_SOURCE_DIR}/include    # include date headers
)

target_compile_definitions(BetfairAPI PRIVATE HAS_REMOTE_API=1)
find_package(OpenSSL REQUIRED)

target_link_libraries(BetfairAPI 
    PRIVATE 
        cpr::cpr
        PUBLIC
        nlohmann_json::nlohmann_json
        magic_enum
        date::date
        Logging
        OpenSSL::SSL
        OpenSSL::Crypto
)


target_include_directories(BetfairAPI 
    PUBLIC 
        ${asio_SOURCE_DIR}/asio/include
)