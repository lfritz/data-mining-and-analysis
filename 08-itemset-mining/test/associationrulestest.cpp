#include "associationrulestest.h"

#include <algorithm>

#include <associationrules.h>

using std::vector;

// test proper_subsets
TEST_F(AssociationRulesTest, proper_subsets) {
    // test itemsets of size 0, 1, 2, 3, 4
    vector<vector<int>> input = { {}, {0}, {0,1}, {0,1,2}, {0,1,2,3} };
    vector<vector<vector<int>>> correct_results = {
        { },
        { },
        { {0}, {1} },
        { {0}, {1}, {2}, {0,1}, {0,2}, {1,2} },
        { {0}, {1}, {2}, {3},
          {0,1}, {0,2}, {0,3}, {1,2}, {1,3}, {2,3},
          {0,1,2}, {0,1,3}, {0,2,3}, {1,2,3} }
    };
    for (unsigned int i = 0; i < input.size(); ++i) {
        auto result = proper_subsets(input[i]);
        auto correct_result = correct_results[i];
        std::sort(result.begin(), result.end());
        std::sort(correct_result.begin(), correct_result.end());
        EXPECT_EQ(correct_result, result);
    }
}

// test association_rules
TEST_F(AssociationRulesTest, association_rules) {
    // input
    FrequentItemsets f = {
        { {0}, 6 },
        { {1}, 6 },
        { {2}, 6 },
        { {3}, 7 },
        { {4}, 4 },
        { {0,1}, 4 },
        { {0,2}, 4 },
        { {0,3}, 4 },
        { {1,3}, 5 },
        { {2,3}, 5 },
        { {0,1,3}, 4 }
    };
    double minconf = 0.8;

    // correct output
    vector<AssociationRule> correct_result = {
        AssociationRule({1},   {3}, 5, 5.0/6.0),
        AssociationRule({2},   {3}, 5, 5.0/6.0),
        AssociationRule({0,1}, {3}, 4, 4.0/4.0),
        AssociationRule({0,3}, {1}, 4, 4.0/4.0),
        AssociationRule({1,3}, {0}, 4, 4.0/5.0)
    };

    auto result = association_rules(f, minconf);

    // since the order doesn't matter, normalize the result by sorting
    std::sort(result.begin(), result.end());
    std::sort(correct_result.begin(), correct_result.end());

    EXPECT_EQ(correct_result, result);
}
