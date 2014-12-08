#include "csv.h"

#include <boost/algorithm/string.hpp>
#include <fstream>
#include <map>

using Eigen::VectorXd;
using std::runtime_error;
using std::map;
using std::string;
using std::vector;

ClassificationDataset load_csv(const string& filename,
                               vector<string>& labels) {
    std::ifstream input(filename);
    if ( ! input) {
        std::ostringstream o;
        o << "Could not open file " << filename;
        throw runtime_error(o.str());
    }

    vector<VectorXd> x;
    vector<int> y;
    map<string, int> class_map;
    for (int i = 0; i < labels.size(); ++i)
        class_map[labels[i]] = i;
    int next_class_id = 0;

    for (string line; std::getline(input, line); ) {
        // skip empty lines
        if (line.size() == 0)
            continue;

        // split line
        vector<string> strings;
        boost::split(strings, line, [](char c) { return c == ','; });

        // get point
        unsigned d = strings.size() - 1;
        VectorXd v(d);
        for (unsigned i = 0; i < d; ++i)
            v(i) = atof(strings[i].c_str());
        x.push_back(v);

        // get class
        string class_name = strings[d];
        if (class_map.count(class_name)) {
            y.push_back(class_map[class_name]);
        } else {
            int class_id = next_class_id++;
            class_map[class_name] = class_id;
            labels.push_back(class_name);
            y.push_back(class_id);
        }
    }

    return ClassificationDataset { x, y };
}
