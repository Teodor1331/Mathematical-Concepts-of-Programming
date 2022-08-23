all: companies

companies: main.o gauss.o matrix.o
	g++ -Wall -Wpedantic -Wextra main.o gauss.o matrix.o -o companies

main.o: main.cpp
	g++ -Wall -Wpedantic -Wextra -c main.cpp

gauss.o: gauss.cpp gauss.h
	g++ -Wall -Wpedantic -Wextra -c gauss.cpp

matrix.o: matrix.cpp matrix.h
	g++ -Wall -Wpedantic -Wextra -c matrix.cpp

clean:
	-rm *.o
	-rm companies;
