#include "snake.h"
#include <vector>
#include <iostream>


using namespace std;
//constructors

//default constructor initializes the snake with size of three
Snake::Snake() : Shape({50,90}, {0,1,0}){

}

//creates a body segment for the snake
Snake::Snake(point segCenter) : Shape(segCenter, {0,1,0}){
}

Snake::Snake(double x, double y) : Shape({x,y}, {0,1,0}){

}


//draw function
void Snake::draw() const{
    glBegin(GL_QUADS);

    //draw the Shape
    //use the color field as the fill
    glColor3f(0, 1, 0);

    drawPoint(corners[1]);
    drawPoint(corners[3]);
    drawPoint(corners[2]);
    drawPoint(corners[0]);

    glEnd();
}


