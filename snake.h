#ifndef ME_FINAL_PROJECT_GRAPHICS_SNAKE_H
#define ME_FINAL_PROJECT_GRAPHICS_SNAKE_H

#include "graphics.h"
#include "shape.h"
#include <vector>

#define UP    0
#define DOWN  1
#define LEFT  2
#define RIGHT 3

class Snake: public Shape {

private:
    //set the color to green
    color fill = {0,1,0};
    int size = 0;

public:

    //constructors
    explicit Snake();
    explicit Snake (point segCenter);
    explicit Snake(double x, double y);

    //destructor
    virtual ~Snake() = default;

    //draw function
    void draw() const override;

};


#endif //ME_FINAL_PROJECT_GRAPHICS_SNAKE_H
