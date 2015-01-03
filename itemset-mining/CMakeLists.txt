# we need to set 'src' as include directory so the compiler can find the header
# files
include_directories(${DATAMINING_SOURCE_DIR}/src)

find_package(Boost COMPONENTS system timer REQUIRED)

add_executable(itemset-mining main.cpp msweb.cpp)
target_link_libraries(itemset-mining datamining)
target_link_libraries(itemset-mining ${Boost_LIBRARIES})
