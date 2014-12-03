#pragma once

#include <functional>

#include <gtest/gtest.h>

// Unit tests for functions in algorithm.h.
class AlgorithmTest : public testing::Test {
protected:
    std::function<double(double)> f;

public:
    AlgorithmTest();
};
