#include <chrono>
#include <functional>
#include <iostream>

#include <bayesclassifier.h>

#include "csv.h"

using std::cout;
using std::get;
using std::string;
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
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " training-data test-data\n";
        return 1;
    }
    string training_filename = argv[1];
    string test_filename = argv[2];

    vector<string> labels;
    ClassificationDataset training = load_csv(training_filename, labels);
    ClassificationDataset test = load_csv(test_filename, labels);

    cout << "Loaded " << training.x.size() << " training datasets.\n";
    cout << "Loaded " << test.x.size() << " test datasets.\n";
    cout << "Training classifier...\n";
    BayesClassifier classifier(training.x, training.y);

    cout << "Prediting class labels...\n";
    unsigned n_test = test.x.size();
    for (unsigned i = 0; i < n_test; ++i) {
        auto x = test.x[i];
        int predicted = classifier.predict(x);
        print(x);
        cout << ": " << labels[predicted] << " (actual: " << labels[test.y[i]]
             << ")\n";
    }

    return 0;
}
