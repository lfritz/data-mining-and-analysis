#include "bruteforce.h"

#include <functional>

#include "database.h"
#include "itemsets.h"

using std::vector;

// Compute the support for an itemset.
int support(const Database& d, const vector<int>& itemset) {
    int count = 0;
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

FrequentItemsets brute_force(const Database& d, int minsup) {
    FrequentItemsets result;

    each_candidate([&d, minsup, &result](const vector<int>& candidate) {
        int s = support(d, candidate);
        if (s >= minsup)
            result[candidate] = s;
    }, d.nItems());

    return result;
}
