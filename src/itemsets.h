#pragma once

// Helper functions for working with itemsets. The itemset vectors are assumed
// to be sorted and without duplicates.

#include <boost/dynamic_bitset.hpp>
#include <functional>
#include <vector>

class Node;

// Is itemset 'a' a subset of itemset 'b'?
bool is_subset(const std::vector<int>& a, const std::vector<int>& b);

// Call 'f' with each subset of 'itemset' of size 'k'.
void each_k_subset(unsigned int k,
                   const std::vector<int>& itemset,
                   std::function<void(const std::vector<int>&)> f);

// Given an itemset of size k, check if all subsets of size k-1 are in the
// tree.
bool immediate_subsets_in(const Node& tree, const std::vector<int>& itemset);

// Get an itemset with all items in 'a', except the ones in 'b'.
std::vector<int> itemset_without(const std::vector<int> itemset_a,
                                 const std::vector<int> itemset_b);

// Get a diffset for a single-item itemset.
std::vector<int> diffset_for_single_item(boost::dynamic_bitset<> tids);
