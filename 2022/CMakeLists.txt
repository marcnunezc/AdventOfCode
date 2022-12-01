cmake_minimum_required(VERSION 3.16)
set (CMAKE_CXX_STANDARD 20)

project(aoc22)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/")

include_directories(include)
include_directories(Day01)

add_executable(aoc22 src/main.cpp)
