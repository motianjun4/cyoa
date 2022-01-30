#ifndef CYOA_H
#define CYOA_H

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;
void myassert(bool expression, string msg);

// Page class
class Page {
 public:
  enum navi_t {
    UNKNOWN,
    WIN,
    LOSE,
    OPTION,
  };

  class Option {
   public:
    int to_page;
    string desc;
    Option(int t, string d) : to_page(t), desc(d){};
    Option() : to_page(0), desc(""){};
    void print() { cout << to_page << desc << "\n"; }
  };

 private:
  Option readOption(string line);
  void readNavigation(string line);

 public:
  int pageNum;
  vector<Option> options;
  string story;
  navi_t navigation_type;
  bool isReachable;
  int depth;
  bool visited;
  Page(const char * filename);
  void print() const;
  vector<int> getToPageNums() const;
};

// Path class

class Path {
 private:
  class Node {
   public:
    int pageNum;
    int choiceNum;
    Node() : pageNum(0), choiceNum(0){};
    Node(int p, int c) : pageNum(p), choiceNum(c){};
    void print() const;
  };
  vector<Node> nodes;

 public:
  void push(int pageNum, int choiceNum);
  void pop();
  void print() const;
};

// Story class
class Story {
 private:
  vector<Page> pagelist;  // 1-index
  bool winnable;
  vector<Page *> getToPages(size_t pageNum);
  void setDepth(Page & startingPage);
  void dfsFindPath(Page & page, Path & path);
  void verifyOptions(Page & page);
  void verify();

 public:
  Story() : pagelist(){};
  Story(const char * dirname);
  void print() const;
  Page & getPage(size_t pageNum);
  void play();
  void printDepth();
  void findPathToWin();
};

#endif
