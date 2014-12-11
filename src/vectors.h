#pragma once

#include <Eigen/Core>

// Compute the squared distance between the vectors.
inline double squared_distance(const Eigen::VectorXd& a,
                               const Eigen::VectorXd& b) {
    Eigen::VectorXd d = a - b;
    return d.dot(d);
}


