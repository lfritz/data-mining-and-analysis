#include <catch.hpp>

#include <transactiondatabase.h>
#include <verticaldatabase.h>

using std::string;
using std::vector;

TEST_CASE("VerticalDatabase") {
    vector<string> items { "A", "B", "C" };
    vector<vector<int>> transactions { { 0, 2 }, { 1 }, { 1, 2 } };

    SECTION("Create VerticalDatabase from item ids") {
        VerticalDatabase d(items, transactions);
        CHECK(d.nItems() == items.size());
        CHECK(d.nTransactions() == transactions.size());
        CHECK(d.is[1] == "B");
        CHECK(d.bs[0][0]); // item 0 (A) is in transaction 0
        CHECK(d.bs[1][1]); // item 1 (B) is in transaction 1
        CHECK(d.bs[2][0]); // item 2 (C) is in transaction 0
        CHECK(d.bs[2][2]); // item 2 (C) is in transaction 2
        CHECK_FALSE(d.bs[0][1]); // item 0 (A) is not in transaction 0
        CHECK_FALSE(d.bs[2][1]); // item 2 (C) is not in transaction 1
    }

    SECTION("Create VerticalDatabase from TransactionDatabase") {
        TransactionDatabase td(items, transactions);
        VerticalDatabase d(td);
        CHECK(d.nItems() == items.size());
        CHECK(d.nTransactions() == transactions.size());
        CHECK(d.is[1] == "B");
        CHECK(d.bs[0][0]); // item 0 (A) is in transaction 0
        CHECK(d.bs[1][1]); // item 1 (B) is in transaction 1
        CHECK(d.bs[2][0]); // item 2 (C) is in transaction 0
        CHECK(d.bs[2][2]); // item 2 (C) is in transaction 2
        CHECK_FALSE(d.bs[0][1]); // item 0 (A) is not in transaction 0
        CHECK_FALSE(d.bs[2][1]); // item 2 (C) is not in transaction 1
    }
}