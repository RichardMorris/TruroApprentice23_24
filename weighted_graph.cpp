#include "weighted_graph.h"
#include <iostream>
#include <cassert>
#include <limits>
#include <set>
const int infinity = std::numeric_limits<int>::max();
// uncomment to disable assert()
// #define NDEBUG

// implementation
int graph::dijkstra(wnode *start, wnode *end) {
  std::map<wnode *, int> dist;
  std::map<wnode *, wnode *> prev;  
  
  for(auto n : nodes) {
    assert(prev[n] == nullptr);
  }
  std::set<wnode *> Q;
  for (auto n : nodes) {
    dist[n] = infinity;
    Q.insert(n);
 }
  assert(!Q.empty());
  dist[start] = 0;

  while(!Q.empty()) {
    // find u in Q with smallest distance
    wnode* u;
    int smallest = infinity;
    for(auto n : Q) {
      if(dist[n] < smallest) {
        u = n;
        smallest = dist[u];
      }
    }
    Q.erase(u);   // remove u from Q
    // for each neighour of u still in Q
    for(auto pair: u->neighbors) {
      wnode *v = pair.first;
      int edge_len = pair.second;
      if(Q.contains(v)) { // v is now a neighbour of u in Q
//      std::cout << v << "\t" << edge_len << std::endl;
        int alt = dist[u] + edge_len;
        if( alt < dist[v]) { // if dist via u is smaller than current, update
          dist[v] = alt;
          prev[v] = u;
        }
      }
    }

  }
  return dist[end];
}