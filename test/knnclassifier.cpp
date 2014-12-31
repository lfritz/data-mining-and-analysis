#include <catch.hpp>

#include <set>

#include <knnclassifier.h>

using Eigen::Vector2d;
using Eigen::VectorXd;
using std::set;
using std::vector;

TEST_CASE("K Nearest Neighbors classifier") {
    vector<VectorXd> x {
        Vector2d(1.0, 1.0),
        Vector2d(1.0, 2.0),
        Vector2d(1.5, 3.5),
        Vector2d(1.5, 5.5),
        Vector2d(1.5, 8.0),
        Vector2d(2.0, 1.0),
        Vector2d(2.0, 2.5),
        Vector2d(2.5, 1.5),
        Vector2d(2.5, 8.0),
        Vector2d(3.0, 2.5),
        Vector2d(3.0, 3.0),
        Vector2d(3.5, 6.5),
        Vector2d(4.0, 1.5),
        Vector2d(4.0, 4.5),
        Vector2d(4.5, 4.0),
        Vector2d(5.0, 5.5),
        Vector2d(5.0, 8.0),
        Vector2d(6.0, 4.0),
        Vector2d(6.5, 3.0),
        Vector2d(6.5, 3.5),
        Vector2d(6.5, 4.0),
        Vector2d(6.5, 7.0),
        Vector2d(7.0, 3.5),
        Vector2d(7.0, 4.0),
        Vector2d(7.0, 4.5),
        Vector2d(7.5, 3.5)
    };
    vector<int> y { 0,0,0,2,2,0,0,0,2,0,0,2,0,2,2,2,2,1,1,1,1,2,1,1,1,1 };
    KnnClassifier c(x, y, 5);
    vector<VectorXd> test_x {
        Vector2d(1.5, 1.5),
        Vector2d(7.0, 3.0),
        Vector2d(2.0, 7.5),
        Vector2d(4.5, 3.0),
        Vector2d(5.0, 3.0),
        Vector2d(6.5, 6.5),
        Vector2d(0.5, 4.0),
        Vector2d(6.5, 2.0),
        Vector2d(3.0, 5.5)
    };

    SECTION("find 5 nearest neighbors") {
        vector<set<int>> nearest {
            { 0, 1, 5, 7, 6 },
            { 18, 22, 19, 25, 23 },
            { 4, 8, 3, 11, 16 }
        };
        for (int i = 0; i < 3; ++i) {
            auto v = c.find_k_nearest(test_x[i]);
            CHECK(set<int>(v.cbegin(), v.cend()) == nearest[i]);
        }
    }

    SECTION("predict class for points") {
        vector<int> classes { 0,1,2,0,1,2,0,1,2 };
        for (int i = 0; i < 9; ++i)
            CHECK(c.predict(test_x[i]) == classes[i]);
    }
}
