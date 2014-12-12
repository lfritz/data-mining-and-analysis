#include <catch.hpp>

#include <kmeans.h>

using Eigen::Vector2d;
using Eigen::Vector3d;
using Eigen::VectorXd;
using std::vector;

TEST_CASE("squared_distance") {
    Vector2d a(1,2);
    Vector2d b(3,2);
    Vector2d c(5,3);
    CHECK(squared_distance(a, b) == Approx(4));
    CHECK(squared_distance(b, a) == Approx(4));
    CHECK(squared_distance(a, c) == Approx(17));
}

TEST_CASE("vector_range") {
    vector<VectorXd> points = {
        Vector2d( 1.3, 4.1),
        Vector2d( 3.2, 1.2),
        Vector2d(-0.3, 4.4),
        Vector2d( 0.4, 6.2)
    };
    VectorXd min, max;
    vector_range(points, min, max);
    CHECK(min == Vector2d(-0.3, 1.2));
    CHECK(max == Vector2d( 3.2, 6.2));
}

TEST_CASE("uniform_random_vector") {
    Vector3d min(1.2, -7.6, -0.5);
    Vector3d max(2.3, -6.5,  0.5);
    vector<VectorXd> points(3);
    for (VectorXd& p : points)
        p = uniform_random_vector(min, max);

    // make sure the values aren't the same
    CHECK_FALSE(points[0] == points[1]);
    CHECK_FALSE(points[1] == points[2]);

    // make sure the values are in the right range
    for (const VectorXd& p : points)
        for (unsigned i = 0; i < 3; ++i) {
            CHECK(min[i] <= p[i]);
            CHECK(p[i] <= max[i]);
        }
}

TEST_CASE("K-means") {
    vector<VectorXd> points {
        Vector2d(0.5, 2.0),
        Vector2d(0.5, 2.5),
        Vector2d(1.0, 2.5),
        Vector2d(2.0, 0.5),
        Vector2d(2.5, 0.5),
        Vector2d(2.5, 1.0)
    };
    Clustering clustering { {0,1,2}, {3,4,5} };

    SECTION("clustering_sse") {
        CHECK(clustering_sse(6, 2, points, clustering) == Approx(2.0 / 3.0));
    }

    SECTION("compute_centroids") {
        vector<VectorXd> correct_centroids {
            Vector2d(2.0/3.0, 7.0/3.0),
            Vector2d(7.0/3.0, 2.0/3.0)
        };
        vector<VectorXd> centroids = compute_centroids(points, clustering);
        CHECK(centroids[0].isApprox(correct_centroids[0]));
        CHECK(centroids[1].isApprox(correct_centroids[1]));
    }

    SECTION("clustering_for_centroids") {
        vector<VectorXd> centroids {
            Vector2d(2.0/3.0, 7.0/3.0),
            Vector2d(7.0/3.0, 2.0/3.0)
        };
        CHECK(clustering_for_centroids(6, 2, points, centroids) == clustering);
    }

    SECTION("kmeans produces a valid clustering") {
        CHECK(valid_clustering(kmeans(points, 2, 0.01), 6, 2));
    }
}
