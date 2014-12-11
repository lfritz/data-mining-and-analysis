#include "knnclassifiertest.h"

#include <set>

#include "helper.h"

using Eigen::Vector2d;
using std::set;
using std::vector;

KnnClassifierTest::KnnClassifierTest() :
x {
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
},
y { 0,0,0,2,2,0,0,0,2,0,0,2,0,2,2,2,2,1,1,1,1,2,1,1,1,1 },
c(KnnClassifier(x, y, 5)),
test_x {
    Vector2d(1.5, 1.5),
    Vector2d(7.0, 3.0),
    Vector2d(2.0, 7.5),
    Vector2d(4.5, 3.0),
    Vector2d(5.0, 3.0),
    Vector2d(6.5, 6.5),
    Vector2d(0.5, 4.0),
    Vector2d(6.5, 2.0),
    Vector2d(3.0, 5.5)
} { }

TEST_F(KnnClassifierTest, find_k_nearest) {
    vector<set<int>> nearest {
        { 0, 1, 5, 7, 6 },
        { 18, 22, 19, 25, 23 },
        { 4, 8, 3, 11, 16 }
    };
    for (int i = 0; i < 3; ++i) {
        auto v = c.find_k_nearest(test_x[i]);
        EXPECT_EQ(nearest[i], set<int>(v.begin(), v.end()));
    }
}

// Test predicting class for points.
TEST_F(KnnClassifierTest, predict) {
    vector<int> classes { 0,1,2,0,1,2,0,1,2 };
    for (int i = 0; i < 9; ++i)
        EXPECT_EQ(classes[i], c.predict(test_x[i]));
}
