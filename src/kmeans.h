#pragma once

// K-means algorithm for clustering, from chapter 13.1 of Data Mining and
// Analysis: Fundamental Concepts and Algorithms by Mohammed J. Zaki and Wagner
// Meira Jr.

#include <utility>
#include <vector>

typedef std::vector<double> Point;

// Result of clustering using centroids: centroid[j] is the center of cluster j
// and cluster[i] indicates which cluster point i is assigned to.
// XXX do we need to return the centroids?
struct Clustering {
    std::vector<Point> centroids;
    std::vector<unsigned> cluster;
};

// Compute the sum of squared errors (SSE) for a clustering.
double clustering_sse(const std::vector<Point>& points,
                      const Clustering& clustering);

// Determine the range of values in each dimension for a set of vectors.
std::vector<std::pair<double,double>>
vector_range(const std::vector<Point>& points);

// Randonly generate double value in the given range.
double uniform_random_double(double min, double max);

// Randomly generate double vector in the given range.
Point uniform_random_vector(const std::vector<std::pair<double,double>>& r);

// K-means algorithm for clustering: group the points into k clusters. The
// algorithm proceeds iteratively for at most max_iterations or until the
// change between successive iterations (measured as the total distance that
// the centroids moved) is at most epsilon.
Clustering kmeans(const std::vector<Point>& points,
                  unsigned k,
                  double epsilon,
                  unsigned max_iterations=1000);

// Run kmeans multiple times and take the result with the lowest SSE (sum of
// squared errors).
Clustering kmeans_repeat(unsigned repetitions,
                         const std::vector<Point>& points,
                         unsigned k,
                         double epsilon,
                         unsigned max_iterations=1000);
