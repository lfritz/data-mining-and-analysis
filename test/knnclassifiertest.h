#pragma once

#include <Eigen/Core>
#include <gtest/gtest.h>
#include <vector>

#include <knnclassifier.h>

// Unit tests for class K Nearest Neighbor classifier implementation.
class KnnClassifierTest : public testing::Test {
protected:
    std::vector<Eigen::VectorXd> x;
    std::vector<int> y;
    KnnClassifier c;
    std::vector<Eigen::VectorXd> test_x;

public:
    KnnClassifierTest();
};
