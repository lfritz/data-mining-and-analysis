cmake_minimum_required(VERSION 2.8)

project(DATAMINING)

add_definitions(-std=c++11 -Wall)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(lib/gtest-1.7.0)

enable_testing()
add_test(UnitTest COMMAND unittest)
