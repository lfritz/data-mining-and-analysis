#include "vectormathtest.h"

#include <vectormath.h>

using std::vector;

TEST_F(VectorMathTest, add) {
    vector<double> x = { 1.2,  3.4 };
    vector<double> y = { 0.3, -1.5 };
    vector<double> z = { 1.5,  1.9 };
    vector<double> result = add(x, y);
    EXPECT_DOUBLE_EQ(z[0], result[0]);
    EXPECT_DOUBLE_EQ(z[1], result[1]);
}

TEST_F(VectorMathTest, subtract) {
    vector<double> x = { 1.2,  3.4 };
    vector<double> y = { 0.3, -1.5 };
    vector<double> z = { 0.9,  4.9 };
    vector<double> result = subtract(x, y);
    EXPECT_DOUBLE_EQ(z[0], result[0]);
    EXPECT_DOUBLE_EQ(z[1], result[1]);
}

TEST_F(VectorMathTest, norm) {
    vector<double> x = { 1.2,  3.4 };
    EXPECT_DOUBLE_EQ(3.605551275463989, norm(x));
}

TEST_F(VectorMathTest, distance) {
    vector<double> x = { 1.2,  3.4 };
    vector<double> y = { 0.3, -1.5 };
    EXPECT_EQ(4.98196748283246, distance(x, y));
}
