#include "bruteforce.h"

#include <functional>

#include "itemsets.h"
#include "transactiondatabase.h"

using std::vector;

// Compute the support for an itemset.
unsigned int support(const TransactionDatabase& d,
                     const vector<int>& itemset) {
    unsigned int count = 0;
    for (const vector<int>& transaction : d.ts)
        count += is_subset(itemset, transaction);
    return count;
}

void each_candidate(std::function<void(const vector<int>&)> f,
                    vector<int>& candidate,
                    int nItems,
                    int from) {
    for (int i = from; i < nItems; ++i) {
        candidate.push_back(i);
        f(candidate);
        each_candidate(f, candidate, nItems, i+1);
        candidate.pop_back();
    }
}

// Generate all possible non-empty itemsets using depth-first traversal of the
// prefix tree.
void each_candidate(std::function<void(const vector<int>&)> f, int nItems) {
    vector<int> candidate;
    each_candidate(f, candidate, nItems, 0);
}

FrequentItemsets brute_force(const TransactionDatabase& d,
                             unsigned int minsup) {
    FrequentItemsets result;

    each_candidate([&d, minsup, &result](const vector<int>& candidate) {
        unsigned int s = support(d, candidate);
        if (s >= minsup)
            result[candidate] = s;
    }, d.nItems());

    return result;
}
