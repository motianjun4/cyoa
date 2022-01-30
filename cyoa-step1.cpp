#include <cstdlib>
#include <iostream>

#include "cyoa.h"

int main(int argc, char ** argv) try {
  myassert(argc == 2, "Usage: ./step1 story1/page1.txt");
  Page page(argv[1]);
  page.print();
  return EXIT_SUCCESS;
}
catch (invalid_argument & e) {
  cerr << e.what() << endl;
  exit(EXIT_FAILURE);
};
