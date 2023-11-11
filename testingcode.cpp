#include "weighted_graph.h"
using namespace std;
#include <catch2/catch_test_macros.hpp>

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