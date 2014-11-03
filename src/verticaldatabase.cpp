#include "verticaldatabase.h"

#include "transactiondatabase.h"

using boost::dynamic_bitset;
using std::string;
using std::vector;

VerticalDatabase::VerticalDatabase(vector<string> items,
                                   vector<vector<int>> transactions) :
ts(transactions.size()),
bs(items.size(), dynamic_bitset<>(ts)),
is(items) {
    for (int tid = 0; tid < ts; ++tid)
        for (int item_id : transactions[tid])
            bs[item_id][tid] = 1;
}

VerticalDatabase::VerticalDatabase(const TransactionDatabase& d) :
ts(d.nTransactions()),
bs(d.nItems(), dynamic_bitset<>(ts)),
is(d.is) {
    for (int tid = 0; tid < ts; ++tid)
        for (int item_id : d.ts[tid])
            bs[item_id][tid] = 1;
}

void VerticalDatabase::printItemset(std::ostream& out,
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
