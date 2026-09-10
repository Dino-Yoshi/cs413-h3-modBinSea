cmake_minimum_required(VERSION 4.3)
project(modBinSea)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.8.1
        GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(Catch2)

enable_testing()

add_executable(modBinSea
        main.cpp)

add_executable(modBinSea_tests
        tests.cpp)
target_link_libraries(modBinSea_tests PRIVATE Catch2::Catch2WithMain)

include(Catch)
catch_discover_tests(modBinSea_tests)
