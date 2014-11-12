#pragma once

#include <Eigen/Core>
#include <gtest/gtest.h>

#include <kernelkmeans.h>

// Unit tests for the functions in kernelkmeans.h.
class KernelKmeansTest : public testing::Test {
protected:
    Eigen::MatrixXd kernel;
    std::vector<std::vector<unsigned>> clusters;

public:
    KernelKmeansTest();
};
