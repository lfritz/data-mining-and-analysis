cmake_minimum_required(VERSION 2.8.11)

project(DATAMINING)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")

if(USE_SANITIZER STREQUAL "address")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O1 -g -fsanitize=address -fno-omit-frame-pointer")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -g -fsanitize=address")
elseif(USE_SANITIZER STREQUAL "undefined")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O1 -g -fsanitize=undefined -fno-omit-frame-pointer")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -g -fsanitize=undefined")
elseif(USE_SANITIZER)
    message("Unknown value for USE_SANITIZER!")
endif()

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(classification)
add_subdirectory(clustering-gui)
add_subdirectory(itemset-mining)

enable_testing()
add_test(UnitTest COMMAND unittest)
