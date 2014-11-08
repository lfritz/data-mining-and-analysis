#pragma once

// Kernel K-means algorithm for clustering, from chapter 13.2 of Data Mining
// and Analysis: Fundamental Concepts and Algorithms by Mohammed J. Zaki and
// Wagner Meira Jr.

#include <vector>

#include "clustering.h"

typedef std::vector<std::vector<double>> Kernel;

// Randomly partition n points into k clusters.
Clustering random_clustering(unsigned n, unsigned k);

// Compute the squared norm of the cluster mean in feature space.
double cluster_sqnorm(const Kernel& kernel, const std::vector<unsigned>& c);

// Compute the average kernel value for point j and cluster c.
double avg_kernel_value(const Kernel& kernel,
                        unsigned j,
                        const std::vector<unsigned>& c);

// Find the closest cluster for point j in feature space.
unsigned find_closest_cluster(unsigned k,
                              unsigned j,
                              const std::vector<double>& sqnorm,
                              const std::vector<std::vector<double>>& avg);

// Count the number of elements that are in both a and b.
unsigned count_same(const std::vector<unsigned>& a,
                    const std::vector<unsigned>& b);

// The change between two clusterings of a set of points, measure as the
// fraction of points reassigned to a different cluster.
double clustering_change(unsigned n,
                         unsigned k,
                         const Clustering& a,
                         const Clustering& b);

// Kernel K-means algorithm for clustering in feature space: group the points
// into k clusters based on the values of a kernel function. The algorithm
// proceeds iteratively for at most max_iterations or until the change between
// successive iterations (as measured by clustering_change) is at most epsilon.
Clustering kernel_kmeans(const Kernel& kernel,
                         unsigned k,
                         double epsilon=0.0,
                         unsigned max_iterations=1000);


// Compute the sum of squared errors (SSE) of a clustering in feature space.
double clustering_kernel_sse(const Kernel& kernel,
                             const Clustering& clustering);

// Run kmeans multiple times and take the result with the lowest SSE (sum of
// squared errors).
Clustering kernel_kmeans_repeat(unsigned repetitions,
                                const Kernel& kernel,
                                unsigned k,
                                double epsilon=0.0,
                                unsigned max_iterations=1000);
