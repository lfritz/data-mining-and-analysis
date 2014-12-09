#pragma once

#include <Eigen/Core>
#include <gtest/gtest.h>
#include <vector>

// Unit tests for the functions in naivebayesclassifier.h.
class NaiveBayesClassifierTest : public testing::Test {
protected:
    std::vector<Eigen::VectorXd> x;
    std::vector<int> y;

public:
    NaiveBayesClassifierTest();
};
