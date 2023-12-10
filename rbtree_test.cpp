
#include <catch2/catch_all.hpp>
#include "rbtree.h"
#include<vector>
using std::vector;

// CMake test driver
#define CATCH_CONFIG_MAIN

TEST_CASE("Build a bnode")
{
    rbnode R(1);
}

TEST_CASE("RBnode has val")
{
    rbnode R(7);
    REQUIRE(R.get_val() == 7);
}

TEST_CASE("RBnode has no left or right")
{
    rbnode R(7);
    REQUIRE(R.get_left() == nullptr);
    REQUIRE(R.get_right() == nullptr);
}

TEST_CASE("Insert lower val into rbnode")
{
    rbnode R(7);
    R.insert_raw(5);
    REQUIRE(R.get_val() == 7);
    REQUIRE(R.get_left() != nullptr);
    REQUIRE(R.get_right() == nullptr);
    REQUIRE(R.get_left()->get_val() == 5);

}

TEST_CASE("Insert equal val into rbnode is on left")
{
    rbnode R(7);
    R.insert_raw(7);
    REQUIRE(R.get_val() == 7);
    REQUIRE(R.get_left() != nullptr);
    REQUIRE(R.get_right() == nullptr);
    REQUIRE(R.get_left()->get_val() == 7);
}

TEST_CASE("Insert higher val into rbnode is on right")
{
    rbnode R(7);
    R.insert_raw(11);
    REQUIRE(R.get_val() == 7);
    REQUIRE(R.get_left() == nullptr);
    REQUIRE(R.get_right() != nullptr);
    REQUIRE(R.get_right()->get_val() == 11);
}

TEST_CASE("RBNodes default colour is red")
{
    rbnode R(7);
    REQUIRE(R.get_colour() == red);
}

TEST_CASE("RBNodes colour can be set to black")
{
    rbnode R(7);
    R.set_black();
    REQUIRE(R.get_colour() == black);
}

TEST_CASE("RBNodes colour can be reset to red")
{
    rbnode R(7);
    R.set_black();
    R.set_red();
    REQUIRE(R.get_colour() == red);
}

TEST_CASE( "Single RBnode is a leaf") {
    rbnode R(7);
    REQUIRE(R.is_leaf());
}

TEST_CASE( "RBnode with left child is not a leaf") {
    rbnode R(7);
    R.insert_raw(5);
    REQUIRE(!R.is_leaf());
}

TEST_CASE( "RBnode with right child is not a leaf") {
    rbnode R(7);
    R.insert_raw(11);
    REQUIRE(!R.is_leaf());
}

TEST_CASE( "RBnode with left and right child is not a leaf") {
    rbnode R(7);
    R.insert_raw(5);
    R.insert_raw(11);
    REQUIRE(!R.is_leaf());
}

TEST_CASE("RBnode with no children and default, red, colour has max_black_depth 0")
{
    rbnode R(7);
    REQUIRE(R.get_max_black_depth() == 0);
}

TEST_CASE("RBnode with no children and  default, red, colour has min_black_depth 0")
{
    rbnode R(7);
    REQUIRE(R.get_min_black_depth() == 0);
}

TEST_CASE("RBnode with no children and black colour has minn_black_depth 1")
{
    rbnode R(7);
    R.set_black();
    REQUIRE(R.get_min_black_depth() == 1);
}

TEST_CASE("RBnode with no children and black colour has max_black_depth 1")
{
    rbnode R(7);
    R.set_black();
    REQUIRE(R.get_max_black_depth() == 1);
}

TEST_CASE("Build a tree")
{
    rbtree tree;
}

TEST_CASE("Tree with no elements has no vals")
{
    rbtree tree;
    vector<int> vals = tree.get_vals();
    REQUIRE(vals.size() == 0);
}

TEST_CASE("Tree with 0 elements has min_black_depth 0")
{
    rbtree tree;
    REQUIRE(tree.get_min_black_depth() == 0);
}

TEST_CASE("Tree with 0 elements has max_black_depth 0")
{
    rbtree tree;
    REQUIRE(tree.get_max_black_depth() == 0);
}

TEST_CASE("Tree with 0 eles has no root")
{
    rbtree tree;
    REQUIRE(tree.get_root() == nullptr);
}

TEST_CASE("Tree with 0 else passes black depth test")
{
    rbtree tree;
    REQUIRE(tree.black_depth_test());
}

TEST_CASE("Tree with 0 else passes no adjacent red test")
{
    rbtree tree;
    REQUIRE(tree.no_adjacent_red_test());
}

TEST_CASE("Insert root into tree")
{
    rbtree tree;
    tree.insert_raw(1);
}

