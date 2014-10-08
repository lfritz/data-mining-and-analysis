#include <chrono>
#include <iostream>
#include <memory>

#include "apriori.h"
#include "bruteforce.h"
#include "database.h"
#include "msweb.h"

using std::cout;

int main(int argc, char * argv[]) {
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " minsup msweb-file\n";
        return 1;
    }

    int minsup = std::stoi(argv[1]);
    std::string filename = argv[2];

    cout << "Loading input data...\n";
    Database d(load_msweb_file(filename));

    cout << "Loaded " << d.nItems() << " items and " << d.nTransactions()
         << " transactions.\n";
    cout << "Finding frequent itemsets...\n";

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    // FrequentItemsets fi = brute_force(d, minsup);
    FrequentItemsets fi = apriori(d, minsup);
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    cout << "Done (" << elapsed_seconds.count() << " s).\n",

    cout << "Found " << fi.size() << " requent itemsets:\n";
    for (const auto& kv : fi) {
        cout << kv.second << " ";
        d.printItemset(cout, kv.first, " ");
        cout << "\n";
    }

    return 0;
}
