// Teodor Dishanski, XI B, Number 23
// Technological School "Electronic Systems"

#include <iostream>
#include <vector>

std::vector<std::vector<int>> findEdgeList(std::vector<std::vector<int>> associativeMatrix) {
    std::vector<std::vector<int>> edgeList;

    for (unsigned int i = 0; i < associativeMatrix.size(); i++) {
        for (unsigned int j = 0; j < associativeMatrix[i].size(); j++) {
            if (associativeMatrix[i][j]) {
                std::vector<int> subList;
                subList.push_back(i + 1); // Increment the first index.
                subList.push_back(j + 1); // Increment the second index.
                edgeList.push_back(subList);
            }
        }
    }

    return edgeList;
}

std::vector<std::vector<int>> findAdjencyListByEdgeList(std::vector<std::vector<int>> edgeList) {
    std::vector<std::vector<int>> adjencyList;

    std::vector<int> tmpVector;
    int currentEdge = edgeList[0][0];
    tmpVector.push_back(edgeList[0][0]);

    for (unsigned int i = 0; i < edgeList.size(); i++) {
        if (currentEdge == edgeList[i][0]) {
            tmpVector.push_back(edgeList[i][1]);
        }
        else {
            adjencyList.push_back(tmpVector);
            tmpVector.clear();

            currentEdge = edgeList[i][0];
            tmpVector.push_back(edgeList[i][0]);
            tmpVector.push_back(edgeList[i][1]);

            // The last line is needed in case we have only
            // one neighbour around the current edge.
        }
    }

    adjencyList.push_back(tmpVector); // Push the information for the last edge.

    return adjencyList;
}

std::vector<std::vector<int>> findAdjencyListByAssociativeMatrix(std::vector<std::vector<int>> associativeMatrix) {
    std::vector<std::vector<int>> adjencyList;

    for (unsigned int i = 0; i < associativeMatrix.size(); i++) {
        std::vector<int> tmpVector;
        tmpVector.push_back(i + 1); // Again increment the first index.

        for (unsigned int j = 0; j < associativeMatrix[i].size(); j++) {
            if (associativeMatrix[i][j]) {
                tmpVector.push_back(j + 1); // Again increment the second index.
            }
        }

        adjencyList.push_back(tmpVector);
    }

    return adjencyList;
}

int main() {

    std::vector<std::vector<int>> associativeMatrix;
    unsigned int edges = 0;

    do {
        std::cout << "Enter the number of edges: ";
        std::cin >> edges;
    } while (edges < 2);

    // Simulate an "automatic" graph for the program.
    for (unsigned int i = 0; i < edges; i++) {
        std::vector<int> tmpVector;
        for (unsigned int j = 0; j < edges; j++) {
            int number = rand() % 2;
            if (i == j) { number = 0; }
            tmpVector.push_back(number);
        }

        associativeMatrix.push_back(tmpVector);
    }

    std::cout << std::endl;
    std::cout << "The associative matrix is: " << std::endl;

    for (unsigned int i = 0; i < associativeMatrix.size(); i++) {
        for (unsigned int j = 0; j < associativeMatrix[i].size(); j++) {
            std::cout << associativeMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::vector<std::vector<int>> edgeList = findEdgeList(associativeMatrix);

    std::cout << std::endl;
    std::cout << "The edge list is: " << std::endl;

    for (unsigned int i = 0; i < edgeList.size(); i++) {
        std::cout << "(" <<  edgeList[i][0] << ", " << edgeList[i][1] << ")" << std::endl;
    }

    std::vector<std::vector<int>> adjencyList1 = findAdjencyListByEdgeList(edgeList);

    std::cout << std::endl;
    std::cout << "The adjency list by the edge list is: " << std::endl;

    for (unsigned int i = 0; i < adjencyList1.size(); i++) {
        for (unsigned int j = 0; j < adjencyList1[i].size(); j++) {
            if (j == 0) { std::cout << adjencyList1[i][j] << "| "; }
            else { std::cout << adjencyList1[i][j] << " "; }
        }
        std::cout << std::endl;
    }

    std::vector<std::vector<int>> adjencyList2 = findAdjencyListByAssociativeMatrix(associativeMatrix);
    
    std::cout << std::endl;
    std::cout << "The adjency list by the associative matrix is: " << std::endl;

    for (unsigned int i = 0; i < adjencyList2.size(); i++) {
        for (unsigned int j = 0; j < adjencyList2[i].size(); j++) {
            if (j == 0) { std::cout << adjencyList2[i][j] << "| "; }
            else { std::cout << adjencyList2[i][j] << " "; }
        }
        std::cout << std::endl;
    }

    return 0;
}
