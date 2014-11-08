#include "kmeans.h"

#include <cassert>
#include <limits>
#include <random>

#include "vectormath.h"

using std::pair;
using std::vector;

double clustering_sse(unsigned n,
                      unsigned k,
                      const vector<Point>& points,
                      const Clustering& clustering) {
    vector<Point> centroids = compute_centroids(points, clustering);
    double sse = 0.0;
    for (unsigned j = 0; j < k; ++j) {
        const vector<unsigned>& cluster = clustering[j];
        const Point& centroid = centroids[j];
        for (unsigned i : cluster)
            sse += distance_squared(points[i], centroid);
    }
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

vector<Point> compute_centroids(const vector<Point>& points,
                                const Clustering& clustering) {
    unsigned m = points[0].size();
    vector<Point> centroids;
    for (const vector<unsigned>& cluster : clustering) {
        Point centroid(m);
        for (unsigned i : cluster)
            centroid = add(centroid, points[i]);
        divide(centroid, (double)cluster.size());
        centroids.push_back(centroid);
    }
    return centroids;
}

Clustering clustering_for_centroids(unsigned n,
                                    unsigned k,
                                    const vector<Point>& points,
                                    const vector<Point>& centroids) {
    Clustering clustering(k);
    for (unsigned i = 0; i < n; ++i) {
        const Point& p = points[i];
        unsigned min_j = 0;
        double min_d = std::numeric_limits<double>::max();
        for (unsigned j = 0; j < k; ++j) {
            double d = distance_squared(centroids[j], p);
            if (d < min_d) {
                min_j = j;
                min_d = d;
            }
        }
        clustering[min_j].push_back(i);
    }
    return clustering;
}

Clustering kmeans(const vector<Point>& points,
                  unsigned k,
                  double epsilon,
                  unsigned max_iterations) {
    unsigned n = points.size();
    vector<Point> centroids(k);
    vector<Point> previous_centroids;

    // initialize centroids
    vector<pair<double,double>> r = vector_range(points);
    for (Point& c : centroids)
        c = uniform_random_vector(r);

    Clustering clustering;
    for (unsigned t = 0; t < max_iterations; ++t) {
        // cluster assignment
        clustering = clustering_for_centroids(n, k, points, centroids);

        // centroid update
        previous_centroids = std::move(centroids);
        centroids = compute_centroids(points, clustering);

        // check stopping criterion
        double d = 0.0;
        for (unsigned j = 0; j < k; ++j)
            d += distance_squared(previous_centroids[j], centroids[j]);
        if (d <= epsilon)
            break;
    }

    return clustering;
}

Clustering kmeans_repeat(unsigned int repetitions,
                         const vector<Point>& points,
                         unsigned int k,
                         double epsilon,
                         unsigned int max_iterations) {
    unsigned n = points.size();
    Clustering best_clustering;
    double best_sse = std::numeric_limits<double>::max();
    for (unsigned int i = 0; i < repetitions; ++i) {
        Clustering clustering = kmeans(points, k, epsilon, max_iterations);
        double sse = clustering_sse(n, k, points, clustering);
        if (sse < best_sse) {
            best_clustering = clustering;
            best_sse = sse;
        }
    }
    return best_clustering;
}
