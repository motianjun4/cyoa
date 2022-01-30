#include "./cyoa.h"

void Path::push(int pageNum, int choiceNum) {
  nodes.push_back(Node(pageNum, choiceNum));
}

void Path::pop() {
  nodes.pop_back();
}

// print the node
void Path::Node::print() const {
  cout << pageNum << "(";
  if (choiceNum == -1) {
    cout << "win";
  }
  else {
    cout << choiceNum;
  }
  cout << ")";
}

// print the path
void Path::print() const {
  for (size_t i = 0; i < nodes.size(); i++) {
    if (i > 0) {
      cout << ",";
    }
    nodes[i].print();
  }
  cout << endl;
}
