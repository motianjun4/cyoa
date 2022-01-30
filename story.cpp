
#include "cyoa.h"
#include <queue>

// constructor, read files in dir
Story::Story(const char * dirname) : pagelist(), winnable(false) {
  int fileIdx = 1;
  ostringstream ss;
  string filename;
  while (true) {
    ss.str("");
    ss << dirname << "/page" << fileIdx << ".txt";
    filename = ss.str();
    try {
      Page page(filename.c_str());
      pagelist.push_back(page);
    }
    catch (...) {
      break;
    }
    fileIdx++;
  }
  verify();
  setDepth(pagelist[0]);
}

// print the story
void Story::print() const {
  cout << "Story: pages:" << pagelist.size() << endl;
}

// get page by pageNum
Page & Story::getPage(size_t pageNum) {
  myassert(pageNum <= pagelist.size() && pageNum > 0, "page num not exist");
  return pagelist[pageNum - 1];
}

// start to play the story
void Story::play() {
  int pageNum = 1;
  while (true) {
    Page & page = getPage(pageNum);
    page.print();
    if (page.navigation_type == Page::WIN || page.navigation_type == Page::LOSE) {
      return;
    }
    size_t selection = 0;

    cin >> selection;
    while (!cin.good() || selection <= 0 || selection > page.options.size()) {
      myassert(!cin.eof(), "input EOF");
      cout << "That is not a valid choice, please try again\n";
      string none;
      if (!cin.good()) {
        cin.clear();
        cin >> none;
      }
      cin >> selection;
    }
    pageNum = page.options[selection - 1].to_page;
  }
}

// print the depth of each page
void Story::printDepth() {
  for (size_t i = 0; i < pagelist.size(); i++) {
    Page & page = pagelist[i];
    if (page.depth != -1) {
      cout << "Page " << page.pageNum << ":" << page.depth << endl;
    }
    else {
      cout << "Page " << page.pageNum << " is not reachable\n";
    }
  }
}

// find the path to win
void Story::findPathToWin() {
  Path path;
  dfsFindPath(pagelist[0], path);
  if (!winnable) {
    cout << "This story is unwinnable!\n";
  }
}

// get all related pages' pointer
vector<Page *> Story::getToPages(size_t pageNum) {
  vector<int> toPageNums = getPage(pageNum).getToPageNums();
  vector<Page *> toPages;
  for (size_t i = 0; i < toPageNums.size(); i++) {
    toPages.push_back(&getPage(toPageNums[i]));
  }
  return toPages;
}

// use BFS to set depth of pages
void Story::setDepth(Page & startingPage) {
  queue<Page *> q;
  startingPage.depth = 0;
  q.push(&startingPage);
  while(!q.empty()){
    Page & page = *q.front();
    q.pop();
    vector<Page*> pages = getToPages(page.pageNum);
    for(size_t i=0;i<pages.size(); ++i){
    // if already visited
    if(pages[i]->depth != -1){
        continue;
    }
    pages[i]->depth = page.depth + 1;
    q.push(pages[i]);
    }
  }
}

// use DFS to find the winning path
void Story::dfsFindPath(Page & page, Path & path) {
  if (page.visited) {
    return;
  }
  if (page.navigation_type == Page::WIN) {
    path.push(page.pageNum, -1);
    page.visited = true;
    path.print();
    winnable = true;
    path.pop();
    page.visited = false;
  }
  else if (page.navigation_type == Page::LOSE) {
    return;
  }
  else {
    page.visited = true;
    vector<Page *> pages = getToPages(page.pageNum);
    for (size_t i = 0; i < pages.size(); i++) {
      path.push(page.pageNum, i + 1);
      dfsFindPath(*pages[i], path);
      path.pop();
    }
    page.visited = false;
  }
}

// set the relative page reachable
void Story::verifyOptions(Page & page) {
  vector<Page *> toPages = getToPages(page.pageNum);
  for (size_t i = 0; i < toPages.size(); i++) {
    if (toPages[i] == &page) {
      continue;
    }
    toPages[i]->isReachable = true;
  }
}

// verify whether the story is valid
void Story::verify() {
  vector<Page>::iterator it = pagelist.begin();
  bool hasWin = false;
  bool hasLose = false;
  while (it != pagelist.end()) {
    verifyOptions(*it);
    if (it->navigation_type == Page::WIN) {
      hasWin = true;
    }
    if (it->navigation_type == Page::LOSE) {
      hasLose = true;
    }
    ++it;
  }
  myassert(pagelist.size() > 1, "no page");
  pagelist[0].isReachable = true;
  it = pagelist.begin();
  while (it != pagelist.end()) {
    myassert(it->isReachable, "Unreachble page");
    ++it;
  }
  myassert(hasWin, "No win page");
  myassert(hasLose, "No lose page");
}
