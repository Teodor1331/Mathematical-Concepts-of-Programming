// Teodor Dishanski, XI B, Number 23
// Technological School "Electronic Systems"

#include "../Source/ReadFileGraph.h"
#include "../Source/ConversionOperations.h"
#include "../Source/PrintOperations.h"
#include "../Source/UtilityOperations.h"

#include <iostream>
#include <vector>
#include <climits>

std::vector<std::vector<int>> associativeMatrix;        // The associative matrix of the graph.
std::vector<std::vector<int>> edgeList;                 // The edge list of the graph.
std::vector<std::vector<int>> adjencyList;              // The adjency list of the graph.
std::vector<std::vector<int>> cycles;                   // The possible paths through all vertices.

int timeShortestPath = -1;  // The shortest time in minutes for the result of the program.

void shortestPathTwoVertices(int startVertex, int endVertex, std::vector<std::vector<int>> associativeMatrix) {
    // This function will be used to find the shortest path from a start vertex
    // to an end vertex. For this purpose we should use the Dijkstra's algorithm.

    // If there is no path between two vertices (-1), we record INT_MAX there.
    // This will be needed to remove the possibility of using this path.

    for (unsigned int i = 0; i < associativeMatrix.size(); ++i) {
        for (unsigned int j = 0; j < associativeMatrix[i].size(); ++j) {
            if (associativeMatrix[i][j] == -1) {
                associativeMatrix[i][j] = INT_MAX;
            }
        }
    }

    std::vector<bool> visitedArray;     // Vector to store if vertices are visited.
    std::vector<int> distances;         // Vector to store the shortest distances.

    for (unsigned int i = 0; i < associativeMatrix.size(); ++i) {
        visitedArray.push_back(false);  // In the beginning all vertices are unvisited.
        distances.push_back(INT_MAX);   // In the beginning we don't know the shortest path.
    }

    distances[startVertex] = 0; // The distance from the start vertex to itself is equal to 0.

    // With this loop in fact we find the shortest path to every other vertex in the
    // graph (if there is a one). At the end of the program we will use just the vertex
    // we need information for which is our end vertex argument with real vertex index.

    for (unsigned int i = 0; i < associativeMatrix.size() - 1; ++i) {

        // Find the minimum distance from the not visited vertices.

        int vertex = minimumDistance(visitedArray, distances, associativeMatrix);
        visitedArray[vertex] = true; // Set the current vertex as visited.

        for (unsigned int j = 0; j < associativeMatrix.size(); ++j) {
            if (!visitedArray[j] && associativeMatrix[vertex][j] && distances[vertex] != INT_MAX && distances[vertex] + associativeMatrix[vertex][j] < distances[j]) {
                
                // 1-st condition - the next vertex is not visited.
                // 2-nd condition - there is a path between the vertices.
                // 3-rd condition - cost of the path is smaller than the current.
                
                distances[j] = distances[vertex] + associativeMatrix[vertex][j];
            }
        }
    }
    
    if (distances[endVertex] == INT_MAX) { std::cout << "There is no path between " << startVertex << " and " << endVertex << "!" << std::endl; return; }
    else { std::cout << "The shortest path between " << startVertex << " and " << endVertex << " is " << distances[endVertex] << "." << std::endl; return; }

    // Important: I haven't used this function in the program, but
    // I have made it because of the requirements in the project.
}

void findAllCycles(int startVertex, int nextVertex, std::vector<int> foundCycle) {
	std::vector<bool> visitedArray;         // Again, we use a vector for the visited vertices.
    foundCycle.push_back(nextVertex);       // In the beginning the next vertex is the start vertex.

    // Every time we use a new created visited array, so we have to manage it correctly.

	for (unsigned int i = 0; i < associativeMatrix.size(); ++i) { visitedArray.push_back(false); }
	for (unsigned int i = 0; i < foundCycle.size(); ++i) { visitedArray[foundCycle[i]] = true; }

	bool validateFullCycle = true;   // Validate if the path is already made through all vertices.

    // If any of the vertices is not visited, we set the upper variable to false.

	for (unsigned int i = 0; i < associativeMatrix.size(); ++i) {
		if (!visitedArray[i]) { validateFullCycle = false; }
	}

	if (validateFullCycle) {
        // If the path is a cycle, we add it to the global vector.

		if (associativeMatrix[nextVertex][startVertex] > 0) {
			cycles.push_back(foundCycle);
		}
	}
    else {
        // If the path is not a cycle, we use the function recursively.
        // We use the adjency list of the graph and we have to shift the index
        // because of the first number in every sublist which content is needless.

        for (unsigned int i = 0; i < adjencyList[nextVertex].size(); ++i) {
		    if (visitedArray[adjencyList[nextVertex][i + 1]] == 0 && adjencyList[nextVertex].size() != 1) {
			    findAllCycles(startVertex, adjencyList[nextVertex][i + 1], foundCycle);
		    }
	    }
    }

	return;
}

int findBestCycle() {
    if (!validateCycle(cycles)) { return -1; }  // The functions returns invalid result if there are no any cycles.

    std::vector<int> minutesPaths;   // The shortest path with the weights of the edges in minutes.

	for (unsigned int i = 0; i < cycles.size(); ++i) {
		std::vector<int> currentPath = cycles[i];   // For very path we calculate the minutes.
        int currentMinutes = 0;
	
		for (unsigned int j = 0; j < currentPath.size() - 1; ++j) {
			currentMinutes = associativeMatrix[currentPath[j]][currentPath[j + 1]] + currentMinutes;
		}
	
        // We should not forget to add the last distance from the end vertex to the start vertex.
		currentMinutes = associativeMatrix[currentPath[currentPath.size() - 1]][currentPath[0]]  + currentMinutes;
        minutesPaths.push_back(currentMinutes);
	}

    // At the end the function finds the minimum path in minutes
    // and returns the path index as result position.
	
	int minimumPath = minutesPaths[0];
    int pathIndex = 0;
	
	for (unsigned int i = 1; i < minutesPaths.size(); i++) {
		if (minutesPaths[i] < minimumPath){
			minimumPath = minutesPaths[i];
			pathIndex = i;
		}
	}
	
	timeShortestPath = minimumPath;
	return pathIndex;
}

int main(int argc, const char **argv) {

    // As in the other projects, the file with the graph structure must
    // be taken by the file and given as console argument to the program.

    if (argc < 2) { std::cout << "Not enough console arguments given!" << std::endl; }
    else if (argc > 2) { std::cout << "Too many console arguments given!" << std::endl; }
    else {
        associativeMatrix = readAssociativeMatrix(argv[1]);
        edgeList = getEdgeList(associativeMatrix);
        adjencyList = getAdjencyList(associativeMatrix);

        printAssociativeMatrix(associativeMatrix);
        printEdgeList(edgeList);
        printAdjencyList(adjencyList);

        int startVertex = 0;

        do {
            std::cout << "Enter the starting vertex: ";
            std::cin >> startVertex;
        } while (startVertex < 0 || (unsigned) startVertex > associativeMatrix.size());

        // In the beggining the vector for the path will be empty and
        // the start vertex and the end vertex will be a same one.

        std::vector<int> emptyPath;
        findAllCycles(startVertex, startVertex, emptyPath);
        int currentIndex = findBestCycle();

        if (currentIndex != -1) {
            std::cout << "The shortest path is: ";

            for (unsigned int i = 0; i < cycles[currentIndex].size(); ++i) {
                std::cout << cycles[currentIndex][i] << " ";
            }

            std::cout << std::endl;
        }
        else {
            std::cout << "There is no any cycle through this vertex!" << std::endl;
        }

        if (timeShortestPath != -1) { std::cout << "Time in minutes: " << timeShortestPath << std::endl; }
    }

    return 0;
}