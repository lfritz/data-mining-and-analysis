#pragma once

#include <gtest/gtest.h>
#include <memory>

#include <apriori.h>
#include <bruteforce.h>
#include <database.h>

// Unit tests for frequent itemset finding functions.
class FrequentItemsetTest : public testing::Test {
protected:
    std::unique_ptr<Database> database;
    int minsup;
    FrequentItemsets correct_result;

public:
    FrequentItemsetTest();
};
