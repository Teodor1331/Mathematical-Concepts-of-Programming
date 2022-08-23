#ifndef LOGIC
#define LOGIC

double* sizes_translations(Point);
Point* inner_rectangle_collinear(Point*, double);
Point* inner_rectangle_nonlinear(Point*, double);
int find_where_point(Point, Point*);
Point new_ball_coordinates_collinear(Point, Point, double, Point*, double*, Point);
Point new_ball_coordinates_nonlinear(Point, Point, double, Point*, double*, Point);


#endif
