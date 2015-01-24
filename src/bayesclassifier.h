#pragma once

// Full Bayes classifier, from chapter 18.1 of Data Mining and Analysis:
// Fundamental Concepts and Algorithms by Mohammed J. Zaki and Wagner Meira Jr.

#include <vector>

#include "classifier.h"

// Evaluate the probability density function for the multivariate normal
// distribution with mean mu and covariance matrix sigma at point x.
double multivariate_normal_pd(const Eigen::VectorXd& x,
                              const Eigen::VectorXd& mu,
                              const Eigen::MatrixXd& sigma);

// Full Bayesian classifier: uses the Bayes theorem to predict the class for a
// point as the one that maximizes the posterior probability.
class BayesClassifier : public Classifier {
    int k;
    std::vector<double> p;
    std::vector<Eigen::VectorXd> mu;
    std::vector<Eigen::MatrixXd> sigma;

public:
    // Create Bayesian classifier using a set of training points x and
    // corresponding class labels y. The labels must go from 0 to some maximum,
    // and there must be at least one point for each class.
    BayesClassifier(const std::vector<Eigen::VectorXd>& x,
                    const std::vector<int>& y);

    // Predict the class for point x.
    int predict(const Eigen::VectorXd& x) const override;

    // Number of classes.
    int nClasses() const;

    // Prior probability for class i.
    double priorProbability(int i) const;

    // Mean value for class i.
    Eigen::VectorXd mean(int i) const;

    // Covariance matrix for class i.
    Eigen::MatrixXd covarianceMatrix(int i) const;
};
