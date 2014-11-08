#include "kmeans.h"

#include <cassert>
#include <limits>
#include <random>

#include "vectormath.h"

using std::pair;
using std::vector;

double clustering_sse(const vector<Point>& points,
                      const Clustering& clustering) {
    double sse = 0.0;
    unsigned n = points.size();
    for (unsigned i = 0; i < n; ++i)
        sse += distance_squared(points[i],
                                clustering.centroids[clustering.cluster[i]]);
    return sse;
}

vector<pair<double,double>>
vector_range(const vector<Point>& points) {
    assert( ! points.empty());
    unsigned n = points[0].size();
    pair<double,double> x(std::numeric_limits<double>::max(),
                          std::numeric_limits<double>::lowest());
    vector<pair<double,double>> result(n, x);
    for (const Point& p : points)
        for (unsigned i = 0; i < n; ++i) {
            double v = p[i];
            pair<double,double>& r = result[i];
            r.first = std::min(r.first, v);
            r.second = std::max(r.second, v);
        }
    return result;
}

double uniform_random_double(double min, double max) {
    static std::random_device rd;
    static std::default_random_engine re(rd());
    static std::uniform_int_distribution<int> ud(0, 10000);
    return min + ud(re) * ((max - min) / 10000.0);
}

Point uniform_random_vector(const vector<pair<double,double>>& r) {
    Point p;
    for (auto& pair : r)
        p.push_back(uniform_random_double(pair.first, pair.second));
    return p;
}

Clustering kmeans(const vector<Point>& points,
                  unsigned k,
                  double epsilon,
                  unsigned max_iterations) {
    unsigned n = points.size();
    unsigned m = points[0].size();
    vector<Point> centroids(k);
    vector<Point> previous_centroids;
    vector<unsigned> cluster(n);

    // initialize centroids
    vector<pair<double,double>> r = vector_range(points);
    for (Point& c : centroids)
        c = uniform_random_vector(r);

    for (unsigned t = 0; t < max_iterations; ++t) {
        // cluster assignment
        for (unsigned i = 0; i < n; ++i) {
            const Point& p = points[i];
            unsigned min_j = 0;
            double min_distance = std::numeric_limits<double>::max();
            for (unsigned j = 0; j < k; ++j) {
                double d = distance_squared(centroids[j], p);
                if (d < min_distance) {
                    min_j = j;
                    min_distance = d;
                }
            }
            cluster[i] = min_j;
        }

        // centroid update
        previous_centroids = std::move(centroids);
        centroids = vector<Point>(k);
        for (unsigned j = 0; j < k; ++j) {
            unsigned count = 0;
            Point c(m);
            for (unsigned i = 0; i < n; ++i)
                if (cluster[i] == j) {
                    ++count;
                    c = add(c, points[i]);
                }
            divide(c, (double)count);
            centroids[j] = c;
        }

        // check stopping criterion
        double d = 0.0;
        for (unsigned j = 0; j < k; ++j)
            d += distance_squared(previous_centroids[j], centroids[j]);
        if (d <= epsilon)
            break;
    }

    Clustering clustering {
        std::move(centroids),
        std::move(cluster)
    };
    return clustering;
}

Clustering kmeans_repeat(unsigned int repetitions,
                         const vector<Point>& points,
                         unsigned int k,
                         double epsilon,
                         unsigned int max_iterations) {
    Clustering best_clustering;
    double best_sse = std::numeric_limits<double>::max();
    for (unsigned int i = 0; i < repetitions; ++i) {
        Clustering clustering = kmeans(points, k, epsilon, max_iterations);
        double sse = clustering_sse(points, clustering);
        if (sse < best_sse) {
            best_clustering = clustering;
            best_sse = sse;
        }
    }
    return best_clustering;
}
