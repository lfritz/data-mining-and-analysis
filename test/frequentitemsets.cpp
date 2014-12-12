#include <catch.hpp>

#include <apriori.h>
#include <bruteforce.h>
#include <declat.h>
#include <eclat.h>
#include <transactiondatabase.h>
#include <verticaldatabase.h>

using std::string;
using std::vector;

TEST_CASE("Finding frequent items from sample database") {
    // sample database from the book
    vector<string> items { "A", "B", "C", "D", "E" };
    vector<vector<int>> transactions {
        { 0, 1,    3, 4 },
        {    1, 2,    4 },
        { 0, 1,    3, 4 },
        { 0, 1, 2,    4 },
        { 0, 1, 2, 3, 4 },
        {    1, 2, 3,   }
    };
    TransactionDatabase td(items, transactions);
    VerticalDatabase vd(td);

    // frequent itemsets (table 8.1 in the book)
    int minsup = 3;
    FrequentItemsets correct_result {
        { {1}, 6 },
        { {4}, 5 }, { {1,4}, 5 },
        { {0}, 4 }, { {2}, 4 }, { {3}, 4 },
        { {0,1}, 4 }, { {0,4}, 4 }, { {1,2}, 4 }, { {1,3}, 4 },
        { {0,1,4}, 4 },
        { {0,3}, 3},
        { {2,4}, 3},
        { {3,4}, 3},
        { {0,1,3}, 3},
        { {0,3,4}, 3},
        { {1,2,4}, 3},
        { {1,3,4}, 3},
        { {0,1,3,4}, 3}
    };

    CHECK(apriori(td, minsup) == correct_result);
    CHECK(brute_force(td, minsup) == correct_result);
    CHECK(declat(vd, minsup) == correct_result);
    CHECK(eclat(vd, minsup) == correct_result);
}
