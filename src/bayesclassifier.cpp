#include "bayesclassifier.h"

#include <algorithm> // for std::max_element
#include <cassert>

#include <Eigen/LU>

#include "algorithm.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;
using std::vector;

double multivariate_normal_pd(const VectorXd& x,
                              const VectorXd& mu,
                              const MatrixXd& sigma) {
    // XXX would be more efficient to pre-compute sigma.inverse() and
    // sigma.determinant()
    double d = x.size();
    VectorXd v = x - mu;
    double a = pow(2.0 * M_PI, d/2.0);
    double b = sqrt(sigma.determinant());
    double c = v.transpose() * sigma.inverse() * v;
    return (1.0 / (a*b)) * exp( - c / 2.0);
}

BayesClassifier::BayesClassifier(const vector<VectorXd>& x,
                                 const vector<int>& y) :
k(0), p(), mu(), sigma() {
    // n is the number of points
    int n = x.size();
    assert(n > 0);
    assert(y.size() == n);

    // d is the dimensionality
    int d = x[0].size();
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

        // covariance matrix
        sigma.push_back((1.0/(double)ni) * z * z.transpose());
    }
}

int BayesClassifier::predict(const VectorXd& x) const {
    return arg_max(0, k, [&x,this](int i) {
        return multivariate_normal_pd(x, mu[i], sigma[i]) * p[i];
    });
}

int BayesClassifier::nClasses() const {
    return k;
}
double BayesClassifier::priorProbability(int i) const {
    return p[i];
}
VectorXd BayesClassifier::mean(int i) const {
    return mu[i];
}
MatrixXd BayesClassifier::covarianceMatrix(int i) const {
    return sigma[i];
}
