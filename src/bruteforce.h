#pragma once

// Brute-force algorithm to find frequent items in a database of transactions
// and items, from chapter 8.2 of Data Mining and Analysis: Fundamental
// Concepts and Algorithms by Mohammed J. Zaki and Wagner Meira Jr.

#include <map>
#include <vector>

struct TransactionDatabase;

// Frequent itemsets from a database. Maps each frequent itemset to its
// support.
typedef std::map<std::vector<int>, int> FrequentItemsets;

// Brute-force algorithm to find frequent items in the database.
FrequentItemsets brute_force(const TransactionDatabase& d,
                             unsigned int minsup);
