cyoa-step4: cyoa-step4.cpp cyoa.h page.cpp path.cpp story.cpp
	g++ -g -std=gnu++98 -Werror -Wall -fprofile-arcs -ftest-coverage -o cyoa-step4 cyoa-step4.cpp page.cpp path.cpp story.cpp
cyoa-step3: cyoa-step3.cpp cyoa.h page.cpp story.cpp path.cpp
	g++ -g -std=gnu++98 -Werror -Wall -o cyoa-step3 cyoa-step3.cpp page.cpp story.cpp path.cpp
cyoa-step2: cyoa-step2.cpp cyoa.h page.cpp story.cpp path.cpp
	g++ -g -std=gnu++98 -Werror -Wall -o cyoa-step2 cyoa-step2.cpp page.cpp story.cpp path.cpp
cyoa-step1: cyoa-step1.cpp cyoa.h page.cpp
	g++ -g -std=gnu++98 -Werror -Wall -o cyoa-step1 cyoa-step1.cpp page.cpp