cmake_minimum_required(VERSION 3.10)
project(BetfairProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#Fetch CPR library
include(FetchContent)
FetchContent_Declare(
    cpr
    GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG        1.11.0
)
FetchContent_MakeAvailable(cpr)

add_subdirectory(BetfairAPI)

add_executable(app main.cpp)
target_link_libraries(app PRIVATE BetfairAPI cpr)