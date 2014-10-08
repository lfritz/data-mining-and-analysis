#pragma once

// Helper functions for working with itemsets. The itemset vectors are assumed
// to be sorted and without duplicates.

#include <functional>
#include <vector>

class Node;

// Is itemset 'a' a subset of itemset 'b'?
bool is_subset(const std::vector<int>& a, const std::vector<int>& b);

// Call 'f' with each subset of 'itemset' of size 'k'.
void each_k_subset(unsigned int k,
                   std::vector<int> itemset,
                   std::function<void(const std::vector<int>&)> f);

// Given an itemset of size k, check if all subsets of size k-1 are in the
// tree.
bool immediate_subsets_in(const Node& tree, const std::vector<int>& itemset);
