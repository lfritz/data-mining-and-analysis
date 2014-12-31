#include "knnclassifier.h"

#include <cassert>
#include <map>
#include <utility> // for std::pair

#include "algorithm.h"
#include "vectors.h"

using Eigen::VectorXd;
using std::make_pair;
using std::map;
using std::pair;
using std::vector;

KnnClassifier::KnnClassifier(vector<VectorXd> xx,
                             vector<int> yy,
                             int kk) :
x(std::move(xx)),
y(std::move(yy)),
n(x.size()),
k(kk) {
    assert(x.size() == y.size());
    assert(k > 0);
    assert(n >= k);
}

int KnnClassifier::predict(const VectorXd& p) const {
    // ki[c] is the number of points in class c among the k nearest neighbors
    map<int,int> ki;
    for (int i : find_k_nearest(p)) {
        int c = y[i];
        auto it = ki.find(c);
        if (it == ki.end())
            ki[c] = 1;
        else
            ++ki[c];
    }

    auto best = arg_max(ki.cbegin(),
                        ki.cend(),
                        [](auto it) { return it->second; });
    return best->first;
}

vector<int> KnnClassifier::find_k_nearest(const VectorXd& p) const {
    // initialize vector of k nearest neighbors
    auto initial_value = make_pair(-1, std::numeric_limits<double>::max());
    vector<pair<int,double>> nearest(k, initial_value);

    // go through training points and look for nearer ones
    for (int i = 0; i < n; ++i) {
        double d = squared_distance(p, x[i]);
        for (auto it = nearest.cbegin();
             it != nearest.cend();
             ++it)
            if (it->second > d) {
                nearest.pop_back();
                nearest.insert(it, make_pair(i, d));
                break;
            }
    }

    // return just the indices
    vector<int> result;
    for (auto p : nearest)
        result.push_back(p.first);
    return result;
}
