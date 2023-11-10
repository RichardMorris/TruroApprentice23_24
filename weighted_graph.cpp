#include "weighted_graph.h"
#include <iostream>
#include <cassert>
// uncomment to disable assert()
// #define NDEBUG

// implementation
int graph::dijkstra(wnode *start, wnode *end) {
  std::map<wnode *, int> dist;
  std::map<wnode *, wnode *> prev;
  
  
  if( dist[start] != 0) {
    std::cout << "error\n";
  }
  if(prev[start] != nullptr) {
    std::cout << "error\n";
  }
  for(auto n : nodes) {
    assert(dist[n] == 0);
    assert(prev[n] == nullptr);
  }
}
  return 0;
}