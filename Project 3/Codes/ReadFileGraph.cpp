#include "../Source/ReadFileGraph.h"

#include <fstream>
#include <string>
#include <vector>

std::vector<int> convertStringLine(std::string stringLine) {
    // This function is used to convert a single string line
    // to a vector of whole numbers. It is important to be said
    // that the function concatenates itself with a space for the
    // correct reading of every last element in the given string.

    std::vector<int> result;
    stringLine.push_back(' ');

    int tmpNumber = 0;              // The read number from the string.
    bool checkNegative = false;     // Check if the number is -1 or not.

    for (unsigned int i = 0; i < stringLine.size(); ++i) {
        if (stringLine[i] >= '0' && stringLine[i] <= '9') {
            tmpNumber = tmpNumber * 10 + (stringLine[i] - '0');
        }
        else if (stringLine[i] == '-') {
            checkNegative = true;
        }
        else {
            if (checkNegative) { result.push_back(-tmpNumber); }
            else { result.push_back(tmpNumber); }

            tmpNumber = 0;          // Reset the integer variable for the next reading.
            checkNegative = false;  // Reset the boolean variable for the next reading.
        }
    }

    return result;
}

bool validateFileMatrix(std::vector<std::vector<int>> associativeMatrix) {
    // This function is additionally used to validate if the
    // matrix is a correct representation of a graph. This will
    // be used in the function for reading the matrix later.

    for (unsigned int i = 0; i < associativeMatrix.size(); ++i) {
        for (unsigned int j = 0; j < associativeMatrix[i].size(); ++j) {
            if (associativeMatrix.size() != associativeMatrix[i].size()) {
                return false;
            }
        }
    }

    return true;
}

std::vector<std::vector<int>> readAssociativeMatrix(const char* filePath) {
    // The function reads a matrix from a file and returns it as
    // a two-dimensional vector array. This will be the associative
    // matrix of the graph which will be used in the program.

    std::vector<std::vector<int>> associativeMatrix;

    std::fstream ReadFromFile(filePath);
    std::string stringLine = "";

    while (std::getline(ReadFromFile, stringLine)) {
        std::vector<int> numbersLineMatrix = convertStringLine(stringLine);
        associativeMatrix.push_back(numbersLineMatrix);
    }

    if (!validateFileMatrix(associativeMatrix)) {
        std::vector<std::vector<int>> emptyMatrix;
        return emptyMatrix;
    }

    return associativeMatrix;
}