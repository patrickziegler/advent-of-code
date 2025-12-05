cmake_minimum_required(VERSION 3.12)

set(PROJECT_NAME advent-of-code)
set(TARGET_NAME ${PROJECT_NAME})

project(${PROJECT_NAME} VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

add_subdirectory(2025)

enable_testing()