TEST_CASE("Tree with 1 ele has 1 val")
{
    rbtree tree;
    tree.insert_raw(7);
    vector<int> vals = tree.get_vals();
    REQUIRE(vals[0] == 7);
    REQUIRE(vals.size() == 1);
}

TEST_CASE("Tree with 1 ele has a root element which is black")
{
    rbtree tree;
    tree.insert_raw(7);
    REQUIRE(tree.get_root() != nullptr);
    rbnode* root = tree.get_root();
    REQUIRE(root->get_val() == 7);
    REQUIRE(root->get_left() == nullptr);
    REQUIRE(root->get_right() == nullptr);
    REQUIRE(root->get_colour() == black);

}
TEST_CASE("Tree with 1 elements has min_black_depth 1")
{
    rbtree tree;
    tree.insert_raw(7);
    REQUIRE(tree.get_min_black_depth() == 1);
}

TEST_CASE("Tree with 1 elements has max_black_depth 1")
{
    rbtree tree;
    tree.insert_raw(7);
    REQUIRE(tree.get_max_black_depth() == 1);
}

TEST_CASE("Tree with 1 else passes black depth test")
{
    rbtree tree;
    tree.insert_raw(7);
    REQUIRE(tree.black_depth_test());
}

TEST_CASE("Tree with 1 else passes no adjacent red test")
{
    rbtree tree;
    tree.insert_raw(7);
    REQUIRE(tree.no_adjacent_red_test());
}

TEST_CASE("Parent of tree with 1 ele is nullptr")
{
    rbtree tree;
    tree.insert_raw(7);
    REQUIRE(tree.get_root()->get_parent() == nullptr);
}

TEST_CASE("Insert 2 in order eles into tree")
{
    rbtree tree;
    tree.insert_raw(5);
    tree.insert_raw(7);
}

TEST_CASE("Insert 2 out of order eles into tree")
{
    rbtree tree;
    tree.insert_raw(7);
    tree.insert_raw(5);
}

TEST_CASE("Tree with 2 in order ele has vals in order")
{
    rbtree tree;
    tree.insert_raw(5);
    tree.insert_raw(7);
    vector<int> vals = tree.get_vals();
    REQUIRE(vals.size() == 2);
    REQUIRE(vals[0] == 5);
    REQUIRE(vals[1] == 7);
}

TEST_CASE("Tree with 2 out of order ele has vals in order")
{
    rbtree tree;
    tree.insert_raw(7);
    tree.insert_raw(5);
    vector<int> vals = tree.get_vals();
    REQUIRE(vals.size() == 2);
    REQUIRE(vals[0] == 5);
    REQUIRE(vals[1] == 7);
}

TEST_CASE("Tree with 2 eles has min_black_depth 1")
{
    rbtree tree;
    tree.insert_raw(5);
    tree.insert_raw(7);
    REQUIRE(tree.get_min_black_depth() == 1);
}

TEST_CASE("Tree with 2 eles has max_black_depth 1")
{
    rbtree tree;
    tree.insert_raw(5);
    tree.insert_raw(7);
    REQUIRE(tree.get_max_black_depth() == 1);
}

TEST_CASE("Tree with 2 eles reversed has min_black_depth 1")
{
    rbtree tree;
    tree.insert_raw(7);
    tree.insert_raw(5);
    REQUIRE(tree.get_min_black_depth() == 1);
}

TEST_CASE("Tree with 2 eles reversed has max_black_depth 1")
{
    rbtree tree;
    tree.insert_raw(7);
    tree.insert_raw(5);
    REQUIRE(tree.get_max_black_depth() == 1);
}

TEST_CASE("Tree with 2 eles passes black depth test")
{
    rbtree tree;
    tree.insert_raw(5);
    tree.insert_raw(7);
    REQUIRE(tree.black_depth_test());
}

TEST_CASE("Tree with 2 eles has black-red colours")
{
    rbtree tree;
    tree.insert_raw(5);
    tree.insert_raw(7);
    REQUIRE(tree.get_root()->get_colour() == black);
    REQUIRE(tree.get_root()->get_right()->get_colour() == red);
}

TEST_CASE("Tree with 2 eles reversed has black-red colours")
{
    rbtree tree;
    tree.insert_raw(7);
    tree.insert_raw(5);
    REQUIRE(tree.get_root()->get_colour() == black);
    REQUIRE(tree.get_root()->get_left()->get_colour() == red);
}

TEST_CASE("Tree with 2 eles passes no adjacent red test")
{
    rbtree tree;
    tree.insert_raw(5);
    tree.insert_raw(7);
    REQUIRE(tree.no_adjacent_red_test());
}

