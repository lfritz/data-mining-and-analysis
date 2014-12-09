#include "naivebayesclassifiertest.h"

#include "helper.h"

#include <naivebayesclassifier.h>

using Eigen::MatrixXd;
using Eigen::Vector2d;
using Eigen::VectorXd;
using std::vector;

NaiveBayesClassifierTest::NaiveBayesClassifierTest() {
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

// Test normal_pd function.
TEST_F(NaiveBayesClassifierTest, normal_pd) {
    double x = 2.0;
    double mu = 1.5;
    double sigma_sq = 2.0;
    EXPECT_EQ(0.26500353234402857, normal_pd(x, mu, sigma_sq));
}

// Test estimation of classifier parameters.
TEST_F(NaiveBayesClassifierTest, estimate) {
    NaiveBayesClassifier c(x, y);

    EXPECT_EQ(2, c.nClasses());
    EXPECT_DOUBLE_EQ(3.0/7.0, c.priorProbability(0));
    EXPECT_DOUBLE_EQ(4.0/7.0, c.priorProbability(1));
    EXPECT_PRED2(is_approx_v, Vector2d(3.0, 5.0), c.mean(0));
    EXPECT_PRED2(is_approx_v, Vector2d(5.0, 3.0), c.mean(1));
    EXPECT_PRED2(is_approx_v, Vector2d(2.0/3.0, 2.0), c.variances(0));
    EXPECT_PRED2(is_approx_v, Vector2d(3.0/2.0, 3.0/2.0), c.variances(1));
}

// Test predicting class for points.
TEST_F(NaiveBayesClassifierTest, predict) {
    NaiveBayesClassifier c(x, y);

    EXPECT_EQ(0, c.predict(Vector2d(2.0, 3.0)));
    EXPECT_EQ(0, c.predict(Vector2d(3.0, 5.0)));
    EXPECT_EQ(0, c.predict(Vector2d(2.0, 5.0)));
    EXPECT_EQ(0, c.predict(Vector2d(3.5, 4.5)));

    EXPECT_EQ(1, c.predict(Vector2d(4.0, 3.0)));
    EXPECT_EQ(1, c.predict(Vector2d(5.0, 3.0)));
    EXPECT_EQ(1, c.predict(Vector2d(6.0, 1.0)));
    EXPECT_EQ(1, c.predict(Vector2d(4.0, 4.0)));
}
