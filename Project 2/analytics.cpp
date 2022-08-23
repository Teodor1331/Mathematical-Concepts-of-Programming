#include "analytics.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

Point translate_point(Point point, double *new_sizes) {
    Point result = {0, 0};
    result.x = point.x + new_sizes[0];
    result.y = point.y + new_sizes[1];
    return result;
}

Point untranslate_point(Point point, double *new_sizes) {
    Point result = {0, 0};
    result.x = point.x - new_sizes[0];
    result.y = point.y - new_sizes[1];
    return result;
}

Point rotate_point(Point point, double angle) {
    Point result = {0, 0};
    result.x = (point.x * cos(angle)) + (point.y * sin(angle));
    result.y = (-point.x * sin(angle)) + (point.y * cos(angle));
    return result;
}

Line describe_line(Point point1, Point point2) {
    Line result = {0, 0};
    double num1 = point2.x - point1.x;
    double num2 = point2.y - point1.y;
    result.a = num2 / num1;
    result.b = point1.y - point1.x * result.a;
    return result;
}

Point crossing_point(Line line1, Line line2) {
    Point result = {0, 0};
    double num1 = line1.a - line2.a;
    double num2 = line2.b - line1.b;
    result.x = num2 / num1;
    result.y = line1.a * result.x + line1.b;
    return result;
}

Line find_perpendicular(Line line, Point point) {
    Line result = {0, 0};
    result.a = (-1) / line.a;
    result.b = point.y - result.a * point.x;
    return result;
}

Vector to_down_wall(Point point, Point* points) {
    Vector result = {{0, 0}, {0, 0}};
    result.start = point;
    result.end.x = point.x;
    result.end.y = points[0].y;
    result.end.x = 2 * result.end.x - result.start.x;
    result.end.y = 2 * result.end.y - result.start.y;
    return result;
}

Vector to_up_wall(Point point, Point* points) {
    Vector result = {{0, 0}, {0, 0}};
    result.start = point;
    result.end.x = point.x;
    result.end.y = points[2].y;
    result.end.x = 2 * result.end.x - result.start.x;
    result.end.y = 2 * result.end.y - result.start.y;
    return result;
}

Vector to_left_wall(Point point, Point* points) {
    Vector result = {{0, 0}, {0, 0}};
    result.start = point;
    result.end.x = points[0].x;
    result.end.y = point.y;
    result.end.x = 2 * result.end.x - result.start.x;
    result.end.y = 2 * result.end.y - result.start.y;
    return result;
}

Vector to_right_wall(Point point, Point* points) {
    Vector result = {{0, 0}, {0, 0}};
    result.start = point;
    result.end.x = points[2].x;
    result.end.y = point.y;
    result.end.x = 2 * result.end.x - result.start.x;
    result.end.y = 2 * result.end.y - result.start.y;
    return result;
}
