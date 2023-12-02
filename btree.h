#include <iostream>
#include<vector>


class bnode {
    int vals[4];
    int nvals = 1;
    bnode* left;
    bnode* mid;
    bnode* right;

    // an array of 4 pointers to bnodes
    bnode* children[4];
public:
    bnode(int val) {
        vals[0] = val;
        left = nullptr;
        mid = nullptr;
        right = nullptr;
    }

    void insert(int val) {
        if(nvals==1) {
            vals[1] = val;
            nvals++;
        }
    }
};

class btree {
    bnode* root = nullptr;

public:
    void insert(int val) {
        if(root == nullptr) {
            root = new bnode(val);
        } else {
            root->insert(val);
        }
    };
    
    // method to return a sorted list of all values in the tree
    
    std::vector<int> get_vals() {
        std::vector<int> vals = {1,2,3,4,5};
        return vals;
    };
};