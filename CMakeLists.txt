cmake_minimum_required(VERSION 2.8)

project(DATAMINING)

add_definitions(-std=c++11 -Wall)

find_package(Boost 1.54.0 REQUIRED regex)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
    add_definitions("-DHAS_BOOST")
endif()

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(lib/gtest-1.7.0)

enable_testing()
add_test(UnitTest COMMAND unittest)
