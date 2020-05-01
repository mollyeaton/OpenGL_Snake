#include "graphics.h"
#include <iostream>
#include "Shape.h"

using namespace std;

///////////////////Color Struct//////////////////////////
color::color() : red(0.0), green(0.0), blue(0.0) {
}

color::color(double r, double g, double b) : red(r), green(g), blue(b){
}

ostream& operator << (ostream& outs, const color &c) {
    outs << "(" << c.red << ", " << c.green << ", " << c.blue << ")";
    return outs;
}


////////////////////Point Struct//////////////////////////
point::point() : x(0), y(0) {}

point::point(double x, double y) : x(x), y(y) {}

ostream& operator << (ostream& outs, const point &p) {
    outs << "(" << p.x << ", " << p.y << ")";
    return outs;
}


/////////////////////Shape Class///////////////////////////
void Shape::resetCorners() {
    corners.clear();
    corners.resize(4);
    corners[0] = {center.x + (LENGTH / 2.0), center.y + (LENGTH / 2.0)};
    corners[1] = {center.x - (LENGTH / 2.0), center.y + (LENGTH / 2.0)};
    corners[2] = {center.x + (LENGTH / 2.0), center.y - (LENGTH / 2.0)};
    corners[3] = {center.x - (LENGTH / 2.0), center.y - (LENGTH / 2.0)};

}

void Shape::drawPoint(const point &p) const {
    glVertex2i(p.x, p.y);
}

Shape::Shape(){
    center = {0,0};
    fill = {.5,.5,.5};

    resetCorners();
}
Shape::Shape(point center, color fill){
    //set center and color
    this->center = center;
    this->fill = fill;
    //redo the corners
    resetCorners();
}

void Shape::move(double delta_x, double delta_y){
    //move via x
    center.x += delta_x;
    for (point &p : corners) {
        p.x += delta_x;
    }
    //move via y
    center.y += delta_y;
    for (point &p : corners) {
        p.y += delta_y;
    }

    resetCorners();
}


void Shape::setCenter(point p) {
    center = p;
    resetCorners();
}
int Shape::getLeftX() const {
    return center.x - (LENGTH / 2);
}

int Shape::getRightX() const {
    return center.x + (LENGTH / 2);
}

int Shape::getTopY() const {
    return center.y - (LENGTH / 2);
}

int Shape::getBottomY() const {
    return center.y + (LENGTH / 2);
}

point Shape::getCenter() const {
    return center;
}
