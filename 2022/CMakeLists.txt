cmake_minimum_required(VERSION 3.16)
set (CMAKE_CXX_STANDARD 20)

project(aoc22)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/")

include_directories(include)
include_directories(Day01)
include_directories(Day02)
include_directories(Day03)
include_directories(Day04)
include_directories(Day05)
include_directories(Day06)
include_directories(Day07)
include_directories(Day08)
include_directories(Day09)
include_directories(Day10)
include_directories(Day11)

add_executable(aoc22 src/main.cpp)
