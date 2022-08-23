// Teodor Dishanski, XI B, Number 23

#include <iostream>
#include <cmath>

struct Point {
	double x;
	double y;

	Point(double x, double y): x(x), y(y) {}
};

class Vector {
	double x;
	double y;

public:
	Vector(double x, double y) : x(x), y(y) {}
	Vector(Point p1, Point p2) : x(p2.x - p1.x), y(p2.y - p1.y) {}

	void sum (const Vector& other) const {
		std::cout << "(" << x << ", " << ") + " << "(" << other.x << ", " << other.y << ")" << " = ";
		std::cout << "(" << x + other.x << ", " << y + other.y << ")" << std::endl;
	}

	void difference (const Vector& other) const {
		std::cout << "(" << x << ", " << ") - " << "(" << other.x << ", " << other.y << ")" << " = ";
		std::cout << "(" << x + (-other.x) << ", " << y + (-other.y) << ")" << std::endl;
	}

	bool is_colinear(const Vector& other) const {
		return (other.x / other.y == x / y);
	}

	double length() const {
		return sqrt(pow(x, 2) + pow(y, 2));
	}

	double angle(const Vector& other) const {
		double result1 = x * other.x + y * other.y;
		double result2 = result1 / (this->length() * other.length());
		return acos(result2);
	}
};

double area(const Point& p1, const Point& p2, const Point& p3) {
	return abs((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p2.x)) / 2;
}

double area(const Point points[50], int size) {
	if (size < 3) { 
		return -1;
	}

	double sum_areas = 0;

	for (int i = 2; i < size; i++) {
		sum_areas = sum_areas + area(points[0], points[i - 1], points[i]);
	}

	return sum_areas;
}

int main() {
	return 0;
}