TEST_CASE("Three with 2 ele has parent of right child as root and parent of root as nullptr")
{
    rbtree tree;
    tree.insert_raw(5);
    tree.insert_raw(7);
    REQUIRE(tree.get_root()->get_right()->get_parent() == tree.get_root());
    REQUIRE(tree.get_root()->get_parent() == nullptr);    
}

TEST_CASE("Insert 3 eles into tree")
{
    rbtree tree;
    tree.insert_raw(1);
    tree.insert_raw(2);
    tree.insert_raw(3);
}

TEST_CASE("Tree with all possible combinations of 3 eles 5,7,11 has vals in order")
{
    int vals[6][3] = {
        {5,7,11},
        {5,11,7},
        {7,5,11},
        {7,11,5},
        {11,5,7},
        {11,7,5}
    };

    for(int i=0; i<6; i++) {
        rbtree tree;
        tree.insert_raw(vals[i][0]);
        tree.insert_raw(vals[i][1]);
        tree.insert_raw(vals[i][2]);
        vector<int> res = tree.get_vals();
        // require vector has elements 5, 7, 11
        REQUIRE(res.size() == 3);
        REQUIRE(res[0] == 5);
        REQUIRE(res[1] == 7);
        REQUIRE(res[2] == 11);
    }
}

TEST_CASE("Tree with 3 eles 5,7,11 is right leaning with colours black, red, red and fails red test")
{
    rbtree tree;
    tree.insert_raw(5);
    tree.insert_raw(7);
    tree.insert_raw(11);
    rbnode* root = tree.get_root();
    REQUIRE(tree.get_root()->get_val() == 5);
    REQUIRE(tree.get_root()->get_right()->get_val() == 7 );
    REQUIRE(tree.get_root()->get_right()->get_right()->get_val() == 11);
    REQUIRE(root->get_colour() == black);
    REQUIRE(root->get_right()->get_colour() == red);
    REQUIRE(root->get_right()->get_right()->get_colour() == red);
    REQUIRE_FALSE(tree.no_adjacent_red_test());
}

TEST_CASE("Tree with 3 eles 5,11,7 is R L colours black, red, red and fails red test")
{
    rbtree tree;
    tree.insert_raw(5);
    tree.insert_raw(11);
    tree.insert_raw(7);
    rbnode* root = tree.get_root();
    REQUIRE(tree.get_root()->get_val() == 5);
    REQUIRE(tree.get_root()->get_right()->get_val() == 11 );
    REQUIRE(tree.get_root()->get_right()->get_left()->get_val() == 7);
    REQUIRE(root->get_colour() == black);
    REQUIRE(root->get_right()->get_colour() == red);
    REQUIRE(root->get_right()->get_left()->get_colour() == red);
    REQUIRE_FALSE(tree.no_adjacent_red_test());
}

TEST_CASE("Tree with 3 eles 7,5,11 is balanced with colours black, red, red and passes red test")
{
    rbtree tree;
    tree.insert_raw(7);
    tree.insert_raw(5);
    tree.insert_raw(11);
    rbnode* root = tree.get_root();
    REQUIRE(tree.get_root()->get_val() == 7);
    REQUIRE(tree.get_root()->get_left()->get_val() == 5 );
    REQUIRE(tree.get_root()->get_right()->get_val() == 11);
    REQUIRE(root->get_colour() == black);
    REQUIRE(root->get_left()->get_colour() == red);
    REQUIRE(root->get_right()->get_colour() == red);
    REQUIRE(tree.no_adjacent_red_test());
}

TEST_CASE("Tree with 3 eles 7,11,5 is balanced with colours black, red, red and passes red test")
{
    rbtree tree;
    tree.insert_raw(7);
    tree.insert_raw(11);
    tree.insert_raw(5);
    rbnode* root = tree.get_root();
    REQUIRE(tree.get_root()->get_val() == 7);
    REQUIRE(tree.get_root()->get_left()->get_val() == 5 );
    REQUIRE(tree.get_root()->get_right()->get_val() == 11);
    REQUIRE(root->get_colour() == black);
    REQUIRE(root->get_left()->get_colour() == red);
    REQUIRE(root->get_right()->get_colour() == red);
    REQUIRE(tree.no_adjacent_red_test());
}


