#include <catch.hpp>

#include <kernelkmeans.h>

using Eigen::MatrixXd;
using std::vector;

TEST_CASE("random_clustering") {
    CHECK(valid_clustering(random_clustering(10, 3), 10, 3));
}

TEST_CASE("find_closest_cluster") {
    vector<double> sqnorm { 5.0, 8.0 };
    vector<vector<double>> avg {
        { 0.0, 0.0 },
        { 0.0, 0.0 },
        { 0.0, 0.0 },
        { 5.0, 8.0 }
    };
    CHECK(find_closest_cluster(2, 3, sqnorm, avg) == 1);
}

TEST_CASE("count_same") {
    vector<unsigned> a { 0, 1, 2 };
    vector<unsigned> b { 3, 4, 5 };
    vector<unsigned> c { 0, 3, 4, 7 };
    CHECK(count_same(a, b) == 0);
    CHECK(count_same(a, c) == 1);
    CHECK(count_same(b, c) == 2);
}

TEST_CASE("clustering_change") {
    vector<vector<unsigned>> a = { {0,2},   {3}, {1,4,5} };
    vector<vector<unsigned>> b = {   {2}, {0,3}, {1,4,5} };
    vector<vector<unsigned>> c = { {1,2},   {3}, {0,4,5} };
    vector<vector<unsigned>> d = {   {5}, {1,4}, {0,2,3} };
    CHECK(clustering_change(6, 3, a, a) == Approx(    0.0));
    CHECK(clustering_change(6, 3, a, b) == Approx(1.0/6.0));
    CHECK(clustering_change(6, 3, a, c) == Approx(2.0/6.0));
    CHECK(clustering_change(6, 3, a, d) == Approx(    1.0));
}

TEST_CASE("Kernel K-means") {
    // Example data with n=4 points in a 2-dimensional feature space:
    // (1,1) and (1,3) make up cluster 0
    // (2,2) is cluster 1
    // (3,1) is not (yet) in a cluster
    MatrixXd kernel(4,4);
    kernel << 2,  4,  4,  4,
              4, 10,  8,  6,
              4,  8,  8,  8,
              4,  6,  8, 10;
    vector<vector<unsigned>> clusters {
        { 0, 1 },
        { 2 }
    };

    CHECK(cluster_sqnorm(kernel, clusters[0]) == Approx(5.0));
    CHECK(cluster_sqnorm(kernel, clusters[1]) == Approx(8.0));

    CHECK(avg_kernel_value(kernel, 3, clusters[0]) == Approx(5.0));
    CHECK(avg_kernel_value(kernel, 3, clusters[1]) == Approx(8.0));

    CHECK(valid_clustering(kernel_kmeans(kernel, 2), 4, 2));

    SECTION("clustering_kernel_sse") {
        // clustering with cluster means at (1,2) and (2.5,2.5)
        vector<vector<unsigned>> c { {0,1}, {2,3} };
        // correct SSE is easy to calculate from the points and cluster means
        double correct_sse = 1.0 + 1.0 + 0.5 + 0.5;
        CHECK(clustering_kernel_sse(kernel, c) == Approx(correct_sse));
    }
}
