#include "analytics.h"
#include "validations.h"
#include "logic.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

double* sizes_translation(Point point) {
    double num1 = 0 - point.x;
    double num2 = 0 - point.y;
    double *translations = new double[2];
    translations[0] = num1;
    translations[1] = num2;
    return translations;
}

Point* inner_rectangle_collinear(Point* points, double radius) {

    Point* new_points = new Point[4];
    new_points[0] = {points[0].x + radius, points[0].y + radius};
    new_points[1] = {points[1].x - radius, points[1].y + radius};
    new_points[2] = {points[2].x - radius, points[2].y - radius};
    new_points[3] = {points[3].x + radius, points[3].y - radius};
    return new_points;
}

Point* inner_rectangle_nonlinear(Point *points, double radius) {
    double *offsets = new double[2];
    Point* translated = new Point[4];
    Point *new_points = new Point[4];
    offsets = sizes_translation(points[0]);

    for (int i = 0; i < 4; i++) {
        translated[i] = translate_point(points[i], offsets);
    }

    double tangens = (translated[1].y - translated[0].y) / (translated[1].x - translated[0].x);
    double angle = atan(tangens);

    for (int i = 0; i < 4; i++) {
        translated[i] = rotate_point(translated[i], angle);
    }
    
    new_points = inner_rectangle_collinear(translated, radius);

    for (int i = 0; i < 4; i++) {
        new_points[i] = rotate_point(new_points[i], -angle);
    }

    for (int i = 0; i < 4; i++) {
        new_points[i] = untranslate_point(new_points[i], offsets);
        new_points[i].x = round(new_points[i].x);
        new_points[i].y = round(new_points[i].y);
    }

    delete[] offsets;
    delete[] translated;
    return new_points;
}

int find_where_point(Point place, Point *points) {
    
    if ((place.x > points[0].x && place.x < points[1].x) && (place.y < points[0].y && place.y < points[1].y)) { return 1; }
    else if ((place.x > points[3].x && place.x < points[2].x) && (place.y > points[3].y && place.y > points[2].y)) { return 2; }
    else if ((place.x < points[3].x && place.x < points[0].x) && (place.y < points[3].y && place.y > points[0].y)) { return 3; }
    else if ((place.x > points[2].x && place.x > points[1].x) && (place.y < points[2].y && place.y > points[1].y)) { return 4; }
    else if ((place.x > points[2].x) && (place.y > points[2].y)) { return 5; }
    else if ((place.x > points[1].x) && (place.y < points[1].y)) { return 6; }
    else if ((place.x < points[0].x) && (place.y < points[0].y)) { return 7; }
    else if ((place.x < points[3].x) && (place.y > points[3].y)) { return 8; }
    else { return 0; }
}

Point new_ball_coordinates_collinear(Point point1, Point point2, double power, Point *points, double *sizes, Point start_point) {

    Point last_place = point1;
    bool check = false;
    Point previous = last_place;

    for (int i = 0; i < power; i++) {

        check = valid_point_coordinates(points, last_place, sizes);
        if (check == true) { previous = last_place; }
        last_place.x = last_place.x + (point2.x - point1.x);
        last_place.y = last_place.y + (point2.y - point1.y);
        check = valid_point_coordinates(points, last_place, sizes);
    }

    check = valid_point_coordinates(points, last_place, sizes);

    Line diagon1 = describe_line(points[2], points[0]);
    Line diagon2 = describe_line(points[3], points[1]);

    bool check1 = (valid_point_coordinates(points, last_place, sizes) == false) && (check_belonging(last_place, diagon1) == true);
    bool check2 = (valid_point_coordinates(points, last_place, sizes) == false) && (check_belonging(last_place, diagon2) == true);
    if (check1 || check2) { return start_point; }

    while(check == false) {

        Line line1 = describe_line(points[1], points[0]);
        Line line2 = describe_line(points[2], points[3]);

        int result = find_where_point(last_place, points);
        Line our_line = describe_line(previous, last_place);
        Point collision = {0, 0};

        if (result == 1) {
            Vector result = to_down_wall(last_place, points);
            last_place.x = result.end.x;
            last_place.y = result.end.y;
            collision = crossing_point(line1, our_line);
            std::cout << "The ball bounced into the wall (" << collision.x << ", " << collision.y << ")" << std::endl;
        }
        else if (result == 2) {
            Vector result = to_up_wall(last_place, points);
            last_place.x = result.end.x;
            last_place.y = result.end.y;
            collision = crossing_point(line2, our_line);
            std::cout << "The ball bounced into the wall (" << collision.x << ", " << collision.y << ")" << std::endl;
        }
        else if (result == 3) {
            Vector result = to_left_wall(last_place, points);
            last_place.x = result.end.x;
            last_place.y = result.end.y;
            std::cout << "The ball bounced into a wall, which is collinear to Oy axis!" << std::endl;
        }
        else if (result == 4) {
            Vector result = to_right_wall(last_place, points);
            last_place.x = result.end.x;
            last_place.y = result.end.y;
            std::cout << "The ball bounced into a wall, which is collinear to Oy axis!" << std::endl;
        }
        else if (result == 5) {
            double num1 = abs(points[2].x - last_place.x);
            double num2 = abs(points[2].y - last_place.y);

            if (num1 > num2) {
                Vector result = to_right_wall(last_place, points);
                last_place.x = result.end.x;
                last_place.y = result.end.y;
                std::cout << "The ball bounced into a wall, whcih is collinear to Oy axis!" << std::endl;
            }
            else {
                Vector result = to_up_wall(last_place, points);
                last_place.x = result.end.x;
                last_place.y = result.end.y;
                collision = crossing_point(line2, our_line);
                std::cout << "The ball bounced into the wall (" << collision.x << ", " << collision.y << ")" << std::endl;
            }
        }
        else if (result == 6) {
            double num1 = abs(points[1].x - last_place.x);
            double num2 = abs(points[1].y - last_place.y);

            if (num1 > num2) {
                Vector result = to_right_wall(last_place, points);
                last_place.x = result.end.x;
                last_place.y = result.end.y;
                std::cout << "The ball bounced into a wall, which is collinear to Oy axis!" << std::endl;
            }
            else {
                Vector result = to_down_wall(last_place, points);
                last_place.x = result.end.x;
                last_place.y = result.end.y;
                collision = crossing_point(line1, our_line);
                std::cout << "The ball bounced into the wall (" << collision.x << ", " << collision.y << ")" << std::endl;
            }
        }
        else if (result == 7) {
            double num1 = abs(points[0].x - last_place.x);
            double num2 = abs(points[0].y - last_place.y);

            if (num1 > num2) {
                Vector result = to_left_wall(last_place, points);
                last_place.x = result.end.x;
                last_place.y = result.end.y;
                std::cout << "The ball bounced into a wall, which is collinear to Oy axis!" << std::endl;
            }
            else {
                Vector result = to_down_wall(last_place, points);
                last_place.x = result.end.x;
                last_place.y = result.end.y;
                collision = crossing_point(line1, our_line);
                std::cout << "The ball bounced into the wall (" << collision.x << ", " << collision.y << ")" << std::endl;
            }
        }
        else if (result == 8) {
            double num1 = abs(points[3].x - last_place.x);
            double num2 = abs(points[3].y - last_place.y);

            if (num1 > num2) {
                Vector result = to_left_wall(last_place, points);
                last_place.x = result.end.x;
                last_place.y = result.end.y;
                std::cout << "The ball bounced into a wall, which is collinear to Oy axis!" << std::endl;
            }
            else {
                Vector result = to_up_wall(last_place, points);
                last_place.x = result.end.x;
                last_place.y = result.end.y;
                collision = crossing_point(line2, our_line);
                std::cout << "The ball bounced into the wall (" << collision.x << ", " << collision.y << ")" << std::endl;
            }
        }
        else {
                std::cout << "A problem has occured with the program!" << std::endl;
                std::cout << "It cannot detect the collision with the wall!" << std::endl;
                break;
        }

        check = valid_point_coordinates(points, last_place, sizes);
        result = find_where_point(last_place, points);
    }

    return last_place;
}