TEST_CASE("Tree with 3 eles 11,5,7 is left-right with colours black, red, red and fails red test")
{
    rbtree tree;
    tree.insert_raw(11);
    tree.insert_raw(5);
    tree.insert_raw(7);
    rbnode* root = tree.get_root();
    REQUIRE(tree.get_root()->get_val() == 11);
    REQUIRE(tree.get_root()->get_left()->get_val() == 5 );
    REQUIRE(tree.get_root()->get_left()->get_right()->get_val() == 7);
    REQUIRE(root->get_colour() == black);
    REQUIRE(root->get_left()->get_colour() == red);
    REQUIRE(root->get_left()->get_right()->get_colour() == red);
    REQUIRE_FALSE(tree.no_adjacent_red_test());
}

TEST_CASE("Tree with 3 eles 11,7,5 is left-left with colours black, red, red and fails red test")
{
    rbtree tree;
    tree.insert_raw(11);
    tree.insert_raw(7);
    tree.insert_raw(5);
    rbnode* root = tree.get_root();
    REQUIRE(tree.get_root()->get_val() == 11);
    REQUIRE(tree.get_root()->get_left()->get_val() == 7 );
    REQUIRE(tree.get_root()->get_left()->get_left()->get_val() == 5);
    REQUIRE(root->get_colour() == black);
    REQUIRE(root->get_left()->get_colour() == red);
    REQUIRE(root->get_left()->get_left()->get_colour() == red);
    REQUIRE_FALSE(tree.no_adjacent_red_test());
}

TEST_CASE("Tree with all possible combinations of 3 eles 5,7,11 gives expected red test ")
{
    int vals[6][3] = {
        {5,7,11},
        {5,11,7},
        {7,5,11},
        {7,11,5},
        {11,5,7},
        {11,7,5}
    };
    bool expected[6] = {
        false,
        false,
        true,
        true,
        false,
        false
    };

    for(int i=0; i<6; i++) {
        rbtree tree;
        tree.insert_raw(vals[i][0]);
        tree.insert_raw(vals[i][1]);
        tree.insert_raw(vals[i][2]);
        vector<int> res = tree.get_vals();
        REQUIRE(tree.no_adjacent_red_test() == expected[i]);
    }
}

TEST_CASE("Tree with all possible combinations of 3 eles 5,7,11 passes black test")
{
    int vals[6][3] = {
        {5,7,11},
        {5,11,7},
        {7,5,11},
        {7,11,5},
        {11,5,7},
        {11,7,5}
    };

    for(int i=0; i<6; i++) {
        rbtree tree;
        tree.insert_raw(vals[i][0]);
        tree.insert_raw(vals[i][1]);
        tree.insert_raw(vals[i][2]);
        vector<int> res = tree.get_vals();
        REQUIRE(tree.black_depth_test());
    }
}


TEST_CASE("fixup on 3 ele LL tree") {
    rbtree tree;
    rbnode* gp = tree.insert_raw(11);
    rbnode *p = tree.insert_raw(7);
    rbnode* node = tree.insert_raw(5);

    REQUIRE(tree.get_root() == gp);
    REQUIRE(tree.get_root()->get_left() == p );
    REQUIRE(tree.get_root()->get_left()->get_left() == node);
    REQUIRE(gp->get_colour() == black);
    REQUIRE(p->get_colour() == red);
    REQUIRE(node->get_colour() == red);    
    REQUIRE_FALSE(tree.no_adjacent_red_test());
    tree.addFixup(node);
    REQUIRE(tree.get_root() == p);
    REQUIRE(tree.get_root()->get_left() == node );
    REQUIRE(tree.get_root()->get_right() == gp);
    REQUIRE(gp->get_colour() == red);
    REQUIRE(p->get_colour() == black);
    REQUIRE(node->get_colour() == red);    

    REQUIRE(tree.no_adjacent_red_test());
    REQUIRE(tree.black_depth_test());
}

TEST_CASE("fixup on 4 ele LLL tree") {
    rbtree tree;
    rbnode* a = tree.insert_raw(13);

    rbnode* gp = tree.insert_raw(11);
    gp->set_black();
    rbnode *p = tree.insert_raw(7);
    rbnode* node = tree.insert_raw(5);

    REQUIRE(tree.get_root() == a);
    REQUIRE(tree.get_root()->get_left() == gp );
    REQUIRE(tree.get_root()->get_left()->get_left() == p);
    REQUIRE(tree.get_root()->get_left()->get_left()->get_left() == node);
    REQUIRE(a->get_colour() == black);
    REQUIRE(gp->get_colour() == black);
    REQUIRE(p->get_colour() == red);
    REQUIRE(node->get_colour() == red);    
    REQUIRE_FALSE(tree.no_adjacent_red_test());

    tree.addFixup(node);
    REQUIRE(tree.get_root() == a);
    REQUIRE(a->get_left() == p );
    REQUIRE(p->get_right() == gp);
    REQUIRE(p->get_left() == node );
    REQUIRE( a->get_colour() == black);
    REQUIRE( p->get_colour() == black);
    REQUIRE( gp->get_colour() == red);
    REQUIRE( node->get_colour() == red);

    REQUIRE(tree.no_adjacent_red_test());
    //REQUIRE(tree.black_depth_test());
}

