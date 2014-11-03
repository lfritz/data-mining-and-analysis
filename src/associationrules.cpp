#include "associationrules.h"

#include "itemsets.h"

using std::vector;

vector<vector<int>> proper_subsets(const vector<int>& itemset) {
    vector<vector<int>> result;
    unsigned int size = itemset.size();
    if (size < 2)
        return result;
    vector<bool> included(size, false);
    vector<int> x;
    unsigned int i = size;
    while (true) {
        if (i == size) {
            unsigned int x_size = x.size();
            if (x_size > 0 && x_size < size)
                result.push_back(x);
            --i;
        } else {
            if (included[i]) {
                x.pop_back();
                included[i] = false;
                if (i == 0)
                    break;
                --i;
            } else {
                x.push_back(itemset[i]);
                included[i] = true;
                i = size;
            }
        }
    }
    return result;
}

vector<AssociationRule> association_rules(const FrequentItemsets& f,
                                          double minconf) {
    vector<AssociationRule> result;

    for (const auto& kv : f) {
        // take a frequent itemset z
        const vector<int>& z = kv.first;
        if (z.size() < 2)
            continue;
        unsigned int support_z = kv.second;

        // take all proper subsets of z
        vector<vector<int>> xs = proper_subsets(z);

        // sort subsets from shortest to longest
        std::sort(xs.begin(), xs.end(), [](const vector<int>& a,
                                           const vector<int>& b) {
            return a.size() > b.size();
        });

        while ( ! xs.empty()) {
            // x is a subset of maximal size
            // we're looking at the association rule x->y, where y = z\x
            vector<int> x = xs.back();
            xs.pop_back();

            // check confidence for x -> y
            double conf = (double)support_z / (double)f.at(x);
            if (conf >= minconf) {
                // strong association rule: add to result
                vector<int> y = itemset_without(z, x);
                result.push_back(AssociationRule({x}, {y}, support_z, conf));
            } else {
                // not a strong association rule: remove all subsets of x,
                // since these will also not be strong association rules
                std::remove_if(xs.begin(),
                               xs.end(),
                               [&x](const vector<int>& w) {
                    return is_subset(w, x);
                });
            }
        }
    }

    return result;
}
