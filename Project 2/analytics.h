#ifndef ANALYTICS
#define ANALYTICS

struct Point {
    double x = 0;
    double y = 0;
};

struct Line {
    double a = 0;
    double b = 0;
};

struct Vector {
    Point start;
    Point end;
};

Point translate_point(Point, double*);
Point untranslate_point(Point, double*);
Point rotate_point(Point, double);
Line describe_line(Point, Point);
Point crossing_point(Line, Line);
Line find_perpendicular(Line, Point);
Vector to_down_wall(Point, Point*);
Vector to_up_wall(Point, Point*);
Vector to_left_wall(Point, Point*);
Vector to_right_wall(Point, Point*);

#endif
