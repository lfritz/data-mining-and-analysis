#include <catch.hpp>

#include <clustering.h>

using std::vector;

TEST_CASE("valid_clustering") {
    vector<vector<unsigned>> a = { {0,2}, {3}, {1,4,5} };
    vector<vector<unsigned>> b = { {0,2}, {3}, {2,4,5} };
    vector<vector<unsigned>> c = { {0,2}, {3}, {1,2,4,5} };
    CHECK(valid_clustering(a, 6, 3));
    CHECK_FALSE(valid_clustering(a, 6, 2));
    CHECK_FALSE(valid_clustering(a, 7, 3));
    CHECK_FALSE(valid_clustering(b, 6, 3));
    CHECK_FALSE(valid_clustering(c, 6, 3));
}
