#include "kmeanstest.h"

#include <cmath>
#include <kmeans.h>
#include <set>
#include <vectormath.h>

using std::pair;
using std::vector;

KmeansTest::KmeansTest() {
    points = vector<Point> {
        { 0.5, 2.0 },
        { 0.5, 2.5 },
        { 1.0, 2.5 },
        { 2.0, 0.5 },
        { 2.5, 0.5 },
        { 2.5, 1.0 }
    };
}

TEST_F(KmeansTest, clustering_sse) {
    Clustering clustering { {0,1,2}, {3,4,5} };
    double correct_sse = 2.0 / 3.0;
    EXPECT_EQ(correct_sse, clustering_sse(6, 2, points, clustering));
}

TEST_F(KmeansTest, vector_range) {
    vector<Point> points {
        { 1.2,  1.3 },
        { 0.4, -3.1 },
        { 5.1,  0.0 }
    };
    vector<pair<double,double>> correct_result {
        {  0.4, 5.1 },
        { -3.1, 1.3 }
    };
    EXPECT_EQ(correct_result, vector_range(points));
}

TEST_F(KmeansTest, uniform_random_double) {
    double min = 1.2;
    double max = 2.3;
    vector<double> values(3);
    for (double& d : values)
        d = uniform_random_double(min, max);

    // make sure the values aren't all the same
    EXPECT_FALSE((values[0] == values[1]) && (values[1] == values[2]));

    // make sure the values are in the right range
    for (double d : values)
        EXPECT_TRUE(min <= d && d <= max);
}

TEST_F(KmeansTest, uniform_random_vector) {
    vector<pair<double,double>> range {
        {  1.2,  2.3 },
        { -7.6, -6.5 },
        { -0.5,  0.5 }
    };
    vector<Point> points(3);
    for (Point& p : points)
        p = uniform_random_vector(range);

    // make sure the values aren't the same
    EXPECT_FALSE(points[0] == points[1]);
    EXPECT_FALSE(points[1] == points[2]);

    // make sure the values are in the right range
    for (const Point& p : points)
        for (int i = 0; i < 3; ++i)
            EXPECT_TRUE(range[i].first <= p[i] && p[i] <= range[i].second);
}

TEST_F(KmeansTest, compute_centroids) {
    Clustering clustering { {0,1,2}, {3,4,5} };
    vector<Point> correct_centroids {
        { 2.0/3.0, 7.0/3.0 },
        { 7.0/3.0, 2.0/3.0 }
    };
    // XXX this compares double values with ==
    EXPECT_EQ(correct_centroids, compute_centroids(points, clustering));
}

TEST_F(KmeansTest, clustering_for_centroids) {
    Clustering correct_clustering { {0,1,2}, {3,4,5} };
    vector<Point> centroids {
        { 2.0/3.0, 7.0/3.0 },
        { 7.0/3.0, 2.0/3.0 }
    };
    EXPECT_EQ(correct_clustering,
              clustering_for_centroids(6, 2, points, centroids));
}

TEST_F(KmeansTest, kmeans) {
    EXPECT_TRUE(valid_clustering(kmeans(points, 2, 0.01), 6, 2));
}
