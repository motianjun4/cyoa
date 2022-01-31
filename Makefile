all: cyoa-step1 cyoa-step2 cyoa-step3 cyoa-step4
cyoa-step4: cyoa-step4.cpp cyoa.h page.o path.o story.o
	g++ -g -std=gnu++98 -Werror -Wall -fprofile-arcs -ftest-coverage -o cyoa-step4 cyoa-step4.cpp page.o story.o path.o
cyoa-step3: cyoa-step3.cpp cyoa.h page.o story.o path.o
	g++ -g -std=gnu++98 -Werror -Wall -fprofile-arcs -ftest-coverage -o cyoa-step3 cyoa-step3.cpp page.o story.o path.o
cyoa-step2: cyoa-step2.cpp cyoa.h page.o story.o path.o
	g++ -g -std=gnu++98 -Werror -Wall -fprofile-arcs -ftest-coverage -o cyoa-step2 cyoa-step2.cpp page.o story.o path.o
cyoa-step1: cyoa-step1.cpp cyoa.h page.o
	g++ -g -std=gnu++98 -Werror -Wall -fprofile-arcs -ftest-coverage -o cyoa-step1 cyoa-step1.cpp page.o
page.o: page.cpp
	g++ -g -std=gnu++98 -Werror -Wall -fprofile-arcs -ftest-coverage -o page.o -c page.cpp
story.o: story.cpp
	g++ -g -std=gnu++98 -Werror -Wall -fprofile-arcs -ftest-coverage -o story.o -c story.cpp
path.o: path.cpp
	g++ -g -std=gnu++98 -Werror -Wall -fprofile-arcs -ftest-coverage -o path.o -c path.cpp
clean:
	ls | grep cyoa-step.$$ | xargs rm -f *.o *.gcno *.gcov *.gcda