#pragma once

#include <Eigen/Core>
#include <gtest/gtest.h>

// Unit tests for the functions in kmeans.h.
class KmeansTest : public testing::Test {
protected:
    std::vector<Eigen::VectorXd> points;

public:
    KmeansTest();
};
