find_package(GTest REQUIRED)

set(TARGET_NAME aoc25)

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

configure_file("day1_input_rotations.txt"
    "${CMAKE_CURRENT_BINARY_DIR}/day1_input_rotations.txt" COPYONLY)
configure_file("day2_input_ranges.txt"
    "${CMAKE_CURRENT_BINARY_DIR}/day2_input_ranges.txt" COPYONLY)
configure_file("day3_input_banks.txt"
    "${CMAKE_CURRENT_BINARY_DIR}/day3_input_banks.txt" COPYONLY)
configure_file("day4_input_paper_rolls.txt"
    "${CMAKE_CURRENT_BINARY_DIR}/day4_input_paper_rolls.txt" COPYONLY)
configure_file("day5_input_database.txt"
    "${CMAKE_CURRENT_BINARY_DIR}/day5_input_database.txt" COPYONLY)
