#include <iostream>
#include<vector>

enum rbcolor { red, black };

class rbnode {
    int val;
    rbcolor color;
    rbnode* left;
    rbnode* right;
    rbnode* parent;
public:
    rbnode(int v) {
        val = v;
        left = nullptr;
        right = nullptr;
        color = red;
    }
    rbnode* insert(int val) {
        if(val <= this->val) {
            if(left == nullptr) {
                left = new rbnode(val);
                left->parent = this;
                return left;
            } else {
                return left->insert(val);
            }
        } else {
            if(right == nullptr) {
                right = new rbnode(val);
                right->parent = this;
                return right;
            } else {
                return right->insert(val);
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

    rbnode* get_parent() {
        return parent;
    }   

    rbnode* get_left() {
        return left;
    }

    rbnode* get_right() {
        return right;
    }

    void set_parent(rbnode* p) {
        parent = p;
    }

    void set_left(rbnode* l) {
        left = l;
    }

    void set_right(rbnode* r) {
        right = r;
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

    bool is_leaf() {
        return left == nullptr && right == nullptr;
    }

    int get_min_black_depth() {
        int min=0;
        if(left != nullptr) {
            int lmin = left->get_min_black_depth();
            min = lmin < min ? lmin : min;
        }
        if(right != nullptr) {
            int rmin = right->get_min_black_depth();
            min = rmin < min ? rmin : min;
        }   
        if(color == black) {
            min++;
        }
        return min;
    }
    int get_max_black_depth() {
        int max=0;
        if(left != nullptr) {
            int lmax = left->get_max_black_depth();
            max = lmax > max ? lmax : max;
        }
        if(right != nullptr) {
            int rmax = right->get_max_black_depth();
            max = rmax > max ? rmax : max;
        }
        if(color == black) {
            max++;
        }
        return max;
    }

    bool no_adjacent_red_test() {
        if(left != nullptr) {
            if(color == red && left->get_colour() == red) {
                return false;
            }
            if(!left->no_adjacent_red_test()) {
                return false;
            }
        }
        if(right != nullptr) {
            if(color == red && right->get_colour() == red) {
                return false;
            }
            if(!right->no_adjacent_red_test()) {
                return false;
            }
        }
        return true;
    }

    void dump(int depth) {
        for(int i=0;i<depth;i++) {
            std::cout << "  ";
        }
        std::cout << val << " " << (color == red ? "red" : "black") << std::endl;
        if(left != nullptr) {
            left->dump(depth+1);
        }
        if(right != nullptr) {
            right->dump(depth+1);
        }
    }
};

class rbtree {
    rbnode* root = nullptr;

public:
    rbnode* insert(int val) {
        if(root == nullptr) {
            root = new rbnode(val);
            root->set_black();
            root->set_parent(nullptr);
            return root;
        } else {
            return root->insert(val);
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
    }

    // method to return the root node
    rbnode* get_root() {
        return root;
    }

    void dump() {
        if(root != nullptr) {
            root->dump(0);
        }
    }

    // method to return the height of the tree
    int get_min_black_depth() {
        if(root != nullptr) {
            return root->get_min_black_depth();
        }
        return 0;
    };

    int get_max_black_depth() {
        if(root != nullptr) {
            return root->get_max_black_depth();
        }
        return 0;
    };    

    bool black_depth_test() {
        return get_min_black_depth() == get_max_black_depth();
    }

    bool no_adjacent_red_test() {
        if(root != nullptr) {
            return root->no_adjacent_red_test();
        }
        return true;
    }

    void addFixup(rbnode* node) {
        // if node is root, set it to black and return
        if(node == root) {
            node->set_black();
            return;
        }
        rbnode* parent = node->get_parent();
        // if parent is black, return
        // We have the situations: *is node we just inserted
        //    B         B       B                
        //   / \       / \     / \ 
        //  R*  R     R*  N    N  R
        // None of which violate the red-black tree properties

        if(parent->get_colour() == black) {
            return;
        }
        // Now get the grandparent and uncle
        rbnode* grandparent = parent->get_parent();
        rbnode* uncle = grandparent->get_left() == parent 
            ? grandparent->get_right() 
            : grandparent->get_left();
        // We have the situations:
        //       G
        //      / \ 
        //     P   U
        //    / \ 
        //   ?   R*

        //  If the uncle is red, we can just recolour
        //       G=B                 G=R
        //      /   \               /   \ 
        //     P=R   U=R    =>     P=B   U=B
        //    / \                  / \                     
        //   ?   R*               ?   R*
        //  The black heights of both parent and uncle are unchanged
        //  and the black height of the grandparent is unchanged
        if(uncle != nullptr && uncle->get_colour() == red) {
            parent->set_black();
            uncle->set_black();
            grandparent->set_red();
            addFixup(grandparent);
            return;
        }
        //  If the uncle is black, we need to rotate

        //  There are four cases 
        //  Case 1: parent is left child of grandparent and node is left child of parent
        //       G=B                 P=B
        //      /   \               /   \ 
        //     P=R   U=B    =>     R*   G=R
        //    /   \                     /  \ 
        //   R*    C                  C    U=B

        //  The black height of the parent is unchanged
        //  The black height of the grandparent is unchanged
        //  The black height of the uncle is unchanged
        //  The black height of the node is unchanged
        //  The black height of the node's sibling is unchanged

        if(parent == grandparent->get_left() && node == parent->get_left()) {
            parent->set_black();
            grandparent->set_red();
            rotateRight(parent,grandparent);
            return;
        }

        //  Case 2: parent is left child of grandparent and node is right child of parent
        //       G=B                 G=B
        //      /   \               /   \ 
        //     P=R   U=B    =>     N    U=B
        //    /   \               /  \ 
        //   S     N=R                P
        //                        
        //                         
        if(parent == grandparent->get_left() && node == parent->get_right()) {
            rotateLeft(node,parent);
            addFixup(parent);
            return;
        }
        // case 3: parent is right child of grandparent and node is left child of parent
        //       G=B                 G=B
        //      /   \               /   \ 
        //     U=B   P=R    =>     U=B   N
        //          /   \               /  \ 
        //         N     S             P    S
        if(parent == grandparent->get_right() && node == parent->get_left()) {
            //dump();
            rotateRight(node,parent);
            //dump();
            addFixup(parent);
            //dump();
            return;
        }

        // case 4: parent is right child of grandparent and node is right child of parent
        //       G=B                 P=B
        //      /   \               /   \ 
        //     U=B   P=R    =>     G=R   N*
        //          /   \         /  \ 
        //         C     N*      U=B   C
        if(parent == grandparent->get_right() && node == parent->get_right()) {
            //std::cout << "case 4" << std::endl;
            parent->set_black();
            grandparent->set_red();
            rotateLeft(parent,grandparent);
            //addFixup(parent);
            return;
        }

    }
    // Swap the child of a parent from A to B
    // If parent is null, then A is the root    
    void swapChild(rbnode* parent, rbnode* A, rbnode* B) {
        if( parent == nullptr) {
            root = B;
        } 
        else if(parent->get_left() == A) {
            parent->set_left(B);
        } else if  (parent->get_right() == A) {
            parent->set_right(B);
        }
    }


        //  Rotate right
        //          A                    A
        //         /                   /
        //        G                   P
        //      /   \               /   \ 
        //     P     U    =>       N     G
        //    /  \                      /  \ 
        //   N    S                    S    U
    void rotateRight(rbnode *parent, rbnode* grandparent) {
        rbnode* ancestor = grandparent->get_parent();

        rbnode* node = parent->get_left();
        rbnode* sibling = parent->get_right();
        parent->set_right(grandparent);
        grandparent->set_left(sibling);

        swapChild(ancestor,grandparent,parent);
        parent->set_parent(ancestor);
        grandparent->set_parent(parent);

        if(sibling != nullptr) {
            sibling->set_parent(grandparent);
        }
    }

    //  Case 2: parent is left child of grandparent and node is right child of parent
    //       A                A
    //      /                / 
    //     G     =>          P
    //    /  \             /  \ 
    //   U    P          G     S
    //       / \        /  \    
    //      N   S      U    N
    void rotateLeft(rbnode *parent, rbnode* grandparent) {
        rbnode* ancestor = grandparent->get_parent();

        rbnode* sibling = parent->get_left();
        parent->set_left(grandparent);
        grandparent->set_right(sibling);
        
        swapChild(ancestor,grandparent,parent);
        parent->set_parent(ancestor);
        grandparent->set_parent(parent);
        if(sibling != nullptr) {
            sibling->set_parent(grandparent);
        }
    }
};