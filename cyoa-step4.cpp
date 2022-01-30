#include <cstdlib>
#include <iostream>

#include "cyoa.h"

int main(int argc, char **argv)
try
{
    myassert(argc == 2, "Usage: ./cyoa-step4 story1");
    Story story(argv[1]);
    story.findPathToWin();
    return EXIT_SUCCESS;
}
catch (invalid_argument &e)
{
    cerr << e.what() << endl;
    exit(EXIT_FAILURE);
};