TEST_CASE("fixup on 4 ele RLL tree") {
    rbtree tree;
    rbnode* a = tree.insert_raw(3);
    rbnode* gp = tree.insert_raw(11);
    gp->set_black();
    rbnode *p = tree.insert_raw(7);
    rbnode* node = tree.insert_raw(5);

    REQUIRE(tree.get_root() == a);
    REQUIRE(a->get_right() == gp );
    REQUIRE(gp->get_left() == p);
    REQUIRE(p->get_left() == node);
    REQUIRE(a->get_colour() == black);
    REQUIRE(gp->get_colour() == black);
    REQUIRE(p->get_colour() == red);
    REQUIRE(node->get_colour() == red);    
    REQUIRE_FALSE(tree.no_adjacent_red_test());

    tree.addFixup(node);
    REQUIRE(tree.get_root() == a);
    REQUIRE(a->get_right() == p );
    REQUIRE(p->get_right() == gp);
    REQUIRE(p->get_left() == node );
    REQUIRE( a->get_colour() == black);
    REQUIRE( p->get_colour() == black);
    REQUIRE( gp->get_colour() == red);
    REQUIRE( node->get_colour() == red);

    REQUIRE(tree.no_adjacent_red_test());
}

TEST_CASE("fixup on 4 ele LL tree with sibling and uncle") {
    rbtree tree;
    rbnode* a = tree.insert_raw(13);
    rbnode* gp = tree.insert_raw(11);
    gp->set_black();
    rbnode *u = tree.insert_raw(12);
    u->set_black();
    rbnode *p = tree.insert_raw(7);
    rbnode* s = tree.insert_raw(8);
    rbnode* node = tree.insert_raw(5);

    REQUIRE(tree.get_root() == a);
    REQUIRE(a->get_left() == gp );
    REQUIRE(gp->get_left() == p);
    REQUIRE(gp->get_right() == u);
    REQUIRE(p->get_left() == node);
    REQUIRE(p->get_right() == s);
    
    REQUIRE(a->get_colour() == black);
    REQUIRE(gp->get_colour() == black);
    REQUIRE(p->get_colour() == red);
    REQUIRE(node->get_colour() == red);    
    REQUIRE_FALSE(tree.no_adjacent_red_test());

    tree.addFixup(node);
    REQUIRE(tree.get_root() == a);
    REQUIRE(a->get_left() == p );
    REQUIRE(p->get_right() == gp);
    REQUIRE(p->get_left() == node );
    REQUIRE(gp->get_right() == u);
    REQUIRE(gp->get_left() == s );

    REQUIRE( a->get_colour() == black);
    REQUIRE( p->get_colour() == black);
    REQUIRE( gp->get_colour() == red);
    REQUIRE( node->get_colour() == red);

    //REQUIRE(tree.no_adjacent_red_test());
}

TEST_CASE("fixup on right red uncle clase") {
    rbtree  tree;
    rbnode* a = tree.insert_raw(13);
    rbnode* gp = tree.insert_raw(11);
    gp->set_black();
    rbnode *u = tree.insert_raw(12);
    rbnode *p = tree.insert_raw(7);
    rbnode* node = tree.insert_raw(5);

    REQUIRE(tree.get_root() == a);
    REQUIRE(a->get_left() == gp );
    REQUIRE(gp->get_right() == u);
    REQUIRE(gp->get_left() == p);
    REQUIRE(p->get_left() == node );

    REQUIRE( a->get_colour() == black);
    REQUIRE( gp->get_colour() == black);
    REQUIRE( u->get_colour() == red);
    REQUIRE( p->get_colour() == red);
    REQUIRE( node->get_colour() == red);
    
    tree.addFixup(node);
    REQUIRE(tree.get_root() == a);
    REQUIRE(a->get_left() == gp );
    REQUIRE(gp->get_left() == p );
    REQUIRE(gp->get_right() == u);
    REQUIRE(p->get_left() == node);

    REQUIRE( a->get_colour() == black);
    REQUIRE( gp->get_colour() == red);
    REQUIRE( u->get_colour() == black);
    REQUIRE( p->get_colour() == black);
    REQUIRE( node->get_colour() == red);

}

