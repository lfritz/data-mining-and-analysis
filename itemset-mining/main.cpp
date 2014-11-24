#include <chrono>
#include <functional>
#include <iostream>
#include <memory>

#include <apriori.h>
#include <associationrules.h>
#include <bruteforce.h>
#include <declat.h>
#include <eclat.h>
#include <transactiondatabase.h>
#include <verticaldatabase.h>

#include "msweb.h"

using std::cout;
using std::get;
using std::string;

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
    if (argc != 5) {
        cout << "Usage: " << argv[0] << " algorithm minsup minconf file\n"
             << "Algorithm can be brute-force, apriori, declat or eclat.\n";
        return 1;
    }
    char algorithm = argv[1][0];
    unsigned int minsup = std::stoi(argv[2]);
    double minconf = std::stod(argv[3]);
    std::string filename = argv[4];

    // load input data
    cout << "Loading input data...\n";
    TransactionDatabase td(load_msweb_file(filename));
    cout << "Loaded " << td.nItems() << " items and " << td.nTransactions()
         << " transactions.\n";
    cout << "Finding frequent itemsets...\n";

    // find frequent items
    FrequentItemsets fi;
    if (algorithm == 'a') {
        time("apriori algorithm", [&fi,&td,minsup]() {
            fi = apriori(td, minsup);
        });
    } else if (algorithm == 'b') {
        time("brute-force algorithm", [&fi,&td,minsup]() {
            fi = brute_force(td, minsup);
        });
    } else {
        VerticalDatabase vd(td);
        if (algorithm == 'd') {
            time("declat algorithm", [&fi,&vd,minsup]() {
                fi = declat(vd, minsup);
            });
        } else {
            time("eclat algorithm", [&fi,&vd,minsup]() {
                fi = eclat(vd, minsup);
            });
        }
    }

    // find association rules
    std::vector<AssociationRule> rules;
    time("finding association rules", [&rules,&fi,&minconf]() {
        rules = association_rules(fi, minconf);
    });

    // print results
    cout << "Found " << rules.size() << " association rules:\n";
    for (const auto& rule : rules) {
        td.printItemset(cout, get<0>(rule), " ");
        cout << " -> ";
        td.printItemset(cout, get<1>(rule), " ");
        cout << " (support: " << get<2>(rule)
             << ", confidence: " << get<3>(rule) << ")\n";
    }

    return 0;
}
