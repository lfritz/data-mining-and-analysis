# we need to set 'src' as include directory so the compiler can find the header
# files
include_directories(
    ${ITEMSETMINING_SOURCE_DIR}/lib/gtest-1.7.0/include
    ${ITEMSETMINING_SOURCE_DIR}/src
)

set(SOURCEFILES main.cpp frequentitemsettest.cpp itemsetstest.cpp prefixtreetest.cpp)

add_executable(unittest ${SOURCEFILES})
target_link_libraries(unittest itemsetmining gtest_main)
