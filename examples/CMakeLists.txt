include(FetchContent)
FetchContent_Declare(
    cxxopts
    GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git
    GIT_TAG v3.1.1 # or latest stable
)
FetchContent_MakeAvailable(cxxopts)

add_executable(example_place_order example_place_order.cpp)
target_link_libraries(example_place_order PRIVATE BetfairAPI cxxopts)

add_executable(example_cancel_order example_cancel_order.cpp)
target_link_libraries(example_cancel_order PRIVATE BetfairAPI cxxopts)