Point new_ball_coordinates_nonlinear(Point point1, Point point2, double power, Point *points, double *sizes, Point start_point) {

    Point last_place = point1;
    bool check = false;
    Point previous = last_place;

    for (int i = 0; i < power; i++) {

        check = valid_point_coordinates(points, last_place, sizes);
        if (check == true) { previous = last_place; }

        last_place.x = last_place.x + (point2.x - point1.x);
        last_place.y = last_place.y + (point2.y - point1.y);

        check = valid_point_coordinates(points, last_place, sizes);
    }

    check = valid_point_coordinates(points, last_place, sizes);

    Line diagon1 = describe_line(points[2], points[0]);
    Line diagon2 = describe_line(points[3], points[1]);

    bool check1 = (valid_point_coordinates(points, last_place, sizes) == false) && (check_belonging(last_place, diagon1) == true);
    bool check2 = (valid_point_coordinates(points, last_place, sizes) == false) && (check_belonging(last_place, diagon2) == true);
    if (check1 || check2) { return start_point; }


    while (check == false) {

            Point collision = {0, 0};

            Line line1 = describe_line(points[1], points[0]);
            Line line2 = describe_line(points[2], points[3]);
            Line line3 = describe_line(points[2], points[1]);
            Line line4 = describe_line(points[3], points[0]);
            Line our_line = describe_line(previous, last_place);

            bool side11 = ((last_place.x > points[0].x && last_place.x < points[1].x) && (last_place.y < points[1].y && last_place.y > points[0].y));
            bool side12 = ((last_place.x > points[0].x && last_place.x < points[1].x) && (last_place.y < points[0].y || last_place.y < points[1].y));
            bool side13 = ((last_place.x > points[1].x || last_place.x > points[0].x) && (last_place.y < points[1].y && last_place.y > points[0].y));

            bool side21 = ((last_place.x > points[3].x && last_place.x < points[2].x) && (last_place.y < points[2].y && last_place.y > points[3].y));
            bool side22 = ((last_place.x > points[3].x && last_place.x < points[2].x) && (last_place.y > points[3].y || last_place.y > points[2].y));
            bool side23 = ((last_place.x < points[2].x || last_place.x < points[3].x) && (last_place.y < points[2].y && last_place.y > points[3].y));

            bool side31 = ((last_place.x > points[2].x && last_place.x < points[1].x) && (last_place.y > points[1].y && last_place.y < points[2].y));
            bool side32 = ((last_place.x > points[2].x && last_place.x < points[1].x) && (last_place.y > points[2].y || last_place.y > points[1].y));
            bool side33 = ((last_place.x > points[1].x || last_place.x > points[2].x) && (last_place.y > points[1].y && last_place.y < points[2].y));

            bool side41 = ((last_place.x > points[3].x && last_place.x < points[0].x) && (last_place.y > points[0].y && last_place.y < points[3].y));
            bool side42 = ((last_place.x > points[3].x && last_place.x < points[0].x) && (last_place.y < points[3].y || last_place.y < points[0].y));
            bool side43 = ((last_place.x < points[0].x || last_place.x < points[3].x) && (last_place.y > points[0].y && last_place.y < points[3].y));

            if (side11 || side12 || side13) {
                Line find_line = find_perpendicular(line1, last_place);
                Point find_point = crossing_point(line1, find_line);
                last_place.x = find_point.x * 2 - last_place.x;
                last_place.y = find_point.y * 2 - last_place.y;
                collision = crossing_point(line1, our_line);
                std::cout << "The ball bounced into the wall (" << collision.x << ", " << collision.y << ")" << std::endl;
            }
            else if (side21 || side22 || side23) {
                Line find_line = find_perpendicular(line2, last_place);
                Point find_point = crossing_point(line2, find_line);
                last_place.x = find_point.x * 2 - last_place.x;
                last_place.y = find_point.y * 2 - last_place.y;
                collision = crossing_point(line2, our_line);
                std::cout << "The ball bounced into the wall (" << collision.x << ", " << collision.y << ")" << std::endl;
            }
            else if (side31 || side32 || side33) {
                Line find_line = find_perpendicular(line3, last_place);
                Point find_point = crossing_point(line3, find_line);
                last_place.x = find_point.x * 2 - last_place.x;
                last_place.y = find_point.y * 2 - last_place.y;
                collision = crossing_point(line3, our_line);
                std::cout << "The ball bounced into the wall (" << collision.x << ", " << collision.y << ")" << std::endl;
            }
            else if (side41 || side42 || side43) {
                Line find_line = find_perpendicular(line4, last_place);
                Point find_point = crossing_point(line4, find_line);
                last_place.x = find_point.x * 2 - last_place.x;
                last_place.y = find_point.y * 2 - last_place.y;
                collision = crossing_point(line4, our_line);
                std::cout << "The ball bounced into the wall (" << collision.x << ", " << collision.y << ")" << std::endl;
            }
            else {
                std::cout << "A problem has occured with the program!" << std::endl;
                std::cout << "It cannot detect the collision with the wall!" << std::endl;
                break;
            }

            check = valid_point_coordinates(points, last_place, sizes);
    }
    return last_place;
}
