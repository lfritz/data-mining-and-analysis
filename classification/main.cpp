#include <chrono>
#include <functional>
#include <iostream>
#include <memory>

#include <bayesclassifier.h>
#include <knnclassifier.h>
#include <naivebayesclassifier.h>

#include "csv.h"

using std::cout;
using std::get;
using std::make_unique;
using std::string;
using std::unique_ptr;
using std::vector;

void print(const Eigen::VectorXd& v) {
    for (int i = 0; i < v.size(); ++i) {
        if (i)
            cout << ", ";
        cout << v(i);
    }
}

void time(const string& name, std::function<void()> f) {
    cout << "Running " << name << "...\n";
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    f();
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    cout << "Done (" << elapsed_seconds.count() << " s).\n";
}

int main(int argc, char * argv[]) {
    // parse arguments
    if (argc != 4) {
        cout << "Usage: " << argv[0] << " algorithm training-data test-data\n"
             << "Algorithm can be bayes, knn or naive-bayes.\n"
             << "    bayes is a Full Bayes classifier\n"
             << "    naive-bayes is a Naive Bayes classifier\n"
             << "    knn is a K Nearest Neighbors classifier with k=5\n";
        return 1;
    }
    char algorithm = argv[1][0];
    string training_filename = argv[2];
    string test_filename = argv[3];

    // load input data
    vector<string> labels;
    ClassificationDataset training = load_csv(training_filename, labels);
    ClassificationDataset test = load_csv(test_filename, labels);
    cout << "Loaded " << training.x.size() << " training datasets.\n";
    cout << "Loaded " << test.x.size() << " test datasets.\n";

    // train classifier
    cout << "Training classifier...\n";
    unique_ptr<Classifier> classifier;
    if (algorithm == 'b')
        classifier = make_unique<BayesClassifier>(training.x, training.y);
    else if (algorithm == 'k')
        classifier = make_unique<KnnClassifier>(std::move(training.x),
                                                std::move(training.y),
                                                5);
    else
        classifier = make_unique<NaiveBayesClassifier>(training.x, training.y);

    // use classifier
    cout << "Prediting class labels...\n";
    unsigned n_test = test.x.size();
    for (unsigned i = 0; i < n_test; ++i) {
        auto x = test.x[i];
        int predicted = classifier->predict(x);
        print(x);
        cout << ": " << labels[predicted] << " (actual: " << labels[test.y[i]]
             << ")\n";
    }

    return 0;
}
