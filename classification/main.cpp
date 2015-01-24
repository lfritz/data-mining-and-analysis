#include <boost/timer/timer.hpp>
#include <Eigen/Core>
#include <iostream>
#include <memory>

#include <bayesclassifier.h>
#include <knnclassifier.h>
#include <naivebayesclassifier.h>

#include "tsv.h"

using Eigen::MatrixXd;
using std::cout;
using std::make_unique;
using std::string;
using std::vector;

void print(const Eigen::VectorXd& v) {
    for (int i = 0; i < v.size(); ++i) {
        if (i)
            cout << ", ";
        cout << v(i);
    }
}

int main(int argc, char * argv[]) {
    // parse arguments
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " file algorithm\n"
             << "Algorithm can be b, k or n:\n"
             << "    b -- Full Bayes classifier\n"
             << "    n -- Naive Bayes classifier\n"
             << "    k -- K Nearest Neighbors classifier with k=5\n";
        return 1;
    }
    string filename = argv[1];
    char algorithm = argv[2][0];

    // load input data
    ClassificationDataset tr = load_tsv(filename);
    ClassificationDataset te;
    unsigned n = tr.x.size();

    // split into training and test data
    unsigned n_tr = (unsigned)std::round(0.7 * (double)n);
    unsigned n_te = n - n_tr;
    te.x.insert(te.x.cbegin(), tr.x.cbegin() + n_tr, tr.x.cend());
    te.y.insert(te.y.cbegin(), tr.y.cbegin() + n_tr, tr.y.cend());
    tr.x.erase(tr.x.cbegin() + n_tr, tr.x.cend());
    tr.y.erase(tr.y.cbegin() + n_tr, tr.y.cend());
    cout << n << " instances (" << n_tr << " training, " << n_te << " test)\n";

    // train classifier
    std::unique_ptr<Classifier> c;
    if (algorithm == 'b') {
        cout << "Training Bayes classifier...\n";
        boost::timer::auto_cpu_timer t;
        c = make_unique<BayesClassifier>(tr.x, tr.y);
    } else if (algorithm == 'k') {
        cout << "Training K Nearest Neighbors classifier...\n";
        boost::timer::auto_cpu_timer t;
        c = make_unique<KnnClassifier>(std::move(tr.x), std::move(tr.y), 5);
    } else {
        cout << "Training Naive Bayes classifier...\n";
        boost::timer::auto_cpu_timer t;
        c = make_unique<NaiveBayesClassifier>(tr.x, tr.y);
    }

    // apply classifier to test data
    Eigen::MatrixXd m = Eigen::MatrixXd::Zero(2,2);
    {
        cout << "Predicting class labels...\n";
        boost::timer::auto_cpu_timer t;
        auto xi = te.x.cbegin();
        auto yi = te.y.cbegin();
        for (; xi != te.x.cend(); ++xi, ++yi)
            ++m(c->predict(*xi), *yi);
    }

    double true_positive  = m(1,1);
    double false_positive = m(1,0);
    double true_negative  = m(0,0);
    double false_negative = m(0,1);

    double accuracy  = (true_positive + true_negative) /  (double)n_te;
    double precision = true_positive / (true_positive + false_positive);
    double recall    = true_positive / (true_positive + false_negative);

    cout << "Results:\n"
         << "    True positives:  " << true_positive << "\n"
         << "    False positives: " << false_positive << "\n"
         << "    True negatives:  " << true_negative << "\n"
         << "    False negatives: " << false_negative << "\n"
         << "    Accuracy:        " << accuracy << "\n"
         << "    Precision:       " << precision << "\n"
         << "    Recall:          " << recall << "\n";

    return 0;
}
