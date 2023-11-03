#include <iostream>
#include <string>
#include <vector>
#include "weighted_graph.h"
using namespace std;

int main() {
  wnode n1("Redruth");
  wnode n2("Camborne");
  wnode n3("Falmouth");
  wnode n4("Truro");
  wnode n5("St Austell");
  graph g;

  g.add_node(&n1);
  g.add_node(&n2);
  g.add_node(&n3);
  g.add_node(&n4);
  g.add_node(&n5);

  g.add_edge(&n1,&n2,5);
  g.add_edge(&n1,&n4,10);
  g.add_edge(&n1,&n5,40);
  g.add_edge(&n4,&n5,20);
  g.add_edge(&n4,&n3,8);
  g.print();    
}