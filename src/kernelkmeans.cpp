#include "kernelkmeans.h"

#include <algorithm>
#include <random>

using std::vector;

Clustering random_clustering(unsigned n, unsigned k) {
    static std::random_device random_device;
    static std::default_random_engine random_engine(random_device());
    std::uniform_int_distribution<unsigned> uniform_dist(0, k-1);
    Clustering clusters(k);
    for (unsigned i = 0; i < n; ++i)
        clusters[uniform_dist(random_engine)].push_back(i);
    return clusters;
}

double cluster_sqnorm(const Kernel& kernel, const vector<unsigned>& c) {
    double s = 0.0;
    for (unsigned a : c)
        for (unsigned b : c)
            s += kernel[a][b];
    double cluster_size = (double)c.size();
    return s / (cluster_size*cluster_size);
}

double avg_kernel_value(const Kernel& kernel,
                        unsigned j,
                        const vector<unsigned>& c) {
    double a = 0.0;
    for (unsigned i : c)
        a += kernel[i][j];
    double cluster_size = (double)c.size();
    return a / cluster_size;
}

unsigned find_closest_cluster(unsigned k,
                              unsigned j,
                              const vector<double>& sqnorm,
                              const vector<vector<double>>& avg) {
    unsigned best_cluster = 0;
    double best_d = std::numeric_limits<double>::max();
    for (unsigned i = 0; i < k; ++i) {
        double d = sqnorm[i] - 2.0 * avg[j][i];
        if (d < best_d) {
            best_cluster = i;
            best_d = d;
        }
    }
    return best_cluster;
}

unsigned count_same(const vector<unsigned>& a,
                    const vector<unsigned>& b) {
    unsigned count = 0;
    for (unsigned i : a)
        count += std::find(std::begin(b), std::end(b), i) != std::end(b);
    return count;
}

double clustering_change(unsigned n,
                         unsigned k,
                         const Clustering& a,
                         const Clustering& b) {
    unsigned sum_same = 0;
    for (unsigned i = 0; i < k; ++i)
        sum_same += count_same(a[i], b[i]);
    return 1.0 - (1.0 / (double)n) * (double)sum_same;
}

Clustering kernel_kmeans(const Kernel& kernel,
                         unsigned k,
                         double epsilon,
                         unsigned max_iterations) {
    unsigned n = kernel.size();
    Clustering clusters = random_clustering(n, k);

    for (unsigned t = 0; t < max_iterations; ++t) {
        // compute squared norm of cluster means
        vector<double> sqnorm;
        for (const vector<unsigned>& c : clusters)
            sqnorm.push_back(cluster_sqnorm(kernel, c));

        // compute average kernel values
        vector<vector<double>> avg;
        for (unsigned j = 0; j < n; ++j) {
            vector<double> avg_j; // average kernel values for point j
            for (const vector<unsigned>& c : clusters)
                avg_j.push_back(avg_kernel_value(kernel, j, c));
            avg.push_back(avg_j);
        }

        // find closest cluster for each point
        Clustering previous_clusters = std::move(clusters);
        clusters = Clustering(k);
        for (unsigned j = 0; j < n; ++j)
            clusters[find_closest_cluster(k, j, sqnorm, avg)].push_back(j);

        // check stopping criterion
        if (clustering_change(n, k, previous_clusters, clusters) <= epsilon)
            break;
    }

    return clusters;
}

double clustering_kernel_sse(const Kernel& kernel,
                             const Clustering& clustering) {
    unsigned n = kernel.size();
    double sse = 0.0;
    for (unsigned j = 0; j < n; ++j)
        sse += kernel[j][j];
    for (const vector<unsigned>& c : clustering) {
        double cluster_size = (double)c.size();
        double sum = 0.0;
        for (unsigned a : c)
            for (unsigned b : c)
                sum += kernel[a][b];
        sse -= sum / cluster_size;
    }
    return sse;
}

Clustering kernel_kmeans_repeat(unsigned repetitions,
                                const Kernel& kernel,
                                unsigned k,
                                double epsilon,
                                unsigned max_iterations) {
    Clustering best_clustering;
    double best_sse = std::numeric_limits<double>::max();
    for (unsigned int i = 0; i < repetitions; ++i) {
        Clustering clustering =
            kernel_kmeans(kernel, k, epsilon, max_iterations);
        double sse = clustering_kernel_sse(kernel, clustering);
        if (sse < best_sse) {
            best_clustering = clustering;
            best_sse = sse;
        }
    }
    return best_clustering;
}