TEST_CASE("fixup on left red uncle clase") {
    rbtree  tree;
    rbnode* a = tree.insert_raw(13);
    rbnode* gp = tree.insert_raw(7);
    gp->set_black();
    rbnode *u = tree.insert_raw(5);
    rbnode *p = tree.insert_raw(11);
    rbnode* node = tree.insert_raw(9);

    REQUIRE(tree.get_root() == a);
    REQUIRE(a->get_left() == gp );
    REQUIRE(gp->get_right() == p);
    REQUIRE(gp->get_left() == u);
    REQUIRE(p->get_left() == node );

    REQUIRE( a->get_colour() == black);
    REQUIRE( gp->get_colour() == black);
    REQUIRE( u->get_colour() == red);
    REQUIRE( p->get_colour() == red);
    REQUIRE( node->get_colour() == red);
    
    tree.addFixup(node);
    REQUIRE(tree.get_root() == a);
    REQUIRE(a->get_left() == gp );
    REQUIRE(gp->get_left() == u );
    REQUIRE(gp->get_right() == p);
    REQUIRE(p->get_left() == node);

    REQUIRE( a->get_colour() == black);
    REQUIRE( gp->get_colour() == red);
    REQUIRE( u->get_colour() == black);
    REQUIRE( p->get_colour() == black);
    REQUIRE( node->get_colour() == red);

}

TEST_CASE("fixup on left red uncle clase where gp is root") {
    rbtree  tree;
    rbnode* gp = tree.insert_raw(7);
    gp->set_black();
    rbnode *u = tree.insert_raw(5);
    rbnode *p = tree.insert_raw(11);
    rbnode* node = tree.insert_raw(9);

    REQUIRE(tree.get_root() == gp);
    REQUIRE(gp->get_right() == p);
    REQUIRE(gp->get_left() == u);
    REQUIRE(p->get_left() == node );

    REQUIRE( gp->get_colour() == black);
    REQUIRE( u->get_colour() == red);
    REQUIRE( p->get_colour() == red);
    REQUIRE( node->get_colour() == red);
    
    tree.addFixup(node);
    REQUIRE(tree.get_root() == gp);
    REQUIRE(gp->get_left() == u );
    REQUIRE(gp->get_right() == p);
    REQUIRE(p->get_left() == node);

    REQUIRE( gp->get_colour() == black);
    REQUIRE( u->get_colour() == black);
    REQUIRE( p->get_colour() == black);
    REQUIRE( node->get_colour() == red);

    REQUIRE(tree.no_adjacent_red_test());
    //REQUIRE(tree.black_depth_test());
}

        //  Rotate right
        //          A 13                   A 13
        //         /                      /
        //        G 11                   P 7
        //      /   \                   /   \ 
        //     P 7    U 12   =>       N 5    G 11
        //    /  \                         /  \ 
        //   N 5  S 9                     S 9  U 12
    //void rotateRight(rbnode *parent, rbnode* grandparent) {

TEST_CASE("RotateRight tree with ancestor") {
    rbtree tree;
    rbnode* a = tree.insert_raw(13);
    rbnode* gp = tree.insert_raw(11);
    rbnode* u = tree.insert_raw(12);
    rbnode *p = tree.insert_raw(7);
    rbnode* node = tree.insert_raw(5);
    rbnode* s = tree.insert_raw(9);

    REQUIRE(tree.get_root() == a);
    REQUIRE(a->get_left() == gp );
    REQUIRE(gp->get_parent() == a);
    REQUIRE(gp->get_right() == u);
    REQUIRE(u->get_parent() == gp);
    REQUIRE(gp->get_left() == p);
    REQUIRE(p->get_parent() == gp);
    REQUIRE(p->get_left() == node );
    REQUIRE(node->get_parent() == p);
    REQUIRE(p->get_right() == s );
    REQUIRE(s->get_parent() == p);
    tree.rotateRight(p, gp);

    REQUIRE(tree.get_root() == a);
    REQUIRE(a->get_left() == p );
    REQUIRE(p->get_parent() == a);

    REQUIRE(p->get_right() == gp);
    REQUIRE(gp->get_parent() == p);

    REQUIRE(p->get_left() == node );
    REQUIRE(node->get_parent() == p);

    REQUIRE(gp->get_left() == s );
    REQUIRE(s->get_parent() == gp);

    REQUIRE(gp->get_right() == u );
    REQUIRE(u->get_parent() == gp);
}

    //  Rotate left
    //          A 13                   A 13
    //         /                      /
    //        G 7                    P 11
    //      /   \                  /   \ 
    //    U 5    P 11      =>    G 7    N 12
    //          /  \            /  \ 
    //         S 9  N 12      U 5  S 9
    //void rotateLeft(rbnode *parent, rbnode* grandparent) 

