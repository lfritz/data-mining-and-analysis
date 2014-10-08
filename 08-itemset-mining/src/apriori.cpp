#include "apriori.h"

#include <map>
#include <vector>

#include "database.h"
#include "itemsets.h"
#include "prefixtree.h"

using std::vector;

FrequentItemsets apriori(const Database& d, int minsup) {
    FrequentItemsets result;

    // initial prefix tree with single-item itemsets
    Node tree;
    unsigned int nItems = d.nItems();
    for (unsigned int i = 0; i < nItems; ++i)
        tree.addChild(i);

    // level-wise processing
    for (unsigned int k = 1; k <= nItems; ++k) {
        // compute support for nodes at level k
        for (const vector<int>& t : d.ts) {
            each_k_subset(k, t, [&tree, &d](const vector<int>& v) {
                if (Node * node = tree.lookup(v))
                    ++(node->support());
            });
        }

        // check support and add nodes to results or purge them
        bool keep = tree.eachNode(k, [&result, minsup](vector<int> itemset,
                                                       Node& node) {
            int s = node.support();
            if (s < minsup)
                return false;
            result[itemset] = s;
            return true;
        });
        if ( ! keep)
            break;

        // extend prefix tree
        keep = tree.eachNode(k-1, [&tree,&d](vector<int> itemset, Node& node) {
            vector<int> children = node.children();
            int size = children.size();
            for (int i = 0; i < size; ++i) {
                int child_id = children[i];
                Node * child = node.getChild(child_id);
                itemset.push_back(child_id);
                for (int j = i+1; j < size; ++j) {
                    int sibling_id = children[j];
                    vector<int> new_itemset(itemset);
                    new_itemset.push_back(sibling_id);
                    if (immediate_subsets_in(tree, new_itemset)) {
                        child->addChild(sibling_id);
                    }
                }
                itemset.pop_back();
                if (child->isLeaf())
                    node.removeChild(child_id);
            }
            return ! node.isLeaf();

        });
        if ( ! keep)
            break;
    }

    return result;
}
