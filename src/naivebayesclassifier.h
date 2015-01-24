#pragma once

// Naive Bayes classifier, from chapter 18.2 of Data Mining and Analysis:
// Fundamental Concepts and Algorithms by Mohammed J. Zaki and Wagner Meira Jr.

#include <vector>

#include "classifier.h"

// Evaluate the probability density function for the normal distribution with
// mean mu and covariance matrix sigma at x.
double normal_pd(double x, double mu, double sigma_squared);

// Naive Bayesian classifier: uses the Bayes theorem to predict the class for a
// point as the one that maximizes the posterior probability, but assuming the
// attributes are independent.
class NaiveBayesClassifier : public Classifier {
    int k;
    int d;
    std::vector<double> p;
    std::vector<Eigen::VectorXd> mu;
    std::vector<Eigen::VectorXd> var;

public:
    // Create Naive Bayesian classifier using a set of training points x and
    // corresponding class labels y. The labels must go from 0 to some maximum,
    // and there must be at least one point for each class.
    NaiveBayesClassifier(const std::vector<Eigen::VectorXd>& x,
                         const std::vector<int>& y);

    // Predict the class for point x.
    int predict(const Eigen::VectorXd& x) const override;

    // Number of classes.
    int nClasses() const;

    // Prior probability for class i.
    double priorProbability(int i) const;

    // Mean value for class i.
    Eigen::VectorXd mean(int i) const;

    // Variances for class i.
    Eigen::VectorXd variances(int i) const;
};
