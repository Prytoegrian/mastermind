default: main

solution.o: Solution.cpp Solution.h
	g++ Solution.cpp -Wall -Wextra -c

status.o: Status.cpp Status.h
	g++ Status.cpp -Wall -Wextra -c

main: solution.o status.o
	g++ *.o main.cpp -Wall -Wextra -o mastermind.app
