#pragma once

#include <gtest/gtest.h>

#include <kernelkmeans.h>

// Unit tests for the functions in kernelkmeans.h.
class KernelKmeansTest : public testing::Test {
protected:
    Kernel kernel;
    std::vector<std::vector<unsigned>> clusters;

public:
    KernelKmeansTest();
};
