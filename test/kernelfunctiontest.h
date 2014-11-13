#pragma once

#include <Eigen/Core>
#include <gtest/gtest.h>

// Unit tests for the functions in kernelfunction.h.
class KernelFunctionTest : public testing::Test {
protected:
    std::vector<Eigen::VectorXd> points;

public:
    KernelFunctionTest();
};
