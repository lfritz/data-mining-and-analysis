#include "prefixtreetest.h"

#include <utility> // for std::pair

using std::pair;
using std::vector;

NodeTest::NodeTest() : root() {
    root.addChild(2);
    node2 = root.getChild(2);
    root.addChild(4);
    node4 = root.getChild(4);
    node2->addChild(1);
    node21 = node2->getChild(1);
}

// test 'isLeaf' member function
TEST_F(NodeTest, isLeaf) {
    EXPECT_FALSE(root.isLeaf());
    EXPECT_FALSE(node2->isLeaf());
    EXPECT_TRUE(node4->isLeaf());
    EXPECT_TRUE(node21->isLeaf());
}

// test 'getChild' member function
TEST_F(NodeTest, getChild) {
    EXPECT_EQ(nullptr, root.getChild(1));
    EXPECT_EQ(node2, root.getChild(2));
}

// test 'lookup' member function
TEST_F(NodeTest, lookup) {
    EXPECT_EQ(nullptr, root.lookup(vector<int>{3}));
    EXPECT_EQ(&root, root.lookup(vector<int>{}));
    EXPECT_EQ(node2, root.lookup(vector<int>{2}));
    EXPECT_EQ(node21, root.lookup(vector<int>{2,1}));
    EXPECT_EQ(node4, root.lookup(vector<int>{4}));
}

// test 'children' member function
TEST_F(NodeTest, children) {
    vector<int> children_root = { 2, 4 };
    vector<int> children2 = { 1 };
    vector<int> empty;
    EXPECT_EQ(children_root, root.children());
    EXPECT_EQ(children2, node2->children());
    EXPECT_EQ(empty, node4->children());
    EXPECT_EQ(empty, node21->children());
}

// test 'addChild' member function
TEST_F(NodeTest, addChild) {
    node4->addChild(3);
    Node * node43 = node4->getChild(3);
    EXPECT_EQ(node43, node4->getChild(3));
}

// test 'removeChild' member function
TEST_F(NodeTest, removeChild) {
    vector<int> just4 = { 4 };
    root.removeChild(2);
    EXPECT_EQ(just4, root.children());
}

// test iterating over nodes with 'eachNode' member function
TEST_F(NodeTest, eachNode1) {
    vector<vector<pair<vector<int>, Node *>>> nodes_by_level = {
        { {{}, &root} },
        { {{2}, node2}, {{4}, node4} },
        { {{2,1}, node21} },
        { }
    };
    for (int level = 0; level < 4; ++level) {
        vector<pair<vector<int>, Node *>> nodes;
        bool keep = root.eachNode(level, [&nodes](vector<int> itemset,
                                                   Node& node) {
            nodes.push_back({itemset, &node});
            return true;
        });
        EXPECT_EQ(nodes_by_level[level], nodes);
        EXPECT_TRUE(keep);
    }
}

// test deleting nodes with 'eachNode' member function
TEST_F(NodeTest, eachNode2) {
    // delete node 4
    bool keep = root.eachNode(1, [](vector<int> itemset, Node&) {
        if (itemset == vector<int>{4})
            return false;
        return true;
    });
    EXPECT_EQ(node2, root.getChild(2));
    EXPECT_EQ(nullptr, root.getChild(4));
    EXPECT_TRUE(keep);
}

// test deleting nodes with 'eachNode' member function
TEST_F(NodeTest, eachNode3) {
    // delete node 21, which should also remove node 2
    bool keep = root.eachNode(2, [](vector<int>, Node&) { return false; });
    EXPECT_EQ(node4, root.getChild(4));
    EXPECT_EQ(nullptr, root.getChild(2));
    EXPECT_TRUE(keep);
}

// test deleting nodes with 'eachNode' member function
TEST_F(NodeTest, eachNode4) {
    // delete nodes 2 and 4, which should wipe out the whole tree
    bool keep = root.eachNode(1, [](vector<int>, Node&) { return false; });
    EXPECT_TRUE(root.isLeaf());
    EXPECT_FALSE(keep);
}
