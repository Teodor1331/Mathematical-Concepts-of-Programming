#ifndef READ_FILE_GRAPH
#define READ_FILE_GRAPH

#include <string>
#include <vector>

std::vector<int> convertStringLine(std::string stringLine);
bool validateFileMatrix(std::vector<std::vector<int>> associativeMatrix);
std::vector<std::vector<int>> readAssociativeMatrix(const char* filePath);

#endif