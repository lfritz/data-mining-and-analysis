#include "itemsetstest.h"

#include <set>
#include <vector>

#include <itemsets.h>
#include <prefixtree.h>

using std::set;
using std::vector;

// test is_subset function
TEST_F(ItemsetsTest, is_subset) {
    EXPECT_TRUE(is_subset(vector<int>{1,3,5}, vector<int>{1,2,3,5}));
    EXPECT_TRUE(is_subset(vector<int>{2,3,5}, vector<int>{1,2,3,5}));
    EXPECT_TRUE(is_subset(vector<int>{1,3,5}, vector<int>{1,3,5}));
    EXPECT_TRUE(is_subset(vector<int>{}, vector<int>{1,2,3}));
    EXPECT_TRUE(is_subset(vector<int>{}, vector<int>{}));

    EXPECT_FALSE(is_subset(vector<int>{1,3,5,7}, vector<int>{1,2,3,5}));
    EXPECT_FALSE(is_subset(vector<int>{1,3,5,7}, vector<int>{1,3,5}));
}

// test each_k_subset function
TEST_F(ItemsetsTest, each_k_subset) {
    vector<int> items = { 1, 2, 3, 4 };
    vector<set<vector<int>>> subsets = {
        { {} },
        { {1}, {2}, {3}, {4} },
        { {1,2}, {1,3}, {1,4}, {2,3}, {2,4}, {3,4} },
        { {1,2,3}, {1,2,4}, {1,3,4}, {2,3,4} },
        { {1,2,3,4} },
        { }
    };
    for (int i = 0; i < 6; ++i) {
        set<vector<int>> result;
        each_k_subset(i, items, [&result](const vector<int>& v) {
            result.insert(v);
        });
        EXPECT_EQ(subsets[i], result);
    }
}

// test immediate_subsets_in function
TEST_F(ItemsetsTest, immediate_subsets_in) {
    Node root;
    Node * node1 = root.addChild(1);
    node1->addChild(2)->addChild(3);
    node1->addChild(3)->addChild(5);
    node1->addChild(5);
    root.addChild(2);
    Node * node3 = root.addChild(3);
    node3->addChild(5);
    node3->addChild(6);
    root.addChild(5)->addChild(6);
    root.addChild(6);

    vector<int> itemset1 = {1,3,5};
    vector<int> itemset2 = {1,2,3};
    vector<int> itemset3 = {3,5,6};
    EXPECT_TRUE(immediate_subsets_in(root, itemset1));
    EXPECT_FALSE(immediate_subsets_in(root, itemset2));
    EXPECT_TRUE(immediate_subsets_in(root, itemset3));
}
