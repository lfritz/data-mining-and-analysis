#include "itemsets.h"

#include "prefixtree.h"

using std::vector;

bool is_subset(const vector<int>& a, const vector<int>& b) {
    int size_a = a.size(),
        size_b = b.size();
    if (size_a > size_b)
        return false;

    int i = 0;
    for (int x1 : a) {
        while (true) {
            if (i >= size_b)
                return false;
            int x2 = b[i];
            if (x2 > x1)
                return false;
            ++i;
            if (x2 == x1)
                break;
        }
    }
    return true;
}

void each_k_subset(unsigned int k,
                   vector<int> itemset,
                   std::function<void(const vector<int>&)> f) {
    unsigned int s = itemset.size();

    // special cases
    if (k > s)
        return;
    if (k == 0) {
        f(vector<int>{});
        return;
    }

    // prepare vectors
    vector<unsigned int> indices(k);
    vector<unsigned int> max_index(k);
    vector<int> subset(k);
    for (unsigned int i = 0; i < k; ++i)
        max_index[i] = s-k+i;
    for (unsigned int i = 0; i < k; ++i)
        indices[i] = i;

    // loop until there are no more subsets
    while (true) {
        // call f
        for (unsigned int j = 0; j < k; ++j)
            subset[j] = itemset[indices[j]];
        f(subset);

        // go back to an index we can increment
        unsigned int i = k-1;
        while (indices[i] == max_index[i]) {
            if (i == 0)
                return;
            --i;
        }

        // increment index
        indices[i] += 1;

        // set remaining indices
        for (unsigned int j = i+1, value = indices[i]+1;
             j < k;
             ++j, ++value)
            indices[j] = value;
    }
}

bool immediate_subsets_in(const Node& tree, const vector<int>& itemset) {
    int itemset_size = itemset.size();
    int subset_size = itemset_size - 1;
    vector<int> subset(subset_size);
    for (int i = 0; i < itemset_size; ++i) {
        // copy 'itemset', but without element 'i'
        for (int j = i; j < subset_size; ++j)
            subset[j] = itemset[j+(j>=i)];
        if ( ! tree.lookup(subset))
            return false;
    }
    return true;
}
