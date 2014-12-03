# we need to set 'src' as include directory so the compiler can find the header
# files
include_directories(
    ${DATAMINING_SOURCE_DIR}/lib/gtest-1.7.0/include
    ${DATAMINING_SOURCE_DIR}/src
)

set(SOURCEFILES main.cpp algorithmtest.cpp associationrulestest.cpp bayesclassifiertest.cpp clusteringtest.cpp frequentitemsettest.cpp itemsetstest.cpp kernelfunctiontest.cpp kernelkmeanstest.cpp kmeanstest.cpp prefixtreetest.cpp verticaldatabasetest.cpp)

add_executable(unittest ${SOURCEFILES})
target_link_libraries(unittest itemsetmining gtest_main)
