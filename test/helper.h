#pragma once

#include <Eigen/Core>

// use with EXPECT_PRED2 to test if two vectors are equal
inline bool is_approx_v(const Eigen::VectorXd& a,
                        const Eigen::VectorXd& b) {
    return a.isApprox(b);
}

// use with EXPECT_PRED2 to test if two matrices are equal
inline bool is_approx_m(const Eigen::MatrixXd& a,
                        const Eigen::MatrixXd& b) {
    return a.isApprox(b);
}
