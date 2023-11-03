#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Node {
  string data;
  std::vector<Node> links;

public:
  // pass by value, makes our own local copy
  Node(string val) : data{val} {}
  // pass the argunemt by reference
  void addLink(const Node &n) { links.push_back(n); }
  int valency() { return links.size(); }

  friend ostream &operator<<(ostream &os, const Node &n);
};

// A fuction called "operator <<"
// that takes an ostream and a node
// and returns a ostrean
ostream &operator<<(ostream &os, const Node &n) {
  os << "Node(" << n.data << ") is friend with ";
  for (auto ele : n.links) {
    os << ele.data << " ";
  }
  os << endl;
  return os;
}

void print_value_from_pointer(Node *p) {
  cout << "address" << p << "Value" << (*p) << endl;
}
void print_value_from_reference(Node &n) {
  cout << "address" << &n << "Value" << n << endl;
}

int main1() {
  Node n1("Alice");
  Node n2("Bob");
  Node n3("Carol");
  Node n4("Dave");
  Node n5("Eric");
  n1.addLink(n2); // Alice is friend with Bob
  n2.addLink(n1);
  n1.addLink(n3); // Alice is friend with Carol
  n3.addLink(n2);
  n1.addLink(n4); // Alice is friend with Dave
  n4.addLink(n1);
  n3.addLink(n4); // Carol is friend with Dave
  n4.addLink(n3);
  n2.addLink(n5); // Bob is friend with Eric
  n5.addLink(n2);
  n4.addLink(n5); // Dave is friend with Eric
  n5.addLink(n4);

  cout << n1 << endl;
  cout << n2 << endl;
  cout << n3 << endl;
  cout << n4 << endl;
  cout << n5 << endl;
  /*
    Node *p1 = &n1;
    print_value_from_pointer(&n1);
    print_value_from_reference(n1);

    std::cout << n1.valency() << std::endl;
    std::cout << n2.valency() << std::endl;
    */
}