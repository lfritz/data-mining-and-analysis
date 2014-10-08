#pragma once

#include <string>
#include <vector>

// Binary database for a frequent itemset mining task.
struct Database {
    // each transaction as a sorted vector of item ids
    std::vector<std::vector<int>> ts;

    // item names
    std::vector<std::string> is;

    // Initialize database using a list of item ids for each transaction.
    Database(std::vector<std::string> items,
             std::vector<std::vector<int>> transactions);

    int nItems() const { return is.size(); }
    int nTransactions () const { return ts.size(); }

    // Print an itemset using the database's item names.
    void printItemset(std::ostream& out,
                      const std::vector<int>& itemset,
                      const std::string& sep="") const;
};
