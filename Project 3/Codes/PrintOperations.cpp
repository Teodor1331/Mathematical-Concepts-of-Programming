#include "../Source/PrintOperations.h"

#include <iostream>
#include <vector>

void printAssociativeMatrix(std::vector<std::vector<int>> associativeMatrix) {
    // The function will be used to print the matrix before
    // the start of the program with the starting vertex.

    std::cout << "The associative matrix of the graph is: " << std::endl;

    for (unsigned int i = 0; i < associativeMatrix.size(); ++i) {
        for (unsigned int j = 0; j < associativeMatrix[i].size(); ++j) {
            std::cout << associativeMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl; return;
}

void printEdgeList(std::vector<std::vector<int>> edgeList) {
    // The function will be used to print the edge list before
    // the start of the program with the starting vertex.

    std::cout << "The edge list of the graph is: " << std::endl;

    for (unsigned int i = 0; i < edgeList.size(); ++i) {
        std::cout << "(" << edgeList[i][0] << ", ";
        std::cout << edgeList[i][1] << ")" << std::endl;
    }

    std::cout << std::endl; return;
}

void printAdjencyList(std::vector<std::vector<int>> adjencyList) {
    // The function will be used to print the adjency list before
    // the start of the program with the starting vertex.

    std::cout << "The adjency list of the graph is: " << std::endl;

    for (unsigned int i = 0; i < adjencyList.size(); ++i) {
        for (unsigned int j = 0; j < adjencyList[i].size(); ++j) {
            if (j == 0) { std::cout << adjencyList[i][j] << "| "; }
            else { std::cout << adjencyList[i][j] << " "; }
        }
        std::cout << std::endl;
    }
    
    std::cout << std::endl; return;
}