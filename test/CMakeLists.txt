# we need to set 'src' as include directory so the compiler can find the header
# files
include_directories(
    ${DATAMINING_SOURCE_DIR}/lib
    ${DATAMINING_SOURCE_DIR}/src
)

set(SOURCEFILES algorithm.cpp associationrule.cpp bayesclassifier.cpp clustering.cpp frequentitemsets.cpp itemsets.cpp kernelfunction.cpp kernelkmeans.cpp kmeans.cpp knnclassifier.cpp main.cpp naivebayesclassifier.cpp prefixtree.cpp verticaldatabase.cpp)

add_executable(unittest ${SOURCEFILES})
target_link_libraries(unittest datamining)
