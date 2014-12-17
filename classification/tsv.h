#pragma once

#include <Eigen/Core>
#include <string>
#include <vector>

// A dataset for a classification task.
struct ClassificationDataset {
    std::vector<Eigen::VectorXd> x;   // points
    std::vector<int> y;               // class labels
};

// Load dataset for classification task from tab-separated values file.
ClassificationDataset load_tsv(const std::string& filename);
