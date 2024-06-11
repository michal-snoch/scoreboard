cmake_minimum_required(VERSION 3.10)
project(ScoreBoard)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(googletest)
add_executable(ScoreBoardTests store_test_suite.cpp)
target_link_libraries(ScoreBoardTests gtest gmock gtest_main)