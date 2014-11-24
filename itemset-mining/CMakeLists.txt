# we need to set 'src' as include directory so the compiler can find the header
# files
include_directories(${DATAMINING_SOURCE_DIR}/src)

add_executable(itemset-mining main.cpp msweb.cpp)
target_link_libraries(itemset-mining itemsetmining)
