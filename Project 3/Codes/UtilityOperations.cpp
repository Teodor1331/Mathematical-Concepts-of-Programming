#include "../Source/UtilityOperations.h"

#include <vector>
#include <climits>

int minimumDistance(std::vector<bool> visitedArray, std::vector<int> distances, std::vector<std::vector<int>> associativeMatrix) {
    // This is a utility function which will be used to find the vertex
    // with the minimum distance. In a for loop we will check from the
    // not included vertices in the visited array and the weights in the matrix.

    int minimumDistance = INT_MAX;      // Hypotethically we do not know the minimum distance yet.
    int vertexIndex = 0;                // Variable for the index of the vertex for the result.

    for (unsigned int i = 0; i < associativeMatrix.size(); ++i) {
        if (distances[i] <= minimumDistance && !visitedArray[i]) {
            minimumDistance = distances[i];     // Update the minimum distance for the loop.
            vertexIndex = i;                    // Update the needed vertex index for the result.
        }
    }

    return vertexIndex;
}

bool validateCycle(std::vector<std::vector<int>> cycles) {
    // To validate if there is a cycle through all vertices
    // we should simply check if there is any cycle in
    // the graph with the given start vertex. But we have
    // made this already and we just need to find the size
    // of our two-dimensional array.

    return cycles.size() != 0 ? true : false;
}