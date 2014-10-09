#include "msweb.h"

#include <boost/regex.hpp>
#include <fstream>
#include <map>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

using boost::regex;
using boost::regex_match;
using std::runtime_error;
using std::string;
using std::vector;

TransactionDatabase load_msweb_file(const string& filename) {
    std::ifstream input(filename);
    if ( ! input) {
        std::ostringstream o;
        o << "Could not open file " << filename;
        throw runtime_error(o.str());
    }

    // regular expressions to parse a line of input
    static const regex attributeLine("A,([0-9]+),1,\"[^\"]+\",\"([^\"]+)\"");
    static const regex caseLine("C,\"[^\"]+\",[0-9]+");
    static const regex voteLine("V,([0-9]+),1");

    vector<vector<int>> ts;
    vector<string> is;

    // maps attribute ids from the file to item ids in the database
    std::map<int, int> attributes;

    // set when we encounter a case line
    vector<int> * current_transaction = nullptr;

    // go though file one line at a time
    boost::smatch match;
    for (string line; std::getline(input, line); ) {
        if (line.size() == 0)
            continue; // skip empty line
        switch (line[0]) {

            case 'A':
            // attribute line: add to 'is' and 'attributes'
            if ( ! regex_match(line, match, attributeLine)) {
                std::cout << "Cannot parse line: " << line << std::endl;
            } else {
                if (current_transaction)
                    throw runtime_error("parse error: "
                                        "attribute line after case line");
                int attribute_id = std::stoi(match[1]);
                string name = match[2];
                int item_id = is.size();
                is.push_back(name);
                attributes[attribute_id] = item_id;
            }
            break;

            case 'C':
            // case line: add to 'ts' and set 'current_transaction'
            if ( ! regex_match(line, match, caseLine)) {
                std::cout << "Cannot parse line: " << line << std::endl;
            } else {
                int transaction_id = ts.size();
                ts.push_back(vector<int>());
                current_transaction = &ts[transaction_id];
            }
            break;

            case 'V':
            // vote line: set bit in 'current_transaction'
            if ( ! regex_match(line, match, voteLine)) {
                std::cout << "Cannot parse line: " << line << std::endl;
            } else {
                if ( ! current_transaction)
                    throw runtime_error("parse error: vote line "
                                        "without preceding case line.");
                int attribute_id = std::stoi(match[1]);
                int item_id = attributes[attribute_id];
                current_transaction->push_back(item_id);
            }
            break;

            default:
            // another type of line -- we'll just skip it
            break;

        }
    }

    return TransactionDatabase(is, ts);
}
