#pragma once

#include <map>
#include <vector>

// An association rule of the form x -> y.
typedef std::tuple<std::vector<int>, // x
                   std::vector<int>, // y
                   unsigned int,     // support
                   double>           // confidence
        AssociationRule;

// Frequent itemsets from a database. Maps each frequent itemset to its
// support.
typedef std::map<std::vector<int>, int> FrequentItemsets;

// Find all proper subsets of an itemset, ie, all subsets except the empty set
// and 'itemset' itself.
std::vector<std::vector<int>> proper_subsets(const std::vector<int>& itemset);

// Given the frequent items in a database, find all association rules that are
// frequent and strong.
std::vector<AssociationRule> association_rules(const FrequentItemsets& f,
                                               double minconf);
