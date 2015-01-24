#pragma once

#include <vector>

// Vector of clusters. Each cluster is a set of points, which are represented
// by indices into a vector.
typedef std::vector<std::vector<unsigned>> Clustering;

// Check if c is a valid clustering for n points and k clusters.
bool valid_clustering(Clustering c, unsigned n, unsigned k);
