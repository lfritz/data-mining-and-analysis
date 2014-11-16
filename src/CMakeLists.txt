# static library used for unit tests
set(LIBRARYFILES apriori.cpp associationrules.cpp bruteforce.cpp clustering.cpp declat.cpp eclat.cpp itemsets.cpp kernelfunction.cpp kernelkmeans.cpp kmeans.cpp main.cpp msweb.cpp prefixtree.cpp transactiondatabase.cpp verticaldatabase.cpp)
add_library(itemsetmining ${LIBRARYFILES})

# itemset mining command-line executable
add_executable(itemset-mining ${LIBRARYFILES} main.cpp)
target_link_libraries(itemset-mining ${Boost_LIBRARIES})
