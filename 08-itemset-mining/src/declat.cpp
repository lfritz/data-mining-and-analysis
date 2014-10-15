#include "declat.h"

#include <boost/dynamic_bitset.hpp>

#include "itemsets.h"
#include "verticaldatabase.h"

using boost::dynamic_bitset;
using std::vector;

struct Candidate {
    int last_item;
    vector<int> diffset;
    unsigned int support;
};

void declat_recursive(const vector<int>& prefix,
                      const vector<Candidate>& p,
                      unsigned int minsup,
                      FrequentItemsets& result) {
    auto size = p.size();
    for (unsigned int i = 0; i < size; ++i) {
        // take candidate a from p
        const Candidate& a = p[i];
        vector<int> itemset_a = prefix;
        itemset_a.push_back(a.last_item);
        result[itemset_a] = a.support;

        // look for frequent itemsets with candidate a as prefix
        vector<Candidate> pa;
        for (unsigned int j = i+1; j < size; ++j) {
            // take candidate b from p
            const Candidate& b = p[j];

            // new candidate ab
            Candidate ab;
            ab.last_item = b.last_item;
            ab.diffset = itemset_without(b.diffset, a.diffset);
            ab.support = a.support - ab.diffset.size();
            if (ab.support >= minsup)
                pa.emplace_back(ab);
        }

        // recurse!
        if ( ! pa.empty())
            declat_recursive(itemset_a, pa, minsup, result);
    }
}

FrequentItemsets declat(const VerticalDatabase& d, unsigned int minsup) {
    // initial candidates: frequent single-item itemsets
    vector<Candidate> p;
    int nItems = d.nItems();
    for (int i = 0; i < nItems; ++i) {
        dynamic_bitset<> b = d.bs[i];
        unsigned int support = b.count();
        if (support >= minsup)
            p.push_back({i, diffset_for_single_item(b), support});
    }

    // run algorithm
    FrequentItemsets result;
    vector<int> prefix;
    declat_recursive(prefix, p, minsup, result);

    return result;
}
