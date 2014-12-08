#pragma once

#include <Eigen/Core>
#include <string>
#include <vector>

// A dataset for a classification task.
struct ClassificationDataset {
    std::vector<Eigen::VectorXd> x;   // points
    std::vector<int> y;               // class labels
};

// Load dataset for classification task from comma-separated values file. Each
// line in the file contains a point's coordinates and its class label.
ClassificationDataset load_csv(const std::string& filename,
                               std::vector<std::string>& labels);
