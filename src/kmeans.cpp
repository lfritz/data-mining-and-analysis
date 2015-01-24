#include "kmeans.h"

#include <cassert>
#include <limits>

#include "algorithm.h"

using Eigen::VectorXd;
using std::pair;
using std::vector;

double clustering_sse(unsigned n,
                      unsigned k,
                      const vector<VectorXd>& points,
                      const Clustering& clustering) {
    vector<VectorXd> centroids = compute_centroids(points, clustering);
    double sse = 0.0;
    for (unsigned j = 0; j < k; ++j) {
        const vector<unsigned>& cluster = clustering[j];
        const VectorXd& centroid = centroids[j];
        for (unsigned i : cluster)
            sse += squared_distance(points[i], centroid);
    }
    return sse;
}

void vector_range(const vector<VectorXd>& points,
                  VectorXd& min,
                  VectorXd& max) {
    assert( ! points.empty());
    min = points[0];
    max = points[0];
    for (unsigned i = 1; i < points.size(); ++i) {
        const VectorXd& p = points[i];
        min = min.cwiseMin(p);
        max = max.cwiseMax(p);
    }
}

VectorXd uniform_random_vector(const VectorXd& min,
                               const VectorXd& max) {
    unsigned d = min.size();
    // get random values in the range [0,1]
    VectorXd v = (VectorXd::Random(d) + VectorXd::Constant(d,1)) / 2;
    // scale random value
    return v.cwiseProduct(max-min) + min;
}

vector<VectorXd> compute_centroids(const vector<VectorXd>& points,
                                   const Clustering& clustering) {
    unsigned d = points[0].size();
    vector<VectorXd> centroids;
    for (const vector<unsigned>& cluster : clustering) {
        VectorXd centroid = VectorXd::Zero(d);
        for (unsigned i : cluster)
            centroid += points[i];
        centroid /= (double)cluster.size();
        centroids.push_back(centroid);
    }
    return centroids;
}

Clustering clustering_for_centroids(unsigned n,
                                    unsigned k,
                                    const vector<VectorXd>& points,
                                    const vector<VectorXd>& centroids) {
    Clustering clustering(k);
    for (unsigned i = 0; i < n; ++i) {
        const VectorXd& p = points[i];
        auto sq_distance_from_p = [&centroids,&p](unsigned j) {
            return squared_distance(centroids[j], p);
        };
        unsigned closest_cluster = arg_min(0u, k, sq_distance_from_p);
        clustering[closest_cluster].push_back(i);
    }
    return clustering;
}

Clustering kmeans(const vector<VectorXd>& points,
                  unsigned k,
                  double epsilon,
                  unsigned max_iterations) {
    unsigned n = points.size();
    vector<VectorXd> centroids(k);
    vector<VectorXd> previous_centroids;

    // initialize centroids
    VectorXd min;
    VectorXd max;
    vector_range(points, min, max);
    for (VectorXd& c : centroids)
        c = uniform_random_vector(min, max);

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
            d += squared_distance(previous_centroids[j], centroids[j]);
        if (d <= epsilon)
            break;
    }

    return clustering;
}

Clustering kmeans_repeat(unsigned int repetitions,
                         const vector<VectorXd>& points,
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
