#include "kernelfunction.h"

#include <cmath>
#include <functional>

using Eigen::MatrixXd;
using Eigen::VectorXd;
using std::function;
using std::vector;

MatrixXd calculate_kernel(function<double(const VectorXd&,
                                          const VectorXd&)> f,
                          vector<VectorXd> points) {
    unsigned n = points.size();
    MatrixXd kernel(n,n);
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

MatrixXd homogeneous_polynomial_kernel(vector<VectorXd> points,
                                       double q) {
    auto f = [q](const VectorXd& a, const VectorXd& b) {
        return pow(a.dot(b), q);
    };
    return calculate_kernel(f, points);
}

MatrixXd inhomogeneous_polynomial_kernel(vector<VectorXd> points,
                                         double q,
                                         double c) {
    auto f = [q,c](const VectorXd& a, const VectorXd& b) {
        return pow(c + a.dot(b), q);
    };
    return calculate_kernel(f, points);
}

MatrixXd gaussian_kernel(vector<VectorXd> points,
                         double var) {
    auto f = [var](const VectorXd& a, const VectorXd& b) {
        VectorXd d = a - b;
        return exp(- d.dot(d) / (2.0 * var));
    };
    return calculate_kernel(f, points);
}
