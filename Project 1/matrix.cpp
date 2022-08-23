#include "matrix.h"
#include <iostream>
#include <fstream>
#include <sstream>

double** create_matrix(const char* filepath) {

    /* This function is used for taking the needed values from the ".txt" file.
    At the end of the function it will return two-sized array (our matrix) as 
    a result. For creating it, I use dynamic memory. I have made my matrix (4 x 5)
    - why? In the text file the matrix always will be 5 rows by 4 columns - (5 x 4).
    But, to make our later operations with the matrix easier, it will be better if
    the values in the last row are in the last column. But why then I do not use
    matrix (5 x 5)? Because the program will temporary record the last row-values
    and then make them as last column-values, but not in the matrix, but in the
    "tmp_line" variable of the string stream.
    
    To make this, the first loop will record as wanted all 16 elements in the matrix,
    which are inside the sizes of (4 x 4). When a "SPACE" is found, it will be passed,
    while all the values from the text file are recorded in the matrix. After the loop
    the last row will be recorded in the stream, but it will be given to the matrix as
    last column. After the second loop, we should close all operations with the file. */

    double **matrix = new double*[4];

    for (int i = 0; i < 4; i++) {
        matrix[i] = new double[5];
    }

    std::ifstream inputting = std::ifstream(filepath);
    std::string tmp_line = "String for the recording.";

    for (int i = 0; i < 4; i++) {

        getline(inputting, tmp_line);
        std::stringstream var = std::stringstream(tmp_line);

        for (int j = 0; j < 4; j++) {
            var >> matrix[i][j];

            if (j < 3) {
                var.seekg(1, var.cur);
            }
        }
    }

    getline(inputting, tmp_line);
    std::stringstream var = std::stringstream(tmp_line);

    for (int i = 0; i < 4; i++) {
        var >> matrix[i][4];

        if (i < 3) {
            var.seekg(1, var.cur);
        }
    }

    inputting.close();
    return matrix;
}

double** copy_matrix(double **matrix) {

    /* The function takes a matrix as an argument,
    prepares dynamic memory for a copy, then assigns
    the values of the given matrix to the copied and
    return the copy of the matrix. This function will
    be used for not making problems with the counting
    of the needed result from the program. */

    double **result = new double* [5];

    for (int i = 0; i < 4; i++) {
        result[i] = new double [5];
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            result[i][j] = matrix[i][j];
        }
    }

    return result;
}

void print_matrix(double **matrix) {

    /* This function can be used for seeing the
    different states of the matrix after every
    last made operation on it. */

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void remove_matrix(double **matrix) {

    /* The function removes the used
    dynamic memory for the matrix. */

    for (int i = 0; i < 4; i++) {
        delete[] matrix[i];
    }

    delete[] matrix;
}
