# we need to set 'src' as include directory so the compiler can find the header
# files
include_directories(${DATAMINING_SOURCE_DIR}/src)

find_package(Boost REQUIRED)

add_executable(classification csv.cpp main.cpp)
target_link_libraries(classification datamining)
