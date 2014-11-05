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
    Clustering clustering {
        { { 1.0, 2.0 }, { 2.0, 1.0 } },
        { 0, 0, 0, 1, 1, 1 }
    };
    double correct_sse = (4.0 + 2.0*sqrt(2.0)) * 0.5;
    EXPECT_EQ(correct_sse, clustering_sse(points, clustering));
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

// Testing kmeans is a bit tricky -- because the algorithm relies on randomly
// initialized values, there's no guarantee it'll find the same result every
// time. This test only checks that the result is a valid clustering, not that
// it's a good one.
TEST_F(KmeansTest, kmeans) {
    Clustering clustering = kmeans(points, 2, 0.01);

    // check that 'clustering' is actually a clustering of the input
    EXPECT_EQ(2, clustering.centroids.size());
    for (auto p : clustering.centroids)
        EXPECT_EQ(2, p.size());
    EXPECT_EQ(6, clustering.cluster.size());
    for (auto i : clustering.cluster)
        EXPECT_TRUE(0 <= i && i < 2);

    // check that each centroid is the mean of its cluster
    for (unsigned int j = 0; j < 2; ++j) {
        Point correct_centroid {0.0, 0.0};
        int n = 0;
        for (unsigned int i = 0; i < 6; ++i)
            if (clustering.cluster[i] == j) {
                ++n;
                correct_centroid = add(correct_centroid, points[i]);
            }
        divide(correct_centroid, (double)n);
        EXPECT_EQ(correct_centroid, clustering.centroids[j]);
    }
}

// Run kmeans 10 times in a row. For this very simple clustering problem, it
// seems virtually certain that one of 10 runs will produce the ideal result.
TEST_F(KmeansTest, kmeans_repeat) {
    Clustering clustering = kmeans_repeat(10, points, 2, 0.01);
    std::set<vector<unsigned int>> ideal {
        { 0, 0, 0, 1, 1, 1 },
        { 1, 1, 1, 0, 0, 0 }
    };
    EXPECT_TRUE(ideal.count(clustering.cluster));
}
