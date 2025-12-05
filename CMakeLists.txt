cmake_minimum_required(VERSION 3.12)

set(PROJECT_NAME aoc25)
set(TARGET_NAME ${PROJECT_NAME})

project(${PROJECT_NAME} VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

find_package(GTest REQUIRED)

add_executable(${TARGET_NAME})

target_sources(${TARGET_NAME} PRIVATE
    "day1.cpp"
    "day2.cpp"
    "day3.cpp"
    "day4.cpp"
    "day5.cpp")

target_link_libraries(${TARGET_NAME}
    GTest::GTest GTest::Main)

gtest_discover_tests(${TARGET_NAME})

enable_testing()

configure_file("${CMAKE_SOURCE_DIR}/day1_input_rotations.txt"
    "${CMAKE_BINARY_DIR}/day1_input_rotations.txt" COPYONLY)
configure_file("${CMAKE_SOURCE_DIR}/day2_input_ranges.txt"
    "${CMAKE_BINARY_DIR}/day2_input_ranges.txt" COPYONLY)
configure_file("${CMAKE_SOURCE_DIR}/day3_input_banks.txt"
    "${CMAKE_BINARY_DIR}/day3_input_banks.txt" COPYONLY)
configure_file("${CMAKE_SOURCE_DIR}/day4_input_paper_rolls.txt"
    "${CMAKE_BINARY_DIR}/day4_input_paper_rolls.txt" COPYONLY)
configure_file("${CMAKE_SOURCE_DIR}/day5_input_database.txt"
    "${CMAKE_BINARY_DIR}/day5_input_database.txt" COPYONLY)
