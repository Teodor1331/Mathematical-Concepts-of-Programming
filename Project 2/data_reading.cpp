#include "analytics.h"
#include "validations.h"
#include "data_reading.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

Point* get_rectangle_two_points(const char *filepath) {

    Point lower_left = {0, 0};
    Point lower_right = {0, 0};
    Point upper_right = {0, 0};
    Point upper_left = {0, 0};

    std::ifstream inputting = std::ifstream(filepath);
    std::string tmp_line = "String for the recording.";

    getline(inputting, tmp_line);
    std::stringstream var = std::stringstream(tmp_line);

    var.seekg(1, var.cur);
    var >> lower_left.x;
    var.seekg(1, var.cur);
    var >> lower_left.y;
    var.seekg(3, var.cur);
    var >> upper_right.x;
    var.seekg(1, var.cur);
    var >> upper_right.y;
    var.seekg(1, var.cur);

    lower_right.x = upper_right.x;
    lower_right.y = lower_left.y;
    upper_left.x = lower_left.x;
    upper_left.y = upper_right.y;

    inputting.close();

    Point* points = new Point[4];
    points[0] = lower_left;
    points[1] = lower_right;
    points[2] = upper_right;
    points[3] = upper_left;
    return points;
}

Point* get_rectangle_four_points(const char* filepath) {

    Point lower_left = {0, 0};
    Point lower_right = {0, 0};
    Point upper_left = {0, 0};
    Point upper_right = {0, 0};

    std::ifstream inputting = std::ifstream(filepath);
    std::string tmp_line = "String for the recording.";

    getline(inputting, tmp_line);
    std::stringstream var = std::stringstream(tmp_line);

    var.seekg(1, var.cur);
    var >> lower_left.x;
    var.seekg(1, var.cur);
    var >> lower_left.y;
    var.seekg(3, var.cur);
    var >> lower_right.x;
    var.seekg(1, var.cur);
    var >> lower_right.y;
    var.seekg(3, var.cur);
    var >> upper_right.x;
    var.seekg(1, var.cur);
    var >> upper_right.y;
    var.seekg(3, var.cur);
    var >> upper_left.x;
    var.seekg(1, var.cur);
    var >> upper_left.y;
    var.seekg(1, var.cur);

    inputting.close();

    Point* points = new Point[4];
    points[0] = lower_left;
    points[1] = lower_right;
    points[2] = upper_right;
    points[3] = upper_left;
    return points;
}

Point* input_rectangle_two_points() {

    Point lower_left = {0, 0};
    Point lower_right = {0, 0};
    Point upper_right = {0, 0};
    Point upper_left = {0, 0};

    std::cout << "Enter the lower left point coordinates: ";
    std::cin >> lower_left.x >> lower_left.y;
    std::cout << "Enter the upper right point coordinates: ";
    std::cin >> upper_right.x >> upper_right.y;

    lower_right.x = upper_right.x;
    lower_right.y = lower_left.y;
    upper_left.x = lower_left.x;
    upper_left.y = upper_right.y;

    Point* points = new Point[4];
    points[0] = lower_left;
    points[1] = lower_right;
    points[2] = upper_right;
    points[3] = upper_left;
    return points;
}

Point* input_rectangle_four_points() {

    Point lower_left = {0, 0};
    Point lower_right = {0, 0};
    Point upper_right = {0, 0};
    Point upper_left = {0, 0};

    std::cout << "Enter the lower left point coordinates: ";
    std::cin >> lower_left.x >> lower_left.y;
    std::cout << "Enter the lower right point coordinates: ";
    std::cin >> lower_right.x >> lower_right.y;
    std::cout << "Enter the upper right point coordinates: ";
    std::cin >> upper_right.x >> upper_right.y;
    std::cout << "Enter the upper left point coordinates: ";
    std::cin >> upper_left.x >> upper_left.y;

    Point* points = new Point[4];
    points[0] = lower_left;
    points[1] = lower_right;
    points[2] = upper_right;
    points[3] = upper_left;
    return points;    
}

double get_ball_radius(const char *filepath) {

    double result = 0;

    std::ifstream inputting = std::ifstream(filepath);
    std::string tmp_line = "String for the recording.";

    getline(inputting, tmp_line);
    getline(inputting, tmp_line);

    std::stringstream var = std::stringstream(tmp_line);
    var >> result;

    inputting.close();
    return result / 2;
}

double input_ball_radius() {

    double result = 0;

    do {
        std::cout << "Enter the diameter of the ball: ";
        std::cin >> result;
    } while (result < 0);

    return result / 2;
}

Point get_ball_coordinates(const char *filepath) {

    Point ball = {0, 0};

    std::ifstream inputting = std::ifstream(filepath);
    std::string tmp_line = "String for the recording.";

    getline(inputting, tmp_line);
    getline(inputting, tmp_line);
    getline(inputting, tmp_line);

    std::stringstream var = std::stringstream(tmp_line);
    var.seekg(1, var.cur);
    var >> ball.x;
    var.seekg(1, var.cur);
    var >> ball.y;
    var.seekg(1, var.cur);

    inputting.close();
    return ball;
}

Point input_ball_coordinates() {

    Point ball = {0, 0};
    std::cout << "Enter the coordinates of the ball: ";
    std::cin >> ball.x >> ball.y;
    return ball;
}

double get_power() {

    double result = 0;

    do {
        std::cout << "Enter the power of the hit: ";
        std::cin >> result;
    } while (result < 2 || result > 5);

    return result;
}

Point get_new_point() {

    Point result = {0, 0};
    std::cout << "Enter the coordinates of the new point: ";
    std::cin >> result.x >> result.y;
    return result;
}
