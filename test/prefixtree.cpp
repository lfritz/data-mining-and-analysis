#include <catch.hpp>

#include <utility> // for std::pair

#include <prefixtree.h>

using std::pair;
using std::vector;

TEST_CASE("PrefixTree") {
    // Sample tree:
    //    root
    //    /  |
    //   2   4
    //  /
    // 1
    Node root;
    root.addChild(2);
    Node * node2 = root.getChild(2);
    root.addChild(4);
    Node * node4 = root.getChild(4);
    node2->addChild(1);
    Node * node21 = node2->getChild(1);

    SECTION("isLeaf") {
        CHECK_FALSE(root.isLeaf());
        CHECK_FALSE(node2->isLeaf());
        CHECK(node4->isLeaf());
        CHECK(node21->isLeaf());
    }

    SECTION("getChild") {
        CHECK(root.getChild(1) == nullptr);
        CHECK(root.getChild(2) == node2);
    }

    SECTION("lookup") {
        CHECK(root.lookup(vector<int>{3}) == nullptr);
        CHECK(root.lookup(vector<int>{}) == &root);
        CHECK(root.lookup(vector<int>{2}) == node2);
        CHECK(root.lookup(vector<int>{2,1}) == node21);
        CHECK(root.lookup(vector<int>{4}) == node4);
    }

    SECTION("children") {
        vector<int> children_root = { 2, 4 };
        vector<int> children2 = { 1 };
        vector<int> empty;
        CHECK(root.children() == children_root);
        CHECK(node2->children() == children2);
        CHECK(node4->children() == empty);
        CHECK(node21->children() == empty);
    }

    SECTION("addChild") {
        node4->addChild(3);
        Node * node43 = node4->getChild(3);
        CHECK(node4->getChild(3) == node43);
    }

    SECTION("removeChild") {
        vector<int> just4 = { 4 };
        root.removeChild(2);
        CHECK(root.children() == just4);
    }

    SECTION("iterating over nodes with 'eachNode' member function") {
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
            CHECK(nodes == nodes_by_level[level]);
            CHECK(keep);
        }
    }

    SECTION("deleting leaf node with 'eachNode' member function") {
        // delete node 4
        bool keep = root.eachNode(1, [](vector<int> itemset, Node&) {
            if (itemset == vector<int>{4})
                return false;
            return true;
        });
        CHECK(root.getChild(2) == node2);
        CHECK(root.getChild(4) == nullptr);
        CHECK(keep);
    }

    SECTION("deleting subtree with 'eachNode' member function") {
        // delete node 21, which should also remove node 2
        bool keep = root.eachNode(2, [](vector<int>, Node&) { return false; });
        CHECK(root.getChild(4) == node4);
        CHECK(root.getChild(2) == nullptr);
        CHECK(keep);
    }

    SECTION("deleting multiple subtrees with 'eachNode' member function") {
        // delete nodes 2 and 4, which should wipe out the whole tree
        bool keep = root.eachNode(1, [](vector<int>, Node&) { return false; });
        CHECK(root.isLeaf());
        CHECK_FALSE(keep);
    }
}
