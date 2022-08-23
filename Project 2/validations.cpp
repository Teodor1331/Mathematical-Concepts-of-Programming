#include "analytics.h"
#include "validations.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

bool valid_rectangle(Point *points) {

    double result1 = (points[1].x - points[0].x) * (points[3].x - points[0].x);
    double result2 = (points[1].y - points[0].y) * (points[3].y - points[0].y);
    double result3 = sqrt(pow((points[1].x - points[0].x), 2) + pow((points[1].y - points[0].y), 2));
    double result4 = sqrt(pow((points[3].x - points[0].x), 2) + pow((points[3].y - points[0].y), 2));
    double result5 = (result1 + result2) / (result3 * result4);

    double result6 = (points[0].x - points[1].x) * (points[2].x - points[1].x);
    double result7 = (points[0].y - points[1].y) * (points[2].y - points[1].y);
    double result8 = sqrt(pow((points[0].x - points[1].x), 2) + pow((points[0].y - points[1].y), 2));
    double result9 = sqrt(pow((points[2].x - points[1].x), 2) + pow((points[2].y - points[1].y), 2));
    double result10 = (result6 + result7) / (result8 * result9);

    double result11 = (points[3].x - points[2].x) * (points[1].x - points[2].x);
    double result12 = (points[3].y - points[2].y) * (points[1].y - points[2].y);
    double result13 = sqrt(pow((points[3].x - points[2].x), 2) + pow((points[3].y - points[2].y), 2));
    double result14 = sqrt(pow((points[1].x - points[2].x), 2) + pow((points[1].y - points[2].y), 2));
    double result15 = (result11 + result12) / (result13 * result14);

    return ((result5 == 0) && (result10 == 0) && (result15) == 0);
}

double* get_sizes_rectangle(Point* points) {

    double length = sqrt(pow((points[1].x - points[0].x), 2) + pow((points[1].y - points[0].y), 2));
    double width = sqrt(pow((points[2].x - points[1].x), 2) + pow((points[2].y - points[1].y), 2));

    if (length < width) {
        double tmp = length;
        length = width;
        width = tmp;
    }

    double *sizes = new double[2];
    sizes[0] = width;
    sizes[1] = length;
    return sizes;
}

bool collinear_axis(Point* points) {

    double result1 = (points[1].y - points[0].y) / (points[1].x - points[0].x);
    double result2 = (points[2].y - points[1].y) / (points[2].x - points[1].x);
    return ((result1 == 0) || (result2 == 0));
}

double area(Point point1, Point point2, Point point3) {

    double sum1 = point1.x * (point2.y - point3.y);
    double sum2 = point2.x * (point3.y - point1.y);
    double sum3 = point3.x * (point1.y - point2.y);
    return abs(sum1 + sum2 + sum3);
}

bool valid_point_coordinates(Point *points, Point place, double *sizes) {

    if (place.x == points[0].x && place.y == points[0].y) {return false; }
    else if (place.x == points[1].x && place.y == points[1].y) { return false; }
    else if (place.x == points[2].x && place.y == points[2].y) { return false; }
    else if (place.x == points[3].x && place.y == points[3].y) { return false; }


    double sum_rectangle = sizes[0] * sizes[1];
    double sum1 = area(points[0], points[1], place);
    double sum2 = area(points[1], points[2], place);
    double sum3 = area(points[2], points[3], place);
    double sum4 = area(points[3], points[0], place);
    double triangles_sum = (sum1 + sum2 + sum3 + sum4) / 2;

    if (round(triangles_sum) == round(sum_rectangle)) { return true; }
    else { return false; }
}

double calculate_vector(Point point1, Point point2, double side) {

    double result = sqrt(pow((point2.x - point1.x), 2) + pow((point2.y - point1.y), 2));

    double num1 = side / 10;
    double num2 = side * 3 / 10;

    if (result < num1 || result > num2) {
        std::cout << std::endl;
        std::cout << "Incorrect length of the vector!" << std::endl;
        return -1;
    }

    return result;
}

bool check_belonging(Point point, Line line) {
    return (point.y == line.a * point.x + line.b);
}
