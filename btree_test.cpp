
#include <catch2/catch_all.hpp>
#include "btree.h"
#include<vector>
using std::vector;

// CMake test driver
#define CATCH_CONFIG_MAIN

TEST_CASE("Build bnode")
{
    bnode R(1);
}

TEST_CASE("Build tree")
{
    btree tree;

    // function returning a array of ints 

}

TEST_CASE("Insert root into tree")
{
    btree tree;
    tree.insert(1);
}

TEST_CASE("Retreive sorted list from tree")
{
    btree tree;
    tree.insert(1);
    vector<int> vals = tree.get_vals();
    REQUIRE(vals[0] == 1);
    REQUIRE(vals.size() == 1);

}
TEST_CASE("Insert 2 eles into tree")
{
    btree tree;
    tree.insert(1);
    tree.insert(2);
}

TEST_CASE("Insert 3 eles into tree")
{
    btree tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
}