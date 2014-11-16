#pragma once

// Kernel functions: transform a set of points to a matrix representing
// pairwise distance in a high-dimensional feature space. Based on chapter 5 of
// Data Mining and Analysis: Fundamental Concepts and Algorithms by Mohammed J.
// Zaki and Wagner Meira Jr

#include <Eigen/Core>

// Homogeneous polynomial kernel.
Eigen::MatrixXd
homogeneous_polynomial_kernel(std::vector<Eigen::VectorXd> points,
                              double q);

// Inhomogeneous polynomial kernel.
Eigen::MatrixXd
inhomogeneous_polynomial_kernel(std::vector<Eigen::VectorXd> points,
                                double q,
                                double c);

// Gaussian kernel, aka Gaussian radial basis function kernel.
Eigen::MatrixXd
gaussian_kernel(std::vector<Eigen::VectorXd> points,
                double var);
