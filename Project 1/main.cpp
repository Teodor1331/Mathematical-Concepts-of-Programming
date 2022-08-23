#include "gauss.h"
#include "matrix.h"

#include <iostream>
#include <fstream>
#include <sstream>

const double coefficients[4] = {0.129, 1.461, 85.07, 0.132};

int main(int argc, const char* argv[]) {

    if (argc == 1) {
        std::cout << "Not given enough console arguments!" <<  std::endl;
    }
    else if (argc == 2) {

        const char* filepath = argv[1];

        double **result_wrong = create_matrix(filepath);
        double **result_right = copy_matrix(result_wrong);
        double **result_copy = copy_matrix(result_wrong);

        std::cout << "Input of the program: " << std::endl;
        std::cout << std::endl;
        print_matrix(result_wrong);

        std::cout << std::endl;

        one_row_sum(result_right);

        double *prices = gauss(result_wrong);

        std::cout << "Output of the program: " << std::endl;
        std::cout << std::endl;

        for (int i = 0; i < 4; i++) {
            double value = result_copy[i][4] - result_right[i][4];
            std::cout << value << " ";
        }
        std::cout << std::endl;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                double value = ((prices[j] - coefficients[j]) * result_copy[i][j]) / prices[j];
                std::cout << value << " ";
            }

            std::cout << std::endl;
        }

        remove_matrix(result_copy);
        remove_matrix(result_right);
        remove_matrix(result_wrong);

        delete[] prices;
    }
    else {
        std::cout << "Given too many console arguments!" << std::endl;
    }

    return 0;
}
