#include "graphics.h"
#include "square.h"



void Square::resetCorners() {
    corners.clear();
    corners.resize(8);
    corners[0] = {center.x + (LENGTH / 2.0), center.y + (LENGTH / 2.0)};
    corners[1] = {center.x - (LENGTH / 2.0), center.y + (LENGTH / 2.0)};
    corners[2] = {center.x + (LENGTH / 2.0), center.y - (LENGTH / 2.0)};
    corners[3] = {center.x - (LENGTH / 2.0), center.y - (LENGTH / 2.0)};

}

void Square::drawPoint(const point &p) const {
    glVertex2i(p.x, p.y);
}

Square::Square(){
    center = {0,0};
    resetCorners();
    color = {.5,.5,.5};
}

Square::Square(point center, fill color){
    this->center = center;
    resetCorners();
    this->color = color;
}

void Square::draw() const{
    glBegin(GL_QUADS);

    //draw the square
    //use the color field as the fill
    glColor3f(color.red, color.green, color.blue);

    drawPoint(corners[0]);
    drawPoint(corners[1]);
    drawPoint(corners[3]);
    drawPoint(corners[2]);

    glEnd();
}

void Square::move(double delta_x, double delta_y) {
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

}
bool Square::isOverlapping(point &p) {

    return ((p.x > getLeftX() && p.x < getRightX()) && (p.y > getTopY() && p.y < getBottomY()));

}

int Square::getLeftX() const {
    return center.x - (LENGTH / 2);
}

int Square::getRightX() const {
    return center.x + (LENGTH / 2);
}

int Square::getTopY() const {
    return center.y - (LENGTH / 2);
}

int Square::getBottomY() const {
    return center.y + (LENGTH / 2);
}

point Square::getCenter() const {
    return center;
}
