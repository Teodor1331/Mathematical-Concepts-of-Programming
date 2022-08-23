#include "gauss.h"
#include <iostream>

const double coefficients[4] = {0.129, 1.461, 85.07, 0.132};

void one_row_sum(double **matrix) {

    /* This function will be very important later,
    because its main purpose is to count the
    sum in levs in one company for every value,
    multiplied by its specific coefficient. The last
    ones are made globally because they will be used
    more than once. The sum is stored in the value
    in the last column. */

    for (int i = 0; i < 4; i++) {
        matrix[i][4] = matrix[i][0] * coefficients[0] + matrix[i][1] * coefficients[1] + matrix[i][2] * coefficients[2] + matrix[i][3] * coefficients[3];
    }
}

void swap_rows(int index1, int index2, double **matrix) {

    /* This function will be used in the Gauss elimination
    method to swap two rows, when is found a 0 value in the
    main diagonal of the matrix. The function takes the two
    indexes and the matrix as arguments. For swapping the
    rows, it will be used a temporary array (row) to store
    the value from the swapping.*/

    double arr[5];

    for (int i = 0; i < 5; i++) {
        arr[i] = matrix[index1][i];
    }

    for (int j = 0; j < 5; j++) {
        matrix[index1][j] = matrix[index2][j];
    }

    for (int k = 0; k < 5; k++) {
        matrix[index2][k] = arr[k];
    }
}

double* gauss(double **matrix) {

    /* This function will be used for the Gauss elimination method. 
    The "result" dynamic array will store the values of the unknowns.
    The loop will iterate until the penultimate row. If one of the
    elements in the main diagonal is 0, then there will be swapping of
    the rows in case the whole row is not with 0 values. After this in
    another inner loop the delimeter and the third loop will make the
    algorithm of Gauss. In the last loop the unknown values will be
    counted and they will be returned from the function. 
    
    The program is not supported with the case, when there are infinite
    solutions, because it is pointless and even if one company hasn't
    used anything, there will be some accruals, which means the last
    element in the matrix won't be 0, then the rows will be swapped
    during the process of the algorithm. */

    double *result = new double[4];

    for (int i = 0; i < 3; i++) {
        if (matrix[i][i] == 0) {
            for (int j = i; j < 4; j++) {
                if (matrix[j][i] != 0) {
                    swap_rows(i, j, matrix);
                    break;
                }
            }
        }

        for (int j = i + 1; j < 4; j++) {
            double delimeter = -(matrix[j][i] / matrix[i][i]);

            for (int k = i; k < 5; k++) {
                matrix[j][k] = matrix[j][k] + (matrix[i][k] * delimeter);
            }
        }
    }

    for (int i = 3; i >= 0; i--) {
        result[i] = matrix[i][4] / matrix[i][i];

        for (int j = 3; j > i; j--) {
            result[i] = result[i] - (result[j] * matrix[i][j]) / matrix[i][i];
        }
    }

    return result;
}
