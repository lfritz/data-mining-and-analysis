#include "clusteringtest.h"

#include <clustering.h>

using std::vector;

TEST_F(ClusteringTest, valid_clustering) {
    vector<vector<unsigned>> a = { {0,2}, {3}, {1,4,5} };
    vector<vector<unsigned>> b = { {0,2}, {3}, {2,4,5} };
    vector<vector<unsigned>> c = { {0,2}, {3}, {1,2,4,5} };
    EXPECT_TRUE(valid_clustering(a, 6, 3));
    EXPECT_FALSE(valid_clustering(a, 6, 2));
    EXPECT_FALSE(valid_clustering(a, 7, 3));
    EXPECT_FALSE(valid_clustering(b, 6, 3));
    EXPECT_FALSE(valid_clustering(c, 6, 3));
}
