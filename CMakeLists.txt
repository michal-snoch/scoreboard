cmake_minimum_required(VERSION 3.10)
project(ScoreBoard)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(ScoreBoardLib src/memory_store.cpp
                          src/score_board.cpp
)
target_include_directories(ScoreBoardLib PRIVATE ${PROJECT_SOURCE_DIR}/include)

add_subdirectory(googletest)

add_executable(ScoreBoardTests tests/memory_store_test_suite.cpp
                               tests/score_reader_test_suite.cpp
                               tests/score_updater_test_suite.cpp
                               tests/score_board_integration_test_suite.cpp                         
)
target_include_directories(ScoreBoardTests PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(ScoreBoardTests gtest gmock gtest_main ScoreBoardLib)