all: Project3

Project3: Main.o ReadFileGraph.o ConversionOperations.o PrintOperations.o UtilityOperations.o
	g++ -Wall -Wpedantic -Wextra Main.o ReadFileGraph.o ConversionOperations.o PrintOperations.o UtilityOperations.o -o Project3

Main.o: Codes/Main.cpp
	g++ -Wall -Wpedantic -Wextra -c Codes/Main.cpp

ReadFileGraph.o: Codes/ReadFileGraph.cpp Source/ReadFileGraph.h
	g++ -Wall -Wpedantic -Wextra -c Codes/ReadFileGraph.cpp

ConversionOperations.o: Codes/ConversionOperations.cpp Source/ConversionOperations.h
	g++ -Wall -Wpedantic -Wextra -c Codes/ConversionOperations.cpp

PrintOperations.o: Codes/PrintOperations.cpp Source/PrintOperations.h
	g++ -Wall -Wpedantic -Wextra -c Codes/PrintOperations.cpp

UtilityOperations.o: Codes/UtilityOperations.cpp Source/UtilityOperations.h
	g++ -Wall -Wpedantic -Wextra -c Codes/UtilityOperations.cpp

clean:
	-rm *.o
	-rm Project3
