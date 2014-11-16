#include "kernelfunctiontest.h"

#include "helper.h"

#include <kernelfunction.h>

using Eigen::Vector2d;
using Eigen::MatrixXd;

KernelFunctionTest::KernelFunctionTest() {
    points = {
        Vector2d(1.0,  0.0),
        Vector2d(1.0,  2.0),
        Vector2d(0.0, -1.0)
    };
}

TEST_F(KernelFunctionTest, homogeneous_polynomial_kernel) {
    MatrixXd kernel = homogeneous_polynomial_kernel(points, 2.0);
    MatrixXd correct_kernel(3,3);
    correct_kernel << 1.0,  1.0, 0.0,
                      1.0, 25.0, 4.0,
                      0.0,  4.0, 1.0;
    EXPECT_PRED2(is_approx_m, kernel, correct_kernel);
}

TEST_F(KernelFunctionTest, inhomogeneous_polynomial_kernel) {
    MatrixXd kernel = inhomogeneous_polynomial_kernel(points, 2.0, 1.0);
    MatrixXd correct_kernel(3,3);
    correct_kernel << 4.0,  4.0, 1.0,
                      4.0, 36.0, 1.0,
                      1.0,  1.0, 4.0;
    EXPECT_PRED2(is_approx_m, kernel, correct_kernel);
}

TEST_F(KernelFunctionTest, gaussian_kernel) {
    MatrixXd kernel = gaussian_kernel(points, 3.0);
    MatrixXd correct_kernel(3,3);
    correct_kernel <<
        1.0,                0.513417119032592,   0.7165313105737893,
        0.513417119032592,  1.0,                 0.18887560283756183,
        0.7165313105737893, 0.18887560283756183, 1.0;
    EXPECT_PRED2(is_approx_m, kernel, correct_kernel);
}
