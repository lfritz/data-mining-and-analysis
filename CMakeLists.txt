cmake_minimum_required(VERSION 2.8.11)

project(DATAMINING)

add_definitions(-std=c++14 -Wall)

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(clustering-gui)
add_subdirectory(lib/gtest-1.7.0)

enable_testing()
add_test(UnitTest COMMAND unittest)
