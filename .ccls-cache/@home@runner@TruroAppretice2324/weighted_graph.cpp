#include <map>
#include <string>
#include <vector>

class wnode {
public:
  std::map<wnode *, int> neighbors;
  std::string name;

  wnode(std::string n) : name{n} {}
};

class graph {
public:
  std::vector<wnode *> nodes;
};
