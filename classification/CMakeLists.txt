# we need to set 'src' as include directory so the compiler can find the header
# files
include_directories(${DATAMINING_SOURCE_DIR}/src)

find_package(Boost COMPONENTS system timer REQUIRED)

add_executable(classification main.cpp tsv.cpp)
target_link_libraries(classification datamining)
target_link_libraries(classification ${Boost_LIBRARIES})
