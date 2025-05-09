cmake_minimum_required(VERSION 3.10)
project(BetfairProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

###################################
# Fetch external libraries
###################################
include(FetchContent)
#Fetch CPR library
FetchContent_Declare(
    cpr
    GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG        1.11.0
)

#Fetch nlohmann/json library
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG        v3.11.2
)


FetchContent_MakeAvailable(cpr json)

add_subdirectory(BetfairAPI)

add_executable(app main.cpp)
target_link_libraries(app PRIVATE BetfairAPI cpr::cpr nlohmann_json::nlohmann_json)