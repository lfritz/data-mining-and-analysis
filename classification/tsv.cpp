#include "tsv.h"

#include <boost/algorithm/string.hpp>
#include <fstream>

using Eigen::VectorXd;
using std::string;
using std::vector;

ClassificationDataset load_tsv(const string& filename) {
    std::ifstream input(filename);
    if ( ! input) {
        std::ostringstream o;
        o << "Could not open file " << filename;
        throw std::runtime_error(o.str());
    }

    vector<VectorXd> x;
    vector<int> y;

    for (string line; std::getline(input, line); ) {
        // skip empty lines
        if (line.size() == 0)
            continue;

        // split line
        vector<string> strings;
        boost::split(strings, line, [](char c) { return c == '\t'; });

        // get point
        VectorXd v(3);
        for (unsigned i = 0; i < 3; ++i)
            v(i) = atof(strings[i].c_str());
        x.push_back(v);

        // get class
        y.push_back(strings[3] == "1");
    }

    return ClassificationDataset { x, y };
}
