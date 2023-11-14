#include "weighted_graph.h"
using namespace std;
#include <catch2/catch_all.hpp>
#include <algorithm>    // std::fill
#include <vector>       // std::vector

TEST_CASE("Build graph")
{
    wnode R("Redruth");
    wnode C("Camborne");
    wnode F("Falmouth");
    wnode T("Truro");
  wnode A("St Austell");
  graph g;

  g.add_node(&R);
  g.add_node(&C);
  g.add_node(&F);
  g.add_node(&T);
  g.add_node(&F);

  g.add_edge(&R,&C,5);
  g.add_edge(&R,&T,10);
  g.add_edge(&R,&A,40);
  g.add_edge(&T,&A,20);
  g.add_edge(&T,&F,8);
  
  int dist;
  dist = g.dijkstra(&C, &C);
  REQUIRE( 0 == dist);
  dist = g.dijkstra(&R, &R);
  REQUIRE(0 == dist);
  dist = g.dijkstra(&T, &T);
  REQUIRE(0 == dist);
  dist = g.dijkstra(&F, &F);
  REQUIRE(0 == dist);
  dist = g.dijkstra(&A, &A);
  REQUIRE(0 == dist);
}

TEST_CASE("Collection times") {
    const int size = 10000; // Size of the vector
    const int lower_bound = 1; // Lower bound of the random numbers
    const int upper_bound = 100000; // Upper bound of the random numbers

    // Seed for the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Generate a vector of unique random numbers
    std::vector<int> randomNumbers;
    randomNumbers.reserve(size);

    std::uniform_int_distribution<int> distribution(lower_bound, upper_bound);

    BENCHMARK("Build random vector") {
    while (randomNumbers.size() < size) {
        int randomNum = distribution(gen);
        if (std::find(randomNumbers.begin(), randomNumbers.end(), randomNum) == randomNumbers.end()) {
            randomNumbers.push_back(randomNum);
        }
    }
    };


}

