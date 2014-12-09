#pragma once

#include <Eigen/Core>

class Classifier {
public:
    virtual ~Classifier() = 0;

    // Predict the class for point x.
    virtual int predict(const Eigen::VectorXd& x) const = 0;
};
