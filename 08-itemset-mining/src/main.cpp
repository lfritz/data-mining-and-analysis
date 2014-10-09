#include <chrono>
#include <functional>
#include <iostream>
#include <memory>

#include "apriori.h"
#include "bruteforce.h"
#include "eclat.h"
#include "msweb.h"
#include "transactiondatabase.h"
#include "verticaldatabase.h"

using std::cout;
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
    if (argc != 4) {
        cout << "Usage: " << argv[0] << " algorithm minsup msweb-file\n"
             << "Algorithm can be 'brute-force', 'apriori' or 'eclat.\n";
        return 1;
    }

    char algorithm = argv[1][0];
    unsigned int minsup = std::stoi(argv[2]);
    std::string filename = argv[3];

    cout << "Loading input data...\n";
    TransactionDatabase td(load_msweb_file(filename));

    cout << "Loaded " << td.nItems() << " items and " << td.nTransactions()
         << " transactions.\n";
    cout << "Finding frequent itemsets...\n";

    FrequentItemsets fi;
    if (algorithm == 'a') {
        time("apriori algorithm", [&fi,&td,minsup]() {
            fi = apriori(td, minsup);
        });
    } else if (algorithm == 'b') {
        time("brute-force algorithm", [&fi,&td,minsup]() {
            fi = brute_force(td, minsup);
        });
    } else if (algorithm == 'e') {
        VerticalDatabase vd(td);
        time("eclat algorithm", [&fi,&vd,minsup]() {
            fi = eclat(vd, minsup);
        });
    }

    cout << "Found " << fi.size() << " requent itemsets:\n";
    for (const auto& kv : fi) {
        cout << kv.second << " ";
        td.printItemset(cout, kv.first, " ");
        cout << "\n";
    }

    return 0;
}
