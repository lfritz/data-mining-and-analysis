#pragma once

#include <boost/dynamic_bitset.hpp>
#include <ostream>
#include <string>
#include <vector>

class TransactionDatabase;

// Binary database for a frequent itemset mining task. Each item is stored as
// a bitset indicating which transactions it is included in.
struct VerticalDatabase {
    int ts; // number of transactions

    // each item as a bitset
    std::vector<boost::dynamic_bitset<>> bs;

    // item names
    std::vector<std::string> is;

    // Initialize database using a list of item ids for each transaction.
    VerticalDatabase(std::vector<std::string> items,
                     std::vector<std::vector<int>> transactions);

    // Create vertical database from transaction database.
    VerticalDatabase(const TransactionDatabase& d);

    int nItems() const { return is.size(); }
    int nTransactions () const { return ts; }

    // Print an itemset using the database's item names.
    void printItemset(std::ostream& out,
                      const std::vector<int>& itemset,
                      const std::string& sep="") const;
};
