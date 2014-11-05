#pragma once

#include <gtest/gtest.h>

// Unit tests for the functions in kmeans.h.
class KmeansTest : public testing::Test {
protected:
    std::vector<std::vector<double>> points;

public:
    KmeansTest();
};
