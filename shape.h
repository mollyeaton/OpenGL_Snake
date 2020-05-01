
#ifndef ME_FINAL_PROJECT_GRAPHICS_SQUARE_H
#define ME_FINAL_PROJECT_GRAPHICS_SQUARE_H

#include <vector>
#include <math.h> // This allows you to use sqrt and pow functions
#include <string>

const double PI = 3.14159265358979323846;

struct point {
    double x;
    double y;

    //constructors
    point();
    point(double x, double y);

    //overloaded operator
    friend std::ostream& operator << (std::ostream& outs, const point &p);
};

struct color {
    double red;
    double blue;
    double green;

    //constructors
    color();
    color(double r, double g, double b);

    //overloaded operator
    friend std::ostream& operator << (std::ostream& outs, const color &c);
};


class Shape{

protected:
    //structs
    point center;
    color fill;

    void drawPoint(const point &p) const;
    void resetCorners();

public:

    //global variable for the side lengths of the squares
    static const int LENGTH = 20;

    //public vector holding the corners of a square
    std::vector<point> corners;

    //constructors
    Shape();
    Shape(point center, color fill);

    //destructor
    virtual ~Shape() = default;

    //abstract method to draw the shape
    virtual void draw() const = 0;

    //move the square by desired amount
    void move(double delta_x, double delta_y);

    //check whether a square is overlapping a point
    bool isOverlapping(point &p) const;

    //getters
    int getLeftX() const;
    int getRightX() const;
    int getTopY() const;
    int getBottomY() const;
    point getCenter() const;

    //setter
    void setCenter(point p);
};


#endif //ME_FINAL_PROJECT_GRAPHICS_SQUARE_H
