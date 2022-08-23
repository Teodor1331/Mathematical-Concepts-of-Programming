#include "analytics.h"
#include "data_reading.h"
#include "validations.h"
#include "logic.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

int main(int args, const char **argv) {

    if (args < 2) { std::cout << "Not enough console arguments given!" << std::endl; }
    else if (args > 2) { std::cout << "Too many console arguments given!" << std::endl; }
    else {

        Point *points = new Point[4];
        Point *inner = new Point[4];
        double *sizes = new double[2];
        double radius = 0;
        Point ball = {0, 0};

        int option = 0;

        do {
            std::cout << "How many points you describe the rectangle with: ";
            std::cin >> option;
        } while (option != 2 && option != 4);

        if (option == 2) {

            points = get_rectangle_two_points(argv[1]);
            bool check_rectangle = valid_rectangle(points);

        CHECK_AGAIN1:
            while (check_rectangle == false) {
                std::cout << std::endl;
                std::cout << "Incorrect data for the points! They are not for a rectangle!" << std::endl;
                std::cout << "Try again to input the two points one by one!" << std::endl;
                std::cout << std::endl;
                points = input_rectangle_two_points();
                check_rectangle = valid_rectangle(points);
            }

            sizes = get_sizes_rectangle(points);

            while (sizes[0] * 2 != sizes[1]) {
                std::cout << std::endl;
                std::cout << "Incorrect data for the pool! The width * 2 is not the length!" << std::endl;
                std::cout << "Try again to input the two points one by one!" << std::endl;
                std::cout << std::endl;
                points = input_rectangle_two_points();
                check_rectangle = valid_rectangle(points);
                if (check_rectangle == false) { goto CHECK_AGAIN1; }
                sizes = get_sizes_rectangle(points);
            }
        }
        else {

            points = get_rectangle_four_points(argv[1]);
            bool check_rectangle = valid_rectangle(points);

        CHECK_AGAIN2:
            while (check_rectangle == false) {
                std::cout << std::endl;
                std::cout << "Incorrect data for the points! They are not for a rectangle!" << std::endl;
                std::cout << "Try again to input the four points one by one!" << std::endl;
                std::cout << std::endl;
                points = input_rectangle_four_points();
                check_rectangle = valid_rectangle(points);
            }

            sizes = get_sizes_rectangle(points);

            while (sizes[0] * 2 != sizes[1]) {
                std::cout << std::endl;
                std::cout << "Incorrect data for the pool! The width * 2 is not the length!" << std::endl;
                std::cout << "Try again to input the four points one by one!" << std::endl;
                std::cout << std::endl;
                points = input_rectangle_four_points();
                check_rectangle = valid_rectangle(points);
                if (check_rectangle == false) {goto CHECK_AGAIN2; }
                sizes = get_sizes_rectangle(points);
            }
        }

        radius = get_ball_radius(argv[1]);

        while ((radius * 2 < 0) || (radius * 2 > sizes[0])) {
            std::cout << std::endl;
            std::cout << "Incorrect data for the ball diameter! The diameter is invalid!" << std::endl;
            std::cout << "Try again to input the diameter of the ball!" << std::endl;
            std::cout << std::endl;
            radius = input_ball_radius();
        }

        bool is_collinear = collinear_axis(points);
        if (is_collinear == 1) { inner = inner_rectangle_collinear(points, radius); }
        else { inner = inner_rectangle_nonlinear(points, radius); }

        sizes = get_sizes_rectangle(inner);

        ball = get_ball_coordinates(argv[1]);
        bool validation1 = valid_point_coordinates(inner, ball, sizes);

        while (validation1 == false) {
            std::cout << std::endl;
            std::cout << "Incorrect data for the ball coordinates! The coordinates are not valid!" << std::endl;
            std::cout << "Try again to input the ball coordinates!" << std::endl;
            std::cout << std::endl;
            ball = input_ball_coordinates();
            validation1 = valid_point_coordinates(inner, ball, sizes);
        }

        std::cout << std::endl;
        std::cout << "The width of the pool is: " << sizes[0] << std::endl;
        std::cout << "The length of the pool is: " << sizes[1] << std::endl;
        std::cout << "The radius of the ball is: " << radius << std::endl;
        std::cout << "The coordinates of the ball are: " << ball.x << " " << ball.y << std::endl;
        std::cout << std::endl;

        Point start_point = ball;

        if (is_collinear == 1) {

            while (true) {
                double power = get_power();
                Point new_point = get_new_point();
                bool validation2 = valid_point_coordinates(inner, new_point, sizes);

            CHECK_LENGTH1:
                while (validation2 == false) {
                    std::cout << std::endl;
                    std::cout << "Incorrect data for the next point! The coordinates are not valid!" << std::endl;
                    std::cout << "Try again to input the next point coordinates!" << std::endl;
                    std::cout << std::endl;
                    new_point = get_new_point();
                    validation2 = valid_point_coordinates(inner, new_point, sizes);
                }

                double length = calculate_vector(new_point, ball, sizes[1]);
                std::cout << "The length of the vector is: " << length << std::endl;

                if (length == -1) {
                    validation2 = false;
                    goto CHECK_LENGTH1;
                }

                new_point = new_ball_coordinates_collinear(ball, new_point, power, inner, sizes, start_point);
                std::cout << "The new point is: " << new_point.x << " " << new_point.y << std::endl;
                ball = new_point;
                std::cout << std::endl;
            }
        }
        else {

            while (true) {
                double power = get_power();
                Point new_point = get_new_point();
                bool validation2 = valid_point_coordinates(inner, new_point, sizes);

            CHECK_LENGTH2:
                while (validation2 == false) {
                    std::cout << std::endl;
                    std::cout << "Inccorrect data for the next point! The coordinates are not valid!" << std::endl;
                    std::cout << "Try again to input the next point coordinates!" << std::endl;
                    std::cout << std::endl;
                    new_point = get_new_point();
                    validation2 = valid_point_coordinates(inner, new_point, sizes); 
                }

                double length = calculate_vector(new_point, ball, sizes[1]);
                std::cout << "The length of the vector is: " << length << std::endl;

                if (length == -1) {
                    validation2 = false;
                    goto CHECK_LENGTH2;
                }

                new_point = new_ball_coordinates_nonlinear(ball, new_point, power, inner, sizes, start_point);
                std::cout << "The new point is: " << new_point.x << " " << new_point.y << std::endl;
                ball = new_point;
                std::cout << std::endl;
            }
        }

        delete[] points;
        delete[] inner;
        delete[] sizes;
    }
    return 0;
}
