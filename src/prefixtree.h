#pragma once

// Defines a class for a prefix tree as used by the Apriori algorithm.

#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

struct TransactionDatabase;

class Node;

// Function to be called by Node::eachNode with the prefix for the node and the
// node itself. If it returns false, the node will be deleted.
typedef std::function<bool(std::vector<int> prefix, Node& node)>
        NodeCallback;

// A node in a prefix tree. The prefix tree is represented by the root node.
class Node {
    std::map<int, std::unique_ptr<Node>> c; // child nodes
    unsigned int s;                         // support

public:
    // Create a node without children and support 0.
    Node() : c(), s(0) { }

    // The node's support.
    unsigned int& support() { return s; }

    // Is the node a leaf node (one with no children)?
    bool isLeaf() const { return c.empty(); }

    // Get the child for the given item id. Returns nullptr if there is no such
    // child.
    const Node * getChild(int item) const;
    Node * getChild(int item);

    // Get the node for the given sequence of item ids. Returns nullptr if it
    // can't be found.
    const Node * lookup(std::vector<int> prefix) const;
    Node * lookup(std::vector<int> prefix);

    // Return a (sorted) vector with the items for all children.
    std::vector<int> children() const;

    // Add a child (with support 0).
    void addChild(int item_id);

    // Remove a child.
    void removeChild(int item_id);

    // Call a function for each node at the given level below this node. If
    // 'level' is 0, 'f' will be called with this node.
    bool eachNode(int level, NodeCallback f);

    // Print the entire tree to 'out'.
    void printTree(std::ostream& out,
                   const TransactionDatabase& database,
                   const std::string& sep="") const;

private:
    // Helper function for 'eachNode'.
    bool eachNode(int level, NodeCallback f, std::vector<int>& prefix);

    // Helper function for 'printTree'.
    void printTree(std::ostream& out,
                   const TransactionDatabase& database,
                   std::vector<int> prefix,
                   const std::string& sep) const;
};
