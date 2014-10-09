#include "transactiondatabase.h"

#include <algorithm>
#include <cassert>

using std::string;
using std::vector;

// Initialize database using a list of item ids for each transaction.
TransactionDatabase::TransactionDatabase(vector<string> items,
                                         vector<vector<int>> transactions) :
    ts(transactions),
    is(items) {
    int nItems = is.size();
    for (vector<int>& t : ts) {
        std::sort(t.begin(), t.end());
        for (int i : t) {
            assert(i >= 0);
            assert(i < nItems);
        }
    }
}

void TransactionDatabase::printItemset(std::ostream& out,
                                       const vector<int>& itemset,
                                       const string& sep) const {
    bool first = true;
    for (int i : itemset) {
        if (first)
            first = false;
        else
            out << sep;
        out << is[i];
    }
}
