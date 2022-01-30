#include "cyoa.h"

void myassert(bool expression, string msg) {
  if (!expression) {
    throw invalid_argument(msg);
  }
}

// read a page
Page::Page(const char * filename) :
    pageNum(),
    options(),
    story(),
    navigation_type(UNKNOWN),
    isReachable(false),
    depth(-1),
    visited(false) {
  // check the filename
  string path(filename);
  if (path[0] != '/') {
    // if path is a relative path,
    path = "./" + path;
  }

  // parse out the filename
  string filenameStr = path.substr(path.find_last_of("/") + 1);

  // check whether the filename is valid
  int numRead = 0;
  myassert(
      sscanf((filenameStr + "\n").c_str(), "page%d.txt\n%n", &pageNum, &numRead) == 1,
      "mal-formated filename, should be page*.txt");
  myassert(numRead == (int)filenameStr.length() + 1,
           "mal-formatted filename, should be page*.txt");

  ifstream f(filename);
  myassert(f.is_open(), "file not found");
  string line;
  bool is_navigation = true;
  while (getline(f, line)) {
    if (line.substr(0, 1) == "#") {
      myassert(is_navigation, "already have #");
      myassert(navigation_type != Page::UNKNOWN, "navigation type unknown");
      is_navigation = false;
      continue;
    }
    if (!is_navigation) {
      story += line + "\n";
    }
    else {
      readNavigation(line);
    }
  }
  myassert(!is_navigation, "# not found");
};

// read option
Page::Option Page::readOption(string line) {
  Option res;
  size_t a = line.find(":");
  res.to_page = atoi(line.substr(0, a).c_str());
  res.desc = line.substr(a + 1, line.npos);
  return res;
}

// read navigation part in a page
void Page::readNavigation(string line) {
  if (line == "WIN") {
    myassert(navigation_type == Page::UNKNOWN, "multiple navigation for WIN");
    navigation_type = Page::WIN;
  }
  else if (line == "LOSE") {
    myassert(navigation_type == Page::UNKNOWN, "multiple navigation for LOSE");
    navigation_type = Page::LOSE;
  }
  else {
    myassert(navigation_type == Page::UNKNOWN || navigation_type == Page::OPTION,
             "multiple navigation for OPTION ");
    options.push_back(readOption(line));
    navigation_type = Page::OPTION;
  }
}

// print the page
void Page::print() const {
  cout << story;
  cout << "\n";

  if (navigation_type == WIN) {
    cout << "Congratulations! You have won. Hooray!\n";
  }
  else if (navigation_type == LOSE) {
    cout << "Sorry, you have lost. Better luck next time!\n";
  }
  else {
    cout << "What would you like to do?\n\n";
    for (size_t i = 0; i < options.size(); i++) {
      cout << " " << i + 1 << ". " << options[i].desc << "\n";
    }
  }
}

// get related page numbers
vector<int> Page::getToPageNums() const {
  vector<int> res;
  for (size_t i = 0; i < options.size(); i++) {
    res.push_back(options[i].to_page);
  }
  return res;
}
