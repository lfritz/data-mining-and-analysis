#include "kmeanstest.h"

#include <kmeans.h>
#include <set>

using Eigen::Vector2d;
using Eigen::Vector3d;
using Eigen::VectorXd;
using std::vector;

bool is_approx(const VectorXd& a,
               const VectorXd& b) {
    return a.isApprox(b);
}

KmeansTest::KmeansTest() {
    points = {
        Vector2d(0.5, 2.0),
        Vector2d(0.5, 2.5),
        Vector2d(1.0, 2.5),
        Vector2d(2.0, 0.5),
        Vector2d(2.5, 0.5),
        Vector2d(2.5, 1.0)
    };
}

TEST_F(KmeansTest, squared_distance) {
    Vector2d a(1,2);
    Vector2d b(3,2);
    Vector2d c(5,3);
    EXPECT_DOUBLE_EQ(4, squared_distance(a, b));
    EXPECT_DOUBLE_EQ(4, squared_distance(b, a));
    EXPECT_DOUBLE_EQ(17, squared_distance(a, c));
}

TEST_F(KmeansTest, clustering_sse) {
    Clustering clustering { {0,1,2}, {3,4,5} };
    double correct_sse = 2.0 / 3.0;
    EXPECT_DOUBLE_EQ(correct_sse, clustering_sse(6, 2, points, clustering));
}

TEST_F(KmeansTest, vector_range) {
    vector<VectorXd> points = {
        Vector2d( 1.3, 4.1),
        Vector2d( 3.2, 1.2),
        Vector2d(-0.3, 4.4),
        Vector2d( 0.4, 6.2)
    };
    Vector2d correct_min(-0.3, 1.2);
    Vector2d correct_max( 3.2, 6.2);
    VectorXd min, max;
    vector_range(points, min, max);
    EXPECT_EQ(correct_min, min);
    EXPECT_EQ(correct_max, max);
}

TEST_F(KmeansTest, uniform_random_vector) {
    Vector3d min(1.2, -7.6, -0.5);
    Vector3d max(2.3, -6.5,  0.5);
    vector<VectorXd> points(3);
    for (VectorXd& p : points)
        p = uniform_random_vector(min, max);

    // make sure the values aren't the same
    EXPECT_FALSE(points[0] == points[1]);
    EXPECT_FALSE(points[1] == points[2]);

    // make sure the values are in the right range
    for (const VectorXd& p : points)
        for (unsigned i = 0; i < 3; ++i)
            EXPECT_TRUE(min[i] <= p[i] && p[i] <= max[i]);
}

TEST_F(KmeansTest, compute_centroids) {
    Clustering clustering { {0,1,2}, {3,4,5} };
    vector<VectorXd> correct_centroids {
        Vector2d(2.0/3.0, 7.0/3.0),
        Vector2d(7.0/3.0, 2.0/3.0)
    };
    vector<VectorXd> centroids = compute_centroids(points, clustering);
    EXPECT_PRED2(is_approx, correct_centroids[0], centroids[0]);
    EXPECT_PRED2(is_approx, correct_centroids[1], centroids[1]);
}

TEST_F(KmeansTest, clustering_for_centroids) {
    Clustering correct_clustering { {0,1,2}, {3,4,5} };
    vector<VectorXd> centroids {
        Vector2d(2.0/3.0, 7.0/3.0),
        Vector2d(7.0/3.0, 2.0/3.0)
    };
    EXPECT_EQ(correct_clustering,
              clustering_for_centroids(6, 2, points, centroids));
}

TEST_F(KmeansTest, kmeans) {
    EXPECT_TRUE(valid_clustering(kmeans(points, 2, 0.01), 6, 2));
}