TEST_CASE("RotateLeft tree with ancestor") {
    rbtree tree;
    rbnode* a = tree.insert_raw(13);
    rbnode* gp = tree.insert_raw(7);
    rbnode* u = tree.insert_raw(5);
    rbnode *p = tree.insert_raw(11);
    rbnode* s = tree.insert_raw(9);
    rbnode* node = tree.insert_raw(12);

    REQUIRE(tree.get_root() == a);
    REQUIRE(a->get_left() == gp );
    REQUIRE(gp->get_parent() == a);
    REQUIRE(gp->get_left() == u);
    REQUIRE(u->get_parent() == gp);
    REQUIRE(gp->get_right() == p);
    REQUIRE(p->get_parent() == gp);
    REQUIRE(p->get_left() == s );
    REQUIRE(s->get_parent() == p);
    REQUIRE(p->get_right() == node );
    REQUIRE(node->get_parent() == p);
    tree.rotateLeft(p, gp);
    REQUIRE(tree.get_root() == a);
    REQUIRE(a->get_left() == p );
    REQUIRE(p->get_parent() == a);
    REQUIRE(p->get_left() == gp);
    REQUIRE(gp->get_parent() == p);
    REQUIRE(p->get_right() == node );
    REQUIRE(node->get_parent() == p);
    REQUIRE(gp->get_left() == u );
    REQUIRE(u->get_parent() == gp);
    REQUIRE(gp->get_right() == s );
    REQUIRE(s->get_parent() == gp);
}

//  Fixup
//                G 9b                    N 8b
//            /        \                /       \ 
//           P 7r     U 11b      =>    P 7r    G 9r 
//          /   \                              /   \ 
//              N 8r                              U 11b
//                
TEST_CASE("fixup on left-right case where gp is root") {
    rbtree  tree;
    rbnode* gp = tree.insert_raw(9);
    rbnode *u = tree.insert_raw(11);
    u->set_black();
    rbnode *p = tree.insert_raw(7);
    rbnode *s = tree.insert_raw(5);
    s->set_black();

    rbnode* node = tree.insert_raw(8);

    REQUIRE(tree.get_root() == gp);
    REQUIRE(gp->get_left() == p);
    REQUIRE(gp->get_right() == u);
    REQUIRE(p->get_right() == node );
    REQUIRE(p->get_left() == s );

    REQUIRE( gp->get_colour() == black);
    REQUIRE( u->get_colour() == black);
    REQUIRE( p->get_colour() == red);
    REQUIRE( node->get_colour() == red);    
    tree.addFixup(node);
    REQUIRE(tree.get_root() == node);
    REQUIRE(node->get_left() == p );
    REQUIRE(node->get_right() == gp);
    REQUIRE(gp->get_right() == u);

    REQUIRE( gp->get_colour() == red);
    REQUIRE( u->get_colour() == black);
    REQUIRE( p->get_colour() == red);
    REQUIRE( node->get_colour() == black);

    REQUIRE(tree.no_adjacent_red_test());
    //REQUIRE(tree.black_depth_test());

}

TEST_CASE("fixup on left-right case where gp has ancestor") {
    rbtree  tree;
    rbnode* a = tree.insert_raw(13);
    rbnode* gp = tree.insert_raw(9);
    gp->set_black();
    rbnode *u = tree.insert_raw(11);
    u->set_black();
    rbnode *p = tree.insert_raw(7);
    rbnode* node = tree.insert_raw(8);

    REQUIRE(tree.get_root() == a);
    REQUIRE(a->get_left() == gp);
    REQUIRE(gp->get_left() == p);
    REQUIRE(gp->get_right() == u);
    REQUIRE(p->get_right() == node );

    REQUIRE( gp->get_colour() == black);
    REQUIRE( u->get_colour() == black);
    REQUIRE( p->get_colour() == red);
    REQUIRE( node->get_colour() == red);    
    tree.addFixup(node);
    REQUIRE(tree.get_root() == a);
    REQUIRE(a->get_left() == node);
    REQUIRE(node->get_left() == p );
    REQUIRE(node->get_right() == gp);
    REQUIRE(gp->get_right() == u);

    REQUIRE( gp->get_colour() == red);
    REQUIRE( u->get_colour() == black);
    REQUIRE( p->get_colour() == red);
    REQUIRE( node->get_colour() == black);

    REQUIRE(tree.no_adjacent_red_test());
    //REQUIRE(tree.black_depth_test());

}

