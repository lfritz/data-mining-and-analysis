#pragma once

#include <gtest/gtest.h>

#include <prefixtree.h>

// Unit tests for the 'Node' class template.
class NodeTest : public testing::Test {
protected:
    // Sample tree:
    //    root
    //    /  |
    //   2   4
    //  /
    // 1
    Node root;
    Node * node2;
    Node * node4;
    Node * node21;

public:
    NodeTest();
};
