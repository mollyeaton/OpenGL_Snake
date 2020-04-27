#include <ctime>
#include "graphics.h"
#include "square.h"
#include <iostream>
#include <vector>

#define UP    0
#define DOWN  1
#define LEFT  2
#define RIGHT 3


using namespace std;

//bool to represent if food is already on the board
bool needFood = true;
//bool if the egg collides with the snake
bool foodCollides;
//bool to represent if ghe snake is moving direction
bool moved = false;
//set initial direction as down
int direction = DOWN;
//object for the snake and egg
vector<Square> snake;
vector<Square> egg;

point eggCenter; //center of the egg

//will hold the width and height of the window
GLdouble width, height;

void init() {
    width = 500;
    height = 500;
}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(2.0, 3.0, 6.0,  // eye position
              0.0, 0.0, 0.0,  // center position (not gaze direction)
              0.0, 1.0, 0.0); // up vector
}
void makeFood(){
    if (needFood){
        while(!foodCollides){
            foodCollides = false;
            //create coordinates for the food piece and store in a temp variable
            //pick a random x and y within the window to place the center
            point tempCenter = {static_cast<double>(rand() % (int)(width - Square::LENGTH)  + Square::LENGTH),
                                static_cast<double>((rand() % (int)height - Square::LENGTH) + Square::LENGTH) };

            Square temp(tempCenter, {1,1,1});

            //check if it collides with the snake
            for(int i = 0; i < snake.size(); ++i){
                for(int j= 0; j < temp.corners.size(); ++j){
                    if (snake[i].isOverlapping(temp.corners[j])){
                        foodCollides = true;
                    }
                }
            }

            if(!foodCollides){
                eggCenter = tempCenter;
                needFood = false;
                egg.push_back(Square(eggCenter, {1,1,1}));
            }


        }
    }


}

void moveSnake(int d){
    direction = d;
    point temp, next, back;
    switch(direction){
        case UP:
            if(snake[0].isOverlapping(eggCenter)) {
                egg.clear();
                needFood = true;
                makeFood();
                temp = snake[0].getCenter();
                snake[0].move(0, -3);
                for (int i = 1; i < snake.size(); ++i) {
                    next = snake[i].getCenter();
                    snake[i].setCenter(next);
                }
                temp = snake[-1].getCenter();
                moveSnake(UP);
                snake.push_back(Square(temp, {0,0,1}));
            }
            else {
                needFood = false;
                temp = snake[0].getCenter();
                snake[0].move(-3, 0);
                for (int i = 1; i < snake.size(); ++i) {
                    next = snake[i].getCenter();
                    snake[i].setCenter(next);
                }

            }
        case DOWN:
            if(snake[0].isOverlapping(eggCenter)) {
                egg.clear();
                needFood = true;
                makeFood();
                temp = snake[0].getCenter();
                snake[0].move(0, 3);
                for (int i = 1; i < snake.size(); ++i) {
                    next = snake[i].getCenter();
                    snake[i].setCenter(next);
                }
                temp = snake[-1].getCenter();
                moveSnake(DOWN);
                snake.push_back(Square(temp, {0,0,1}));
            }
            else {
                needFood = false;
                temp = snake[0].getCenter();
                snake[0].move(-3, 0);
                for (int i = 1; i < snake.size(); ++i) {
                    next = snake[i].getCenter();
                    snake[i].setCenter(next);
                }

            }
        case RIGHT:
            if(snake[0].isOverlapping(eggCenter)) {
                egg.clear();
                needFood = true;
                makeFood();
                temp = snake[0].getCenter();
                snake[0].move(3, 0);
                for (int i = 1; i < snake.size(); ++i) {
                    next = snake[i].getCenter();
                    snake[i].setCenter(next);
                }
                temp = snake[-1].getCenter();
                moveSnake(RIGHT);
                snake.push_back(Square(temp, {0,0,1}));
            }
            else {
                needFood = false;
                temp = snake[0].getCenter();
                snake[0].move(-3, 0);
                for (int i = 1; i < snake.size(); ++i) {
                    next = snake[i].getCenter();
                    snake[i].setCenter(next);
                }

            }
        case LEFT:
            if(snake[0].isOverlapping(eggCenter)) {
                egg.clear();
                needFood = true;
                makeFood();
                temp = snake[0].getCenter();
                snake[0].move(-3, 0);
                for (int i = 1; i < snake.size(); ++i) {
                    next = snake[i].getCenter();
                    snake[i].setCenter(next);
                }
                temp = snake[-1].getCenter();
                moveSnake(LEFT);
                snake.push_back(Square(temp, {0,0,1}));
            }
            else {
                needFood = false;
                temp = snake[0].getCenter();
                snake[0].move(-3, 0);
                for (int i = 1; i < snake.size(); ++i) {
                    next = snake[i].getCenter();
                    snake[i].setCenter(next);
                }

            }
    }
}

void continueMovement(int value){
    if(!moved){
        switch (direction){
            case UP:
                moveSnake(UP);
            case DOWN:
                moveSnake(DOWN);
            case RIGHT:
                moveSnake(RIGHT);
            case LEFT:
                moveSnake(LEFT);
        }
    }
    else{
        moved = false;
    }
    glutTimerFunc(200, continueMovement, 0);
}
/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {

    // tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width/2, width/2, -height/2, height/2, -width, width);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // Clear the color buffer with current clearing color

    glEnable(GL_DEPTH);
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT, GL_FILL);

//    for (int i = 0; i < snake.size(); ++i){
//        snake[i].draw();
//    }
//    makeFood();


    glFlush();  // Render now
}

void keyboard(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP :
            if (direction != DOWN && direction != UP) {
                moved = true;
                moveSnake(UP);
            }
        case GLUT_KEY_RIGHT:
            if (direction != LEFT && direction != RIGHT) {
                moved = true;
                moveSnake(RIGHT);
            }
        case GLUT_KEY_DOWN:
            if (direction != UP && direction != DOWN) {
                moved = true;
                moveSnake(DOWN);
            }
        case GLUT_KEY_LEFT:
            if (direction != RIGHT && direction != LEFT) {
                moved = true;
                moveSnake(LEFT);
            }
        }
    }


int main(int argc, char** argv) {

    init();

    glutInit(&argc, argv);          // Initialize GLUT

    glutInitDisplayMode(GLUT_RGBA);

    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(100, 200); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    int wd = glutCreateWindow("Snake Game" /* title */ );

    // Register callback handler for window re-paint event
    glutDisplayFunc(display);
    //glutKeyboardFunc(kbd);
    glutSpecialFunc(keyboard);
    glutTimerFunc(200, continueMovement, 0);

    srand(time(NULL));
    // Our own OpenGL initialization
    initGL();

    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}
