#include "prefixtree.h"

#include <cassert>

#include "transactiondatabase.h"

using std::function;
using std::vector;

const Node * Node::getChild(int item) const {
    if (c.count(item))
        return c.at(item).get();
    return nullptr;
}

Node * Node::getChild(int item) {
    if (c.count(item))
        return c.at(item).get();
    return nullptr;
}

const Node * Node::lookup(vector<int> prefix) const {
    const Node * node = this;
    for (int i : prefix) {
        node = node->getChild(i);
        if ( ! node)
            return nullptr;
    }
    return node;
}

Node * Node::lookup(vector<int> prefix) {
    Node * node = this;
    for (int i : prefix) {
        node = node->getChild(i);
        if ( ! node)
            return nullptr;
    }
    return node;
}

vector<int> Node::children() const {
    vector<int> result;
    for (const auto& kv : c)
        result.push_back(kv.first);
    return result;
}

void Node::addChild(int item_id) {
    c[item_id] = std::make_unique<Node>();
}

void Node::removeChild(int item_id) {
    c.erase(item_id);
}

bool Node::eachNode(int level, NodeCallback f) {
    vector<int> prefix;
    return eachNode(level, f, prefix);
}

bool Node::eachNode(int level, NodeCallback f, vector<int>& prefix) {
    assert(level >= 0);
    if (level == 0) {
        return f(prefix, *this);
    } else {
        vector<int> eraseThese;
        for (const auto& kv : c) {
            int i = kv.first;
            prefix.push_back(i);
            bool keep = kv.second->eachNode(level - 1, f, prefix);
            if ( ! keep)
                eraseThese.push_back(i);
            prefix.pop_back();
        }
        for (int i : eraseThese)
            c.erase(i);
        return eraseThese.empty() || ( ! isLeaf());
    }
}

void Node::printTree(std::ostream& out,
                     const TransactionDatabase& database,
                     const std::string& sep) const {
    vector<int> prefix;
    printTree(out, database, prefix, sep);
}

void Node::printTree(std::ostream& out,
                     const TransactionDatabase& database,
                     std::vector<int> prefix,
                     const std::string& sep) const {
    database.printItemset(out, prefix, sep);
    out << " " << s << std::endl;
    for (const auto& kv : c) {
        int i = kv.first;
        prefix.push_back(i);
        kv.second->printTree(out, database, prefix, sep);
        prefix.pop_back();
    }
}
