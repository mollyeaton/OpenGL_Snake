#ifndef ME_FINAL_PROJECT_GRAPHICS_EGG_H
#define ME_FINAL_PROJECT_GRAPHICS_EGG_H

#include "shape.h"

#define UP    0
#define DOWN  1
#define LEFT  2
#define RIGHT 3


class Egg: public Shape {

private:
    //set the color to white
    const color fill = {1,1,1};
    double radius;

public:
    //only constructor (needs a point for the center
    explicit Egg (point center);

    explicit Egg (double x, double y);

    //destructor
    virtual ~Egg() = default;

    //draw function
    void draw() const override;

    //check if egg is overlapping with any part of the snake
    bool isOverlapping(point &p) const override;



};



#endif //ME_FINAL_PROJECT_GRAPHICS_EGG_H
