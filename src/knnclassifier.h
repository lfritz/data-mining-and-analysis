#pragma once

// K nearest neighbors (KNN) classifier, from chapter 18.2 of Data Mining and
// Analysis: Fundamental Concepts and Algorithms by Mohammed J. Zaki and Wagner
// Meira Jr.

#include <vector>

#include "classifier.h"

// K nearest neighbors classifier: for a test instance x, uses the k points
// closest to x in the training dataset to predict x's class. It uses a
// straightforward linear search to find the nearest neighbors, so it doesn't
// scale well with the number of training points.
class KnnClassifier : public Classifier {
    std::vector<Eigen::VectorXd> x;
    std::vector<int> y;
    int n;
    int k;

public:
    // Create K nearest neighbors classifier using a set of training points x
    // and corresponding class labels y. Pass x and y with std::move if you
    // want to avoid duplicating the data.
    KnnClassifier(std::vector<Eigen::VectorXd> x,
                  std::vector<int> y,
                  int k);
    int predict(const Eigen::VectorXd& p) const override;
    std::vector<int> find_k_nearest(const Eigen::VectorXd& p) const;
};
