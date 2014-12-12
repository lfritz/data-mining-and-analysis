#include <catch.hpp>

#include <naivebayesclassifier.h>

using Eigen::Vector2d;
using Eigen::VectorXd;
using std::vector;

TEST_CASE("normal_pd") {
    double x = 2.0;
    double mu = 1.5;
    double sigma_sq = 2.0;
    CHECK(normal_pd(x, mu, sigma_sq) == 0.26500353234402857);
}

TEST_CASE("Naive Bayes classifier") {
    vector<VectorXd> x = {
        Vector2d(2, 3),
        Vector2d(3, 6),
        Vector2d(4, 2),
        Vector2d(4, 3),
        Vector2d(4, 6),
        Vector2d(5, 5),
        Vector2d(7, 2)
    };
    vector<int> y = { 0, 0, 1, 1, 0, 1, 1 };

    NaiveBayesClassifier c(x, y);

    SECTION("Estimation of classifier parameters") {
        CHECK(c.nClasses() == 2);
        CHECK(c.priorProbability(0) == Approx(3.0/7.0));
        CHECK(c.priorProbability(1) == Approx(4.0/7.0));
        CHECK(c.mean(0).isApprox(Vector2d(3.0, 5.0)));
        CHECK(c.mean(1).isApprox(Vector2d(5.0, 3.0)));
        CHECK(c.variances(0).isApprox(Vector2d(2.0/3.0, 2.0)));
        CHECK(c.variances(1).isApprox(Vector2d(3.0/2.0, 3.0/2.0)));
    }

    SECTION("Predicting class for points") {
        NaiveBayesClassifier c(x, y);

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
