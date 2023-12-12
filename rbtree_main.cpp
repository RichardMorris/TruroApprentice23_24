#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "rbtree.h"
using std::cout, std::endl;
int main() {
    // input loop reading a line at a time
    // and splitting it into ints
    std::string line;
    std::vector<int> vals;
    rbtree tree;
    cout << "Enter a list of integers separated by spaces, 'clear' to clear the tree" << endl;
    while (std::getline(std::cin, line)) {
        vals.clear();
        std::istringstream iss(line);
        // if line is "clear" then clear the tree
        if (line == "clear") {
            cout << "clearing tree" << endl;
            tree.clear();
            continue;
        }
        if (line == "clear") {
            break;
        }
        int n;
        while (iss >> n) {
            vals.push_back(n);
        }
        // print the vector
        for (auto v:vals) {
            auto n = tree.insert_raw(v);
            cout << "before fixup: " << v << endl;
            tree.dump();
            tree.addFixup(n);
            cout << "after fixup: " << v << endl;
            tree.dump();
        }
        std::cout  << "Black depth test: " << (tree.black_depth_test() ? "true" : "false") 
                   << " red adjacent test " << (tree.no_adjacent_red_test()  ? "true" : "false"  )<< std::endl;
        cout << endl;

    }

    return 0;
}
