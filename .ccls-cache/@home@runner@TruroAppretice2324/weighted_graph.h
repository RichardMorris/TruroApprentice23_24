#include <map>
#include <string>
#include <vector>
#include <iostream>

class wnode {
public:
  std::map<wnode *, int> neighbors;
  std::string name;

  wnode(std::string n) : name{n} {}
  void add_link(wnode* n, int d) {
    neighbors[n] = d;
  }

  void print() {
    std::cout << name << '\t';
    for(auto ele : neighbors) {
      std::cout << ele.first->name << ": " << ele.second << ", ";
    }
    std::cout << std::endl;
  }
};

class graph {
public:
  std::vector<wnode *> nodes;
  void add_node(wnode *n) {
    nodes.push_back(n);
  }
  void add_edge(wnode* n1,wnode *n2, int d) {
    n1->add_link(n2,d);
    n2->add_link(n1,d);
  }

  void print() {
    for(auto ele: nodes) {
      ele->print();
    }
  }

  // just a deleration
  int dijkstra(wnode *start, wnode *end); 
};