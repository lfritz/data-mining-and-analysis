#pragma once

#include <gtest/gtest.h>
#include <memory>

#include <apriori.h>
#include <bruteforce.h>
#include <declat.h>
#include <eclat.h>
#include <transactiondatabase.h>
#include <verticaldatabase.h>

// Unit tests for frequent itemset finding functions.
class FrequentItemsetTest : public testing::Test {
protected:
    std::unique_ptr<TransactionDatabase> td;
    std::unique_ptr<VerticalDatabase> vd;
    int minsup;
    FrequentItemsets correct_result;

public:
    FrequentItemsetTest();
};
