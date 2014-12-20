# Data Mining and Analysis

Implementations of a number of algorithms for data mining which I wrote while working through the book [http://www.dataminingbook.info/](Data Mining and Analysis) by Mohammed J. Zaki and Wagner Meira Jr. There's also unit tests and three small programs that apply the algorithms to sample data.

All code, except for code in the "lib" directory, is open-source software under
the terms of the MIT License (see accompanying file `LICENSE`).


## Directory structure

The project source code is organized in the following directories:

* `src`: implementations of data mining algorithms,
* `test`: unit tests for code in `src`,
* `lib`: the [https://github.com/philsquared/Catch](Catch library) used for unit tests,
* `classification`: command-line program that uses classifier algorithms,
* `itemset-mining`: command-line program that uses the itemset mining algorithms,
* `clustering-gui`: GUI program that uses the clustering algorithms.


## Requirements

In addition to the Catch library, which is included in the repository, the following libraries are needed to build the code:

* [http://eigen.tuxfamily.org/](Eigen library) for linear algebra,
* Qt 5 (only for *clustering-gui*),
* Boost (only for *classifiction*).

The code uses features from C++11 and C++14, so you'll also need an up-to-date C++ compiler. I've tested it with GCC 4.9.1 and Clang 3.5.0.


## Building

The project contains [http://www.cmake.org/](cmake) build files that can be used to build everything. It's usually best to build in a separate build directory. In the Linux (or OS X) shell, you can use these commands to build everything and run the unit tests:

```
mkdir build
cd build
cmake ..
make
./test/unittest
```


## src

The `src` directory contains implementations of the following algorithms:

* Itemset mining:
  * Brute-force frequent itemset mining algorithm (`bruteforce.h`)
  * Apriori algorithm for frequent itemset mining (`apriori.h`)
  * Eclat algorithm for frequent itemst mining (`eclat.h`)
  * Declat algorithm for frequent itemset mining (`declat.h`)
  * Algorithm for generating association rules (`associationrules.h`)
* Clustering:
  * K-Means clustering algorithm (`kmeans.h`)
  * Kernel K-Means clustering algorithm (`kernelkmeans.h`)
* Probabilistic classification:
  * Bayes classifier (`bayesclassifier.h`)
  * Naive Bayes classifier (`naivebayesclassifier.h`)
  * K Nearest Neighbors classifier (`knnclassifier.h`)
* Kernel methods:
  * homogeneous and inhomogeneous polynomial kernels, Gaussian kernel (`kernelfunction.h`)


## itemset-mining

Command-line program that applies the itemset mining algorithms to the [http://archive.ics.uci.edu/ml/datasets/Anonymous+Microsoft+Web+Data]("Anonymous Microsoft Web" sample dataset).


## classification

Command-line program that applies the classifiction algorithms to the [http://archive.ics.uci.edu/ml/datasets/Skin+Segmentation]("Skin Segmentation" sample dataset).


## clustering-gui

GUI program that applies the clustering algorithms to a set of 2D points specified by the user.
