#include "../Source/ConversionOperations.h"

#include <vector>

std::vector<std::vector<int>> getEdgeList(std::vector<std::vector<int>> associativeMatrix) {
    // This function is used to transform the associative matrix to
    // an edge list. The indexes of the vertices are saved with their
    // true numbering. This means vertex with index 0 will be 0, not 1.

    std::vector<std::vector<int>> edgeList;

    for (unsigned int i = 0; i < associativeMatrix.size(); ++i) {
        for (unsigned int j = 0; j < associativeMatrix[i].size(); ++j) {
            if (associativeMatrix[i][j] > 0) {
                std::vector<int> subList;
                subList.push_back(i);
                subList.push_back(j);
                edgeList.push_back(subList);
            }
        }
    }

    return edgeList;
}

std::vector<std::vector<int>> getAdjencyList(std::vector<std::vector<int>> associativeMatrix) {
    // This function is used to transform the associative matrix to
    // an adjency list. The indexes of the vertices are saved with their
    // true numbering. This means vertex with index 0 will be 0, not 1.

    std::vector<std::vector<int>> adjencyList;

    for (unsigned int i = 0; i < associativeMatrix.size(); ++i) {
        std::vector<int> subList;
        subList.push_back(i);

        for (unsigned int j = 0; j < associativeMatrix[i].size(); ++j) {
            if (associativeMatrix[i][j] > 0) {
                subList.push_back(j);
            }
        }

        adjencyList.push_back(subList);
    }

    return adjencyList;
}