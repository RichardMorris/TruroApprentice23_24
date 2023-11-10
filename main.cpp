#include <iostream>
#include <string>
#include <vector>
#include "weighted_graph.h"
using namespace std;

void assert_dist(int expected, int actual) {
  if (expected != actual) {
    cout << "Error expected " << expected << " was " << actual << endl;
  }
}
int main() {
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
  g.print();    

  int dist;
  dist = g.dijkstra(&C, &C);
  assert_dist(0, dist);
  dist = g.dijkstra(&R, &R);
  assert_dist(0, dist);
  dist = g.dijkstra(&T, &T);
  assert_dist(0, dist);
  dist = g.dijkstra(&F, &F);
  assert_dist(0, dist);
  dist = g.dijkstra(&A, &A);
  assert_dist(0, dist);

  dist = g.dijkstra(&C, &R);
  assert_dist(5, dist);

  assert_dist(5, g.dijkstra(&R, &T));
  assert_dist(30, g.dijkstra(&R, &A));
  assert_dist(5, g.dijkstra(&R, &F));
  assert_dist(18, g.dijkstra(&R, &T));
  
  assert_dist(5, g.dijkstra(&C, &R));
  assert_dist(15, g.dijkstra(&C, &T));
  assert_dist(23, g.dijkstra(&C, &F));
  assert_dist(35, g.dijkstra(&C, &A));

  assert_dist(15, g.dijkstra(&T, &C));
  assert_dist(10, g.dijkstra(&T, &R));
  assert_dist(8, g.dijkstra(&T, &F));
  assert_dist(20, g.dijkstra(&T, &A));

  assert_dist(23, g.dijkstra(&F, &C));
  assert_dist(18, g.dijkstra(&F, &R));
  assert_dist(8, g.dijkstra(&F, &T));
  assert_dist(28, g.dijkstra(&F, &A));




  
}
