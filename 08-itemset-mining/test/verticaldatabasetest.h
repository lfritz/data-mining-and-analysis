#pragma once

#include <gtest/gtest.h>
#include <string>
#include <vector>

// Unit tests for the 'VerticalDatabase' class.
class VerticalDatabaseTest : public testing::Test {
protected:
    std::vector<std::string> items;
    std::vector<std::vector<int>> transactions;

public:
    VerticalDatabaseTest();
};
