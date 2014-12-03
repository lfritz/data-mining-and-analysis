#include "bayesclassifiertest.h"

#include "helper.h"

#include <bayesclassifier.h>

using Eigen::MatrixXd;
using Eigen::Vector2d;
using Eigen::VectorXd;
using std::vector;

BayesClassifierTest::BayesClassifierTest() {
    x = {
        Vector2d(2, 3),
        Vector2d(3, 6),
        Vector2d(4, 2),
        Vector2d(4, 3),
        Vector2d(4, 6),
        Vector2d(5, 5),
        Vector2d(7, 2)
    };
    y = { 0, 0, 1, 1, 0, 1, 1 };
}

// Test multivariate_normal_pd function.
TEST_F(BayesClassifierTest, multivariate_normal_pd) {
    VectorXd mu(2);
    mu(0) = 1.5;
    mu(1) = 2.5;

    MatrixXd sigma(2,2);
    sigma(0,0) =  2.0; sigma(0,1) = -0.5;
    sigma(1,0) = -4.0; sigma(1,1) =  3.0;

    VectorXd x(2);
    x(0) = 2.0;
    x(1) = 1.5;

    EXPECT_EQ(0.07475611627593093, multivariate_normal_pd(x, mu, sigma));
}

// Test estimation of classifier parameters.
TEST_F(BayesClassifierTest, estimate) {
    BayesClassifier c(x, y);
    EXPECT_DOUBLE_EQ(2, c.nClasses());
    EXPECT_DOUBLE_EQ(3.0/7.0, c.priorProbability(0));
    EXPECT_DOUBLE_EQ(4.0/7.0, c.priorProbability(1));
    EXPECT_PRED2(is_approx_v, Vector2d(3.0, 5.0), c.mean(0));
    EXPECT_PRED2(is_approx_v, Vector2d(5.0, 3.0), c.mean(1));
    MatrixXd sigma0(2,2);
    sigma0 << 2, 3,
              3, 6;
    sigma0 /= 3.0;
    MatrixXd sigma1(2,2);
    sigma1 <<  6, -1,
              -1,  6;
    sigma1 /= 4.0;
    EXPECT_PRED2(is_approx_m, sigma0, c.covarianceMatrix(0));
    EXPECT_PRED2(is_approx_m, sigma1, c.covarianceMatrix(1));
}

// Test predicting class for points.
TEST_F(BayesClassifierTest, predict) {
    BayesClassifier c(x, y);

    EXPECT_EQ(0, c.predict(Vector2d(2.0, 3.0)));
    EXPECT_EQ(0, c.predict(Vector2d(3.0, 5.0)));
    EXPECT_EQ(0, c.predict(Vector2d(2.0, 5.0)));
    EXPECT_EQ(0, c.predict(Vector2d(3.5, 4.5)));

    EXPECT_EQ(1, c.predict(Vector2d(4.0, 3.0)));
    EXPECT_EQ(1, c.predict(Vector2d(5.0, 3.0)));
    EXPECT_EQ(1, c.predict(Vector2d(6.0, 1.0)));
    EXPECT_EQ(1, c.predict(Vector2d(4.0, 4.0)));
}
