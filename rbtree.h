#include <iostream>
#include<vector>

enum rbcolor { red, black };

class rbnode {
    int val;
    rbcolor color;
    rbnode* left;
    rbnode* right;
public:
    rbnode(int v) {
        val = v;
        left = nullptr;
        right = nullptr;
    }
    void insert(int val) {
        if(val <= this->val) {
            if(left == nullptr) {
                left = new rbnode(val);
            } else {
                left->insert(val);
            }
        } else {
            if(right == nullptr) {
                right = new rbnode(val);
            } else {
                right->insert(val);
            }
        }
    }

    void fill_vals(std::vector<int>& vals) {
        if(left != nullptr) {
            left->fill_vals(vals);
        }
        vals.push_back(val);
        if(right != nullptr) {
            right->fill_vals(vals);
        }
    }

    int get_val() {
        return val;
    }

    rbnode* get_left() {
        return left;
    }

    rbnode* get_right() {
        return right;
    }

    rbcolor get_colour() {
        return color;
    }

    void set_black() {
        color = black;
    }

    void set_red() {
        color = red;
    }
};

class rbtree {
    rbnode* root = nullptr;

public:
    void insert(int val) {
        if(root == nullptr) {
            root = new rbnode(val);
        } else {
            root->insert(val);
        }
    };
    
    // method to return a sorted list of all values in the tree
    // EJ Item 54: Return empty collections or arrays, not nulls
    std::vector<int> get_vals() {
        std::vector<int> vals;
        if(root != nullptr) {
            root->fill_vals(vals);     
        }
        return vals;
    };
};