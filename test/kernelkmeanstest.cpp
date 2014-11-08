#include "kernelkmeanstest.h"

using std::vector;

KernelKmeansTest::KernelKmeansTest() {
    // Example data with n=4 points in a 2-dimensional feature space:
    // (1,1) and (1,3) make up cluster 0
    // (2,2) is cluster 1
    // (3,1) is not (yet) in a cluster
    kernel = Kernel {
        {  2,  4,  4,  4 },
        {  4, 10,  8,  6 },
        {  4,  8,  8,  8 },
        {  4,  6,  8, 10 }
    };
    clusters = {
        { 0, 1 },
        { 2 }
    };
}

TEST_F(KernelKmeansTest, random_clustering) {
    EXPECT_TRUE(valid_clustering(random_clustering(10, 3), 10, 3));
}

TEST_F(KernelKmeansTest, cluster_sqnorm) {
    EXPECT_DOUBLE_EQ(5.0, cluster_sqnorm(kernel, clusters[0]));
    EXPECT_DOUBLE_EQ(8.0, cluster_sqnorm(kernel, clusters[1]));
}

TEST_F(KernelKmeansTest, avg_kernel_value) {
    EXPECT_DOUBLE_EQ(5.0, avg_kernel_value(kernel, 3, clusters[0]));
    EXPECT_DOUBLE_EQ(8.0, avg_kernel_value(kernel, 3, clusters[1]));
}

TEST_F(KernelKmeansTest, find_closest_cluster) {
    vector<double> sqnorm { 5.0, 8.0 };
    vector<vector<double>> avg {
        { 0.0, 0.0 },
        { 0.0, 0.0 },
        { 0.0, 0.0 },
        { 5.0, 8.0 }
    };
    EXPECT_EQ(1, find_closest_cluster(2, 3, sqnorm, avg));
}

TEST_F(KernelKmeansTest, count_same) {
    vector<unsigned> a { 0, 1, 2 };
    vector<unsigned> b { 3, 4, 5 };
    vector<unsigned> c { 0, 3, 4, 7 };
    EXPECT_EQ(0, count_same(a, b));
    EXPECT_EQ(1, count_same(a, c));
    EXPECT_EQ(2, count_same(b, c));
}

TEST_F(KernelKmeansTest, clustering_change) {
    vector<vector<unsigned>> a = { {0,2},   {3}, {1,4,5} };
    vector<vector<unsigned>> b = {   {2}, {0,3}, {1,4,5} };
    vector<vector<unsigned>> c = { {1,2},   {3}, {0,4,5} };
    vector<vector<unsigned>> d = {   {5}, {1,4}, {0,2,3} };
    EXPECT_DOUBLE_EQ(    0.0, clustering_change(6, 3, a, a));
    EXPECT_DOUBLE_EQ(1.0/6.0, clustering_change(6, 3, a, b));
    EXPECT_DOUBLE_EQ(2.0/6.0, clustering_change(6, 3, a, c));
    EXPECT_DOUBLE_EQ(    1.0, clustering_change(6, 3, a, d));
}

TEST_F(KernelKmeansTest, kernel_kmeans) {
    EXPECT_TRUE(valid_clustering(kernel_kmeans(kernel, 2), 4, 2));
}

TEST_F(KernelKmeansTest, clustering_kernel_sse) {
    // clustering with cluster means at (1,2) and (2.5,2.5)
    std::vector<std::vector<unsigned>> c { {0,1}, {2,3} };
    // the correct SSE is easy to calculate from the points and cluster means
    double corrects_sse = 1.0 + 1.0 + 0.5 + 0.5;
    EXPECT_DOUBLE_EQ(corrects_sse, clustering_kernel_sse(kernel, c));
}
