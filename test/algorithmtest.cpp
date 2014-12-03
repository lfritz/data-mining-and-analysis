#include "algorithmtest.h"

#include <algorithm.h>

using std::vector;

AlgorithmTest::AlgorithmTest() :
f([](double x) { return (x+4)*(x+1)*(x-2); }) {
}

TEST_F(AlgorithmTest, arg_max) {
    EXPECT_EQ(-3, arg_max(-4, 3, f));
    EXPECT_EQ(-3, arg_max(-3, 3, f));
    EXPECT_EQ(-3, arg_max(-10, -2, f));
}

TEST_F(AlgorithmTest, arg_min) {
    EXPECT_EQ(1, arg_min(-4, 3, f));
    EXPECT_EQ(1, arg_min(1, 3, f));
    EXPECT_EQ(1, arg_min(-4, 2, f));
}
