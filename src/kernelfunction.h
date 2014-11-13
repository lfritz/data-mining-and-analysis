#pragma once

#include <cmath>
#include <Eigen/Core>
#include <functional>

Eigen::MatrixXd
calculate_kernel(std::function<double(const Eigen::VectorXd&,
                                      const Eigen::VectorXd&)> f,
                 std::vector<Eigen::VectorXd> points) {
    unsigned n = points.size();
    Eigen::MatrixXd kernel(n,n);
    for (unsigned i = 0; i < n; ++i) {
        kernel(i,i) = f(points[i], points[i]);
        for (unsigned j = 0; j < i; ++j) {
            double x = f(points[i], points[j]);
            kernel(i,j) = x;
            kernel(j,i) = x;
        }
    }
    return kernel;
}

std::function<double(const Eigen::VectorXd&,
                     const Eigen::VectorXd&)>
homogeneous_polynomial_kernel(double q) {
    return [q](const Eigen::VectorXd& a,
               const Eigen::VectorXd& b) {
        return pow(a.dot(b), q);
    };
}

std::function<double(const Eigen::VectorXd&,
                     const Eigen::VectorXd&)>
inhomogeneous_polynomial_kernel(double q, double c) {
    return [q,c](const Eigen::VectorXd& a,
                 const Eigen::VectorXd& b) {
        return pow(c + a.dot(b), q);
    };
}

std::function<double(const Eigen::VectorXd&,
                     const Eigen::VectorXd&)>
gaussian_kernel(double var) {
    return [var](const Eigen::VectorXd& a,
                 const Eigen::VectorXd& b) {
        Eigen::VectorXd d = a - b;
        return exp(- d.dot(d) / (2.0 * var));
    };
}
