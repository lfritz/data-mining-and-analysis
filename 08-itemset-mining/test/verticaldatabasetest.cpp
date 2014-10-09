#include "verticaldatabasetest.h"

#include <transactiondatabase.h>
#include <verticaldatabase.h>

using std::string;
using std::vector;

VerticalDatabaseTest::VerticalDatabaseTest() :
items({ "A", "B", "C" }),
transactions({ { 0, 2 }, { 1 }, { 1, 2 } }) {
}

// Test the first constructor.
TEST_F(VerticalDatabaseTest, ctor1) {
    VerticalDatabase d(items, transactions);
    EXPECT_EQ(items.size(), d.nItems());
    EXPECT_EQ(transactions.size(), d.nTransactions());
    EXPECT_EQ("B", d.is[1]);
    EXPECT_TRUE(d.bs[0][0]); // item 0 (A) is in transaction 0
    EXPECT_TRUE(d.bs[1][1]); // item 1 (B) is in transaction 1
    EXPECT_TRUE(d.bs[2][0]); // item 2 (C) is in transaction 0
    EXPECT_TRUE(d.bs[2][2]); // item 2 (C) is in transaction 2
    EXPECT_FALSE(d.bs[0][1]); // item 0 (A) is not in transaction 0
    EXPECT_FALSE(d.bs[2][1]); // item 2 (C) is not in transaction 1
}

// Test the second constructor, which takes a TransactionDatabase object.
TEST_F(VerticalDatabaseTest, ctor2) {
    TransactionDatabase td(items, transactions);
    VerticalDatabase d(td);
    EXPECT_EQ(items.size(), d.nItems());
    EXPECT_EQ(transactions.size(), d.nTransactions());
    EXPECT_EQ("B", d.is[1]);
    EXPECT_TRUE(d.bs[0][0]); // item 0 (A) is in transaction 0
    EXPECT_TRUE(d.bs[1][1]); // item 1 (B) is in transaction 1
    EXPECT_TRUE(d.bs[2][0]); // item 2 (C) is in transaction 0
    EXPECT_TRUE(d.bs[2][2]); // item 2 (C) is in transaction 2
    EXPECT_FALSE(d.bs[0][1]); // item 0 (A) is not in transaction 0
    EXPECT_FALSE(d.bs[2][1]); // item 2 (C) is not in transaction 1
}
