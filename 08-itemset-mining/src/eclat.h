#pragma once

// Eclat algorithm to find frequent items in a database of transactions and
// items, from chapter 8.2 of Data Mining and Analysis: Fundamental Concepts
// and Algorithms by Mohammed J. Zaki and Wagner Meira Jr.

#include <map>
#include <vector>

struct VerticalDatabase;

// Frequent itemsets from a database. Maps each frequent itemset to its
// support.
typedef std::map<std::vector<int>, int> FrequentItemsets;

// Eclat algorithm to find frequent items in the database.
FrequentItemsets eclat(const VerticalDatabase& d, unsigned int minsup);
