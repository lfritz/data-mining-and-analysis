#pragma once

// K-means algorithm for clustering, from chapter 13.1 of Data Mining and
// Analysis: Fundamental Concepts and Algorithms by Mohammed J. Zaki and Wagner
// Meira Jr.

#include <utility>
#include <vector>

#include "clustering.h"

typedef std::vector<double> Point;

// Compute the sum of squared errors (SSE) for a clustering.
double clustering_sse(unsigned n,
                      unsigned k,
                      const std::vector<Point>& points,
                      const Clustering& clustering);

// Determine the range of values in each dimension for a set of vectors.
std::vector<std::pair<double,double>>
vector_range(const std::vector<Point>& points);

// Randonly generate double value in the given range.
double uniform_random_double(double min, double max);

// Randomly generate double vector in the given range.
Point uniform_random_vector(const std::vector<std::pair<double,double>>& r);

// Compute the centroid of each cluster, ie, the mean of all points in the
// cluster.
std::vector<Point> compute_centroids(const std::vector<Point>& points,
                                     const Clustering& clustering);

// Assign each point to the closest centroid.
Clustering clustering_for_centroids(unsigned n,
                                    unsigned k,
                                    const std::vector<Point>& points,
                                    const std::vector<Point>& centroids);

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