TEST_CASE("fixup on right-left case where gp has ancestor","[.historic]") {
    rbtree  tree;
    rbnode* a = tree.insert_raw(13);
    rbnode* gp = tree.insert_raw(9);
    gp->set_black();
    rbnode *u = tree.insert_raw(7);
    u->set_black();
    rbnode *p = tree.insert_raw(11);
    rbnode *s = tree.insert_raw(12);
    rbnode* node = tree.insert_raw(10);

    REQUIRE(tree.get_root() == a);
    REQUIRE(a->get_left() == gp);
    REQUIRE(gp->get_left() == u);
    REQUIRE(gp->get_right() == p);
    REQUIRE(p->get_left() == node);
    REQUIRE(p->get_right() == s );

    REQUIRE( gp->get_colour() == black);
    REQUIRE( u->get_colour() == black);
    REQUIRE( p->get_colour() == red);
    REQUIRE( node->get_colour() == red);    
    tree.addFixup(node);
    REQUIRE(tree.get_root() == a);
    REQUIRE(a->get_left() == node);
    REQUIRE(node->get_left() == gp );
    REQUIRE(node->get_right() == p);
    REQUIRE(gp->get_left() == u);

    REQUIRE( gp->get_colour() == red);
    REQUIRE( u->get_colour() == black);
    REQUIRE( p->get_colour() == red);
    REQUIRE( node->get_colour() == black);

    //REQUIRE(tree.no_adjacent_red_test());
    //REQUIRE(tree.black_depth_test());

}

TEST_CASE("fixup on right-right case where gp has ancestor","[.historic]") {
    rbtree  tree;
    rbnode* a = tree.insert_raw(13);
    rbnode* gp = tree.insert_raw(9);
    gp->set_black();
    rbnode *u = tree.insert_raw(11);
    u->set_black();
    rbnode *p = tree.insert_raw(7);
    rbnode *s = tree.insert_raw(5);
    rbnode* node = tree.insert_raw(8);

    REQUIRE(tree.get_root() == a);
    REQUIRE(a->get_left() == gp);
    REQUIRE(gp->get_left() == p);
    REQUIRE(gp->get_right() == u);
    REQUIRE(p->get_left() == s);
    REQUIRE(p->get_right() == node );

    REQUIRE( gp->get_colour() == black);
    REQUIRE( u->get_colour() == black);
    REQUIRE( p->get_colour() == red);
    REQUIRE( node->get_colour() == red);    
    tree.addFixup(node);
    REQUIRE(tree.get_root() == a);
    REQUIRE(a->get_left() == node);
    REQUIRE(node->get_left() == p );
    REQUIRE(gp->get_right() == u);

    REQUIRE( gp->get_colour() == red);
    REQUIRE( u->get_colour() == black);
    REQUIRE( p->get_colour() == red);
    REQUIRE( node->get_colour() == black);

    //REQUIRE(tree.no_adjacent_red_test());
    //REQUIRE(tree.black_depth_test());
}

TEST_CASE("insert and fixup 13 9 11 7 5 8") {
    int vals[] ={13, 9, 11, 7, 5, 8};
    rbtree  tree;

    for(auto val:vals) {
        tree.insert(val);
        REQUIRE(tree.no_adjacent_red_test());
        REQUIRE(tree.black_depth_test());
    }
}

TEST_CASE("insert & fixup on 3 5 7 9") {
    rbtree  tree;
    rbnode* a = tree.insert(3);
    REQUIRE(tree.no_adjacent_red_test());
    REQUIRE(tree.black_depth_test());
    rbnode* b = tree.insert(5);
    REQUIRE(tree.no_adjacent_red_test());
    REQUIRE(tree.black_depth_test());
    rbnode* c = tree.insert(7);
    REQUIRE(tree.no_adjacent_red_test());
    REQUIRE(tree.black_depth_test());
    rbnode* d = tree.insert(9);
    REQUIRE(tree.no_adjacent_red_test());
    REQUIRE(tree.black_depth_test());

}

TEST_CASE("insert and fixup on 9 7 5 3")
{
    rbtree  tree;
    rbnode* a = tree.insert(9);
    REQUIRE(tree.no_adjacent_red_test());
    REQUIRE(tree.black_depth_test());
    rbnode* b = tree.insert(7);
    REQUIRE(tree.no_adjacent_red_test());
    REQUIRE(tree.black_depth_test());
    rbnode* c = tree.insert(5);
    REQUIRE(tree.no_adjacent_red_test());
    REQUIRE(tree.black_depth_test());
    rbnode* d = tree.insert(3);
    REQUIRE(tree.no_adjacent_red_test());
    REQUIRE(tree.black_depth_test());   
}