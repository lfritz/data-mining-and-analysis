#include "eclat.h"

#include <boost/dynamic_bitset.hpp>
#include <map>
#include <utility> // for std::pair
#include <vector>

#include "verticaldatabase.h"

using boost::dynamic_bitset;
using std::pair;
using std::vector;

typedef pair<int, dynamic_bitset<>> Candidate;

void eclat_recursive(const vector<int>& prefix,
                     const vector<Candidate>& p,
                     unsigned int minsup,
                     FrequentItemsets& result) {
    auto size = p.size();
    for (unsigned int i = 0; i < size; ++i) {
        // take candidate a from 'p'
        const Candidate& candidate_a = p[i];
        int a = candidate_a.first;
        vector<int> itemset_a = prefix;
        itemset_a.push_back(a);
        const dynamic_bitset<>& bitset_a = candidate_a.second;
        result[itemset_a] = bitset_a.count();

        // look for frequent itemsets with candidate a as prefix
        vector<Candidate> pa;
        for (unsigned int j = i+1; j < size; ++j) {
            // take candidate b from 'p'
            const Candidate& candidate_b = p[j];
            int b = candidate_b.first;
            const dynamic_bitset<>& bitset_b = candidate_b.second;

            // new candidate ab
            dynamic_bitset<> bitset_ab = bitset_a & bitset_b;
            if (bitset_ab.count() >= minsup)
                pa.push_back(Candidate(b, bitset_ab));
        }

        // recurse!
        if ( ! pa.empty())
            eclat_recursive(itemset_a, pa, minsup, result);
    }
}

FrequentItemsets eclat(const VerticalDatabase& d, unsigned int minsup) {
    // initial candidates: frequent single-item itemsets
    vector<Candidate> candidates;
    int nItems = d.nItems();
    for (int i = 0; i < nItems; ++i) {
        dynamic_bitset<> b = d.bs[i];
        if (b.count() >= minsup)
            candidates.push_back(Candidate(i, b));
    }

    // run algorithm
    FrequentItemsets result;
    vector<int> prefix;
    eclat_recursive(prefix, candidates, minsup, result);

    return result;
}
