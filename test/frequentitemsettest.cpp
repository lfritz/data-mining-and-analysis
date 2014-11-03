#include "frequentitemsettest.h"

using std::string;
using std::unique_ptr;
using std::vector;

FrequentItemsetTest::FrequentItemsetTest() : td() {
    // sample database from the book
    vector<string> items = { "A", "B", "C", "D", "E" };
    vector<vector<int>> transactions = {
        { 0, 1,    3, 4 },
        {    1, 2,    4 },
        { 0, 1,    3, 4 },
        { 0, 1, 2,    4 },
        { 0, 1, 2, 3, 4 },
        {    1, 2, 3,   }
    };
    td = unique_ptr<TransactionDatabase>(new TransactionDatabase(items,
                                                                 transactions));
    vd = unique_ptr<VerticalDatabase>(new VerticalDatabase(*td));

    // frequent itemsets (table 8.1 in the book)
    minsup = 3;
    correct_result = {
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
}

TEST_F(FrequentItemsetTest, brute_force) {
    FrequentItemsets results = brute_force(*td, minsup);
    EXPECT_EQ(correct_result, results);
}

TEST_F(FrequentItemsetTest, apriori) {
    FrequentItemsets results = apriori(*td, minsup);
    EXPECT_EQ(correct_result, results);
}

TEST_F(FrequentItemsetTest, eclat) {
    FrequentItemsets results = eclat(*vd, minsup);
    EXPECT_EQ(correct_result, results);
}

TEST_F(FrequentItemsetTest, declat) {
    FrequentItemsets results = declat(*vd, minsup);
    EXPECT_EQ(correct_result, results);
}
