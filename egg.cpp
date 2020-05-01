#include "egg.h"
#include "graphics.h"

using namespace std;
//constructor
Egg::Egg(point center) : Shape(), radius(LENGTH/2){
    this->setCenter(center);
}

Egg::Egg(double x, double y): Shape(), radius(LENGTH/2){
    this->setCenter({x,y});
}
//draw the egg as white
void Egg::draw() const{
    // Set drawing color to fill color
    glColor3f(fill.red, fill.green, fill.blue);
    // Draw circle as Triangle Fan
    glBegin(GL_TRIANGLE_FAN);
    // Draw center point
    glVertex2i(center.x, center.y);
    // Draw points on edge of circle
    for (double i = 0; i < 2.0*PI+0.05; i += (2.0*PI)/360.0) {
        glVertex2i(center.x + (radius * cos(i)),
                   center.y + (radius * sin(i)));
    }
    // End Triangle Fan
    glEnd();
}

bool Egg::isOverlapping(point &p) const {
    //check if the egg is overlapping with a point
    return ((p.x > getLeftX() && p.x < getRightX())
            && (p.y > getTopY() && p.y < getBottomY()));
}
