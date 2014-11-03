# find boost::regex library
find_package(Boost 1.54.0 REQUIRED regex)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
    add_definitions("-DHAS_BOOST")
endif()

# static library used for unit tests
set(LIBRARYFILES apriori.cpp associationrules.cpp bruteforce.cpp declat.cpp eclat.cpp itemsets.cpp main.cpp msweb.cpp prefixtree.cpp transactiondatabase.cpp verticaldatabase.cpp)
add_library(itemsetmining ${LIBRARYFILES})

# itemset mining command-line executable
add_executable(itemset-mining ${LIBRARYFILES} main.cpp)
target_link_libraries(itemset-mining ${Boost_LIBRARIES})
