#ifndef VALIDATE
#define VALIDATE

bool valid_rectangle(Point*);
double* get_sizes_rectangle(Point*);
bool collinear_axis(Point*);
double area(Point, Point, Point);
bool valid_point_coordinates(Point*, Point, double*);
double calculate_vector(Point, Point, double);
bool check_belonging(Point, Line);

#endif
