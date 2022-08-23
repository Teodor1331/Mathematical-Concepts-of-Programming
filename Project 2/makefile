all: billiards

billiards: analytics.o data_reading.o validations.o logic.o main.o
	g++ -Wall -Wpedantic -Wextra analytics.o data_reading.o validations.o logic.o main.o -o billiards

analytics.o:
	g++ -Wall -Wpedantic -Wextra -c analytics.cpp

data_reading.o:
	g++ -Wall -Wpedantic -Wextra -c data_reading.cpp

validations.o:
	g++ -Wall -Wpedantic -Wextra -c validations.cpp

logic.o:
	g++ -Wall -Wpedantic -Wextra -c logic.cpp

main.o:
	g++ -Wall -Wpedantic -Wextra -c main.cpp

clean:
	-rm *.o
	-rm billiards
