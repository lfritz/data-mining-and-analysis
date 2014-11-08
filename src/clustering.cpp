#include "clustering.h"

#include <algorithm>

using std::vector;

bool valid_clustering(Clustering c, unsigned n, unsigned k) {
    // check if the number of clusters is correct
    if (c.size() != k)
        return false;

    // check if each point is included exactly once
    vector<unsigned> points;
    for (const vector<unsigned>& cluster : c)
        for (unsigned p : cluster)
            points.push_back(p);
    std::sort(points.begin(), points.end());
    vector<unsigned> all_points(n);
    for (unsigned i = 0; i < n; ++i)
        all_points[i] = i;
    return points == all_points;
}
