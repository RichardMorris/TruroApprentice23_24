
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
    R.insert(5);
    REQUIRE(R.get_val() == 7);
    REQUIRE(R.get_left() != nullptr);
    REQUIRE(R.get_right() == nullptr);
    REQUIRE(R.get_left()->get_val() == 5);

}

TEST_CASE("Insert equal val into rbnode is on left")
{
    rbnode R(7);
    R.insert(7);
    REQUIRE(R.get_val() == 7);
    REQUIRE(R.get_left() != nullptr);
    REQUIRE(R.get_right() == nullptr);
    REQUIRE(R.get_left()->get_val() == 7);
}

TEST_CASE("Insert higher val into rbnode is on right")
{
    rbnode R(7);
    R.insert(11);
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

TEST_CASE("Insert root into tree")
{
    rbtree tree;
    tree.insert(1);
}

TEST_CASE("Tree with 1 ele has 1 val")
{
    rbtree tree;
    tree.insert(7);
    vector<int> vals = tree.get_vals();
    REQUIRE(vals[0] == 7);
    REQUIRE(vals.size() == 1);
}

TEST_CASE("Insert 2 in order eles into tree")
{
    rbtree tree;
    tree.insert(5);
    tree.insert(7);
}

TEST_CASE("Insert 2 out of order eles into tree")
{
    rbtree tree;
    tree.insert(7);
    tree.insert(5);
}

TEST_CASE("Tree with 2 in order ele has vals in order")
{
    rbtree tree;
    tree.insert(5);
    tree.insert(7);
    vector<int> vals = tree.get_vals();
    REQUIRE(vals.size() == 2);
    REQUIRE(vals[0] == 5);
    REQUIRE(vals[1] == 7);
}

TEST_CASE("Tree with 2 out of order ele has vals in order")
{
    rbtree tree;
    tree.insert(7);
    tree.insert(5);
    vector<int> vals = tree.get_vals();
    REQUIRE(vals.size() == 2);
    REQUIRE(vals[0] == 5);
    REQUIRE(vals[1] == 7);
}

TEST_CASE("Insert 3 eles into tree")
{
    rbtree tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
}

TEST_CASE("Tree with 3 eles has vals in order")
{
    rbtree tree;
    tree.insert(5);
    tree.insert(7);
    tree.insert(11);
    vector<int> vals = tree.get_vals();
    // require vector has elements 5, 7, 11
    REQUIRE(vals.size() == 3);
    REQUIRE(vals[0] == 5);
    REQUIRE(vals[1] == 7);
    REQUIRE(vals[2] == 11);
}