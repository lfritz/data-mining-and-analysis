# Data Mining and Analysis

Implementations of a number of algorithms for data mining which I wrote while working through the book [Data Mining and Analysis](http://www.dataminingbook.info/) by Mohammed J. Zaki and Wagner Meira Jr. There's also unit tests and three small programs that apply the algorithms to sample data.

All code, except for code in the "lib" directory, is open-source software under
the terms of the MIT License (see accompanying file `LICENSE`).


## Directory structure

The project source code is organized in the following directories:

* `src`: implementations of data mining algorithms,
* `test`: unit tests for code in `src`,
* `lib`: the [Catch library](https://github.com/philsquared/Catch) used for unit tests,
* `classification`: command-line program that uses classifier algorithms,
* `itemset-mining`: command-line program that uses the itemset mining algorithms,
* `clustering-gui`: GUI program that uses the clustering algorithms.


## Requirements

In addition to the Catch library, which is included in the repository, the following libraries are needed to build the code:

* Boost
* [Eigen library](http://eigen.tuxfamily.org/) for linear algebra,
* Qt 5 (only for *clustering-gui*).

The code uses features from C++11 and C++14, so you'll also need an up-to-date C++ compiler. I've tested it with GCC 4.9.1 and Clang 3.5.0.


## Building

The project contains [cmake](http://www.cmake.org/) build files that can be used to build everything. It's usually best to build in a separate build directory. In the Linux (or OS X) shell, you can use these commands to build everything and run the unit tests:

```
mkdir build
cd build
cmake ..
make
./test/unittest
```

If you're building with Clang, you can enable the [AddressSanitizer](http://clang.llvm.org/docs/AddressSanitizer.html) memory error detector by setting the variable `USE_SANITIZER` to `Address`. On the command line, that would look something like this:

```
clang -DCMAKE_CXX_COMPILER=clang++ -DUSE_SANITIZER=Address ..
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

Command-line program that applies the itemset mining algorithms to the ["Anonymous Microsoft Web" sample dataset](http://archive.ics.uci.edu/ml/datasets/Anonymous+Microsoft+Web+Data) from the [UC Irvine Machine Learning Repository](http://archive.ics.uci.edu/ml/). You can download the data and run the program like this:

```
wget http://archive.ics.uci.edu/ml/machine-learning-databases/anonymous/anonymous-msweb.data
./itemset-mining a 500 0.8 anonymous-msweb.data
```

Run `itemset-mining` by iteself to get an overview of command-line arguments.


## classification

Command-line program that applies the classifiction algorithms to the ["Skin Segmentation" sample dataset](http://archive.ics.uci.edu/ml/datasets/Skin+Segmentation), also from the UC Irvine Machine Learning Repository. It divides the data into training and test datasets by simply using the last 30 % as test data, so it's a good idea to first randomize the order of the entries first. On the command line, you can do this using the `shuf` program, which is part of [GNU Coreutils](https://www.gnu.org/software/coreutils/):

```
wget http://archive.ics.uci.edu/ml/machine-learning-databases/00229/Skin_NonSkin.txt
shuf Skin_NonSkin.txt > shuffled.txt
./classification shuffled.txt n
```

Run `classification` by iteself to get an overview of command-line arguments.


## clustering-gui

GUI program that applies the clustering algorithms to a set of 2D points specified by the user. Click in the main area of the GUI to set points, then click *K-means* or *Kernel K-means* to have one of the algorithms automatically divide the points into a configurable number of clusters.
