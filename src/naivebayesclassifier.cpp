#include "naivebayesclassifier.h"

#include <algorithm> // for std::max_element
#include <cassert>

#include "algorithm.h"

using Eigen::MatrixXd;
using Eigen::VectorXd;
using std::vector;

double normal_pd(double x, double mu, double sigma_squared) {
    double a = sqrt(2.0 * M_PI * sigma_squared);
    double b = (x - mu)*(x - mu) / (2.0 * sigma_squared);
    return (1.0 / a) * exp( - b);
}

NaiveBayesClassifier::NaiveBayesClassifier(const vector<VectorXd>& x,
                                           const vector<int>& y) :
k(0), d(0), p(), mu(), var() {
    // n is the number of points
    int n = x.size();
    assert(n > 0);
    assert(y.size() == n);

    // d is the dimensionality
    d = x[0].size();
    for (const VectorXd& v : x)
        assert(v.size() == d);

    // number of classes
    k = *(std::max_element(y.cbegin(), y.cend())) + 1;

    for (int i = 0; i < k; ++i) {
        // find all points in class i
        vector<VectorXd> xi;
        for (int j = 0; j < n; ++j)
            if (y[j] == i)
                xi.push_back(x[j]);

        // ni is the number of points in class i
        int ni = xi.size();
        assert(ni > 0);

        // prior probability
        p.push_back((double)ni / (double)n);

        // class mean
        VectorXd m = VectorXd::Zero(d);
        for (const VectorXd& v : xi)
            m += v;
        m /= ni;
        mu.push_back(m);

        // centered data matrix
        MatrixXd z(d, ni);
        for (int j = 0; j < ni; ++j)
            z.col(j) = xi[j] - m;

        // class-specific attribute variances
        VectorXd variance(d);
        for (int j = 0; j < d; ++j) {
            VectorXd zj = z.row(j);
            variance(j) = (1.0/ni) * zj.dot(zj);
        }
        var.push_back(variance);
    }
}

int NaiveBayesClassifier::predict(const VectorXd& x) const {
    return arg_max(0, k, [&x,this](int i) {
        double product = 1.0;
        for (int j = 0; j < d; ++j)
            product *= normal_pd(x(j), mu[i](j), var[i](j));
        return p[i] * product;
    });
}

int NaiveBayesClassifier::nClasses() const {
    return k;
}
double NaiveBayesClassifier::priorProbability(int i) const {
    return p[i];
}
VectorXd NaiveBayesClassifier::mean(int i) const {
    return mu[i];
}
VectorXd NaiveBayesClassifier::variances(int i) const {
    return var[i];
}
