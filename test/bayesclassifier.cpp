#include <catch.hpp>

#include <bayesclassifier.h>

using Eigen::MatrixXd;
using Eigen::Vector2d;
using Eigen::VectorXd;
using std::vector;

TEST_CASE("multivariate_normal_pd") {
    VectorXd mu(2);
    mu << 1.5, 2.5;
    MatrixXd sigma(2,2);
    sigma <<  2.0, -0.5,
             -4.0,  3.0;
    VectorXd x(2);
    x << 2.0, 1.5;
    CHECK(multivariate_normal_pd(x, mu, sigma) == 0.07475611627593093);
}

TEST_CASE("Bayes classifier") {
    vector<VectorXd>x {
        Vector2d(2, 3),
        Vector2d(3, 6),
        Vector2d(4, 2),
        Vector2d(4, 3),
        Vector2d(4, 6),
        Vector2d(5, 5),
        Vector2d(7, 2)
    };
    vector<int> y { 0, 0, 1, 1, 0, 1, 1 };

    BayesClassifier c(x, y);

    SECTION("Estimation of classifier parameters") {
        CHECK(c.nClasses() == 2);
        CHECK(c.priorProbability(0) == Approx(3.0/7.0));
        CHECK(c.priorProbability(1) == Approx(4.0/7.0));
        CHECK(c.mean(0).isApprox(Vector2d(3.0, 5.0)));
        CHECK(c.mean(1).isApprox(Vector2d(5.0, 3.0)));
        MatrixXd sigma0(2,2);
        sigma0 << 2, 3,
                  3, 6;
        sigma0 /= 3.0;
        MatrixXd sigma1(2,2);
        sigma1 <<  6, -1,
                  -1,  6;
        sigma1 /= 4.0;
        CHECK(c.covarianceMatrix(0).isApprox(sigma0));
        CHECK(c.covarianceMatrix(1).isApprox(sigma1));
    }

    SECTION("Predicting class for points") {
        CHECK(c.predict(Vector2d(2.0, 3.0)) == 0);
        CHECK(c.predict(Vector2d(3.0, 5.0)) == 0);
        CHECK(c.predict(Vector2d(2.0, 5.0)) == 0);
        CHECK(c.predict(Vector2d(3.5, 4.5)) == 0);

        CHECK(c.predict(Vector2d(4.0, 3.0)) == 1);
        CHECK(c.predict(Vector2d(5.0, 3.0)) == 1);
        CHECK(c.predict(Vector2d(6.0, 1.0)) == 1);
        CHECK(c.predict(Vector2d(4.0, 4.0)) == 1);
    }
}
