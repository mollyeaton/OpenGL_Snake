#include "graphics.h"
#include <ctime>
#include <memory>
#include "shape.h"
#include "snake.h"
#include <vector>
#include "egg.h"
#include <iostream>
#include <cstdlib>

#define UP    0
#define DOWN  1
#define LEFT  2
#define RIGHT 3

using namespace std;
//set initial direction as down
int direction = UP;
bool moved = false;
bool needFood = true;
bool foodCollides;
point tempCenter;
//object for the snake and egg
vector<unique_ptr<Shape>> game ;


int x,y;
point eggCenter; //center of the egg

GLdouble width, height;
int wd;
void populateGame(){
    //populate the egg into the first index
    game.push_back(make_unique<Egg>(0,0));
    //start with three blocks to the snake
    game.push_back(make_unique<Snake>(50,90));
    game.push_back(make_unique<Snake>(50,70));
    game.push_back(make_unique<Snake>(50,50));

}
void init() {
    width = 600;
    height = 600;
    //seed the random number generator
    srand(time(NULL));
    //create the objects for the game
    populateGame();

}

void initGL() {
    //glMatrixMode(GL_PROJECTION);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}


void display(){
    glViewport(0, 0, width*2, height*2); // DO NOT CHANGE THIS LINE

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, 0.0, height, -1.f, 1.f);

    // Clear the color buffer with current clearing color
    glClear(GL_COLOR_BUFFER_BIT); // DO NOT CHANGE THIS LINE
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(0.09, 0.38, 0.46);

    makeFood();

    // Draw the game with ~polymorphism~
    for (unique_ptr<Shape> &g : game) {
        g->draw();
    }


    glFlush();
}

void kbd(unsigned char key, int x, int y){
    // escape
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }

    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_DOWN:
            if (direction != UP && direction != DOWN) {
                moved = true;
                moveSnake(DOWN);
            }
            break;
        case GLUT_KEY_LEFT:
            if (direction != RIGHT && direction != LEFT) {
                moved = true;
                moveSnake(LEFT);
            }
            break;
        case GLUT_KEY_RIGHT:
            if (direction != LEFT && direction != RIGHT) {
                moved = true;
                moveSnake(RIGHT);
            }
            break;
        case GLUT_KEY_UP:

            if (direction != DOWN && direction != UP) {
                moved = true;
                moveSnake(UP);
            }
            break;
    }
    glutPostRedisplay();
}

void cursor(int x, int y) {

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {

    glutPostRedisplay();
}

void timer(int dummy) {

    glutPostRedisplay();
    glutTimerFunc(100, timer, dummy);
}
void moveSnake(int d) {
    glutPostRedisplay();
    direction = d;
    point next, temp;
    //exit the game if the head runs into the tail
    for (int i = 5; i < game.size(); ++i){
        for (int j = 0; j < 2; ++j){
            if (game[i]->isOverlapping(game[1]->corners[j])){
                exit(0);
            }
        }
    }
    switch (direction) {
        case UP:
            //check if the head is overlapping with the egg
            if (game[1]->isOverlapping(eggCenter)) {
                //clear the current egg and set need food to true
                needFood = true;
                //set the next place holder to the head's center
                next = game[1]->getCenter();
                //shift the head in the correct direction  by 10
                game[1]->move(0, 10);

                //loop through the  while storing centers
                //move each segment to the segment in front's center
                for (int i = 2; i < game.size(); ++i) {
                    temp = game[i]->getCenter();
                    game[i]->setCenter(next);
                    next = temp;
                }

                //add on a segment to the snake's tail
                game.push_back(make_unique<Snake>(next.x, next.y));
                //call the make food function to create a new egg
                makeFood();
            }
            //else the snake is not overlapping with the egg
            else {
                needFood = false;
                //set the next place holder to the head's center
                next = game[1]->getCenter();
                //shift the head in the correct direction  by 10
                game[1]->move(0, 10);

                //loop through the  while storing centers
                //move each segment to the segment in front's center
                for (int i = 2; i < game.size(); ++i) {
                    temp = game[i]->getCenter();
                    game[i]->setCenter(next);
                    next = temp;
                }
            }
            break;
        case DOWN:
            //check if the head is overlapping with the egg
            if (game[1]->isOverlapping(eggCenter)) {
                //clear the current egg and set need food to true
                needFood = true;
                //set the next place holder to the head's center
                next = game[1]->getCenter();
                //shift the head in the correct direction  by 10
                game[1]->move(0, -10);

                //loop through the  while storing centers
                //move each segment to the segment in front's center
                for (int i = 2; i < game.size(); ++i) {
                    temp = game[i]->getCenter();
                    game[i]->setCenter(next);
                    next = temp;
                }

                //add on a segment to the snake's tail
                game.push_back(make_unique<Snake>(next.x, next.y));
                //call the make food function to create a new egg
                makeFood();
            }
                //else the snake is not overlapping with the egg
            else {
                needFood = false;
                //set the next place holder to the head's center
                next = game[1]->getCenter();
                //shift the head in the correct direction  by 10
                game[1]->move(0, -10);

                //loop through the  while storing centers
                //move each segment to the segment in front's center
                for (int i = 2; i < game.size(); ++i) {
                    temp = game[i]->getCenter();
                    game[i]->setCenter(next);
                    next = temp;
                }
            }
            break;
        case LEFT:
            //check if the head is overlapping with the egg
            if (game[1]->isOverlapping(eggCenter)) {
                //clear the current egg and set need food to true
                needFood = true;
                //set the next place holder to the head's center
                next = game[1]->getCenter();
                //shift the head in the correct direction  by 10
                game[1]->move(-10, 0);

                //loop through the  while storing centers
                //move each segment to the segment in front's center
                for (int i = 2; i < game.size(); ++i) {
                    temp = game[i]->getCenter();
                    game[i]->setCenter(next);
                    next = temp;
                }

                //add on a segment to the snake's tail
                game.push_back(make_unique<Snake>(next.x, next.y));
                //call the make food function to create a new egg
                makeFood();
            }
                //else the snake is not overlapping with the egg
            else {
                needFood = false;
                //set the next place holder to the head's center
                next = game[1]->getCenter();
                //shift the head in the correct direction  by 10
                game[1]->move(-10, 0);

                //loop through the  while storing centers
                //move each segment to the segment in front's center
                for (int i = 2; i < game.size(); ++i) {
                    temp = game[i]->getCenter();
                    game[i]->setCenter(next);
                    next = temp;
                }
            }
            break;
        case RIGHT:
            //check if the head is overlapping with the egg
            if (game[1]->isOverlapping(eggCenter)) {
                //clear the current egg and set need food to true
                needFood = true;
                //set the next place holder to the head's center
                next = game[1]->getCenter();
                //shift the head in the correct direction  by 10
                game[1]->move(10, 0);

                //loop through the  while storing centers
                //move each segment to the segment in front's center
                for (int i = 2; i < game.size(); ++i) {
                    temp = game[i]->getCenter();
                    game[i]->setCenter(next);
                    next = temp;
                }

                //add on a segment to the snake's tail
                game.push_back(make_unique<Snake>(next.x, next.y));
                //call the make food function to create a new egg
                makeFood();
            }
                //else the snake is not overlapping with the egg
            else {
                needFood = false;
                //set the next place holder to the head's center
                next = game[1]->getCenter();
                //shift the head in the correct direction  by 10
                game[1]->move(10, 0);

                //loop through the  while storing centers
                //move each segment to the segment in front's center
                for (int i = 2; i < game.size(); ++i) {
                    temp = game[i]->getCenter();
                    game[i]->setCenter(next);
                    next = temp;
                }
            }
            break;
        }
    }




void autoMove(int value){
    glutPostRedisplay();
    if(!moved){
        moveSnake(direction);
    } else {
        moved = false;
    }

    glutTimerFunc(100, autoMove, 0);
}

void makeFood(){
    if (needFood){
        foodCollides = true;

        while(foodCollides){
            foodCollides = false;
            //create a random coordinate point for the egg within the window
            x = rand() % (int)(width-Shape::LENGTH) + Shape::LENGTH;
            y = rand() % (int)(height - Shape::LENGTH) + Shape::LENGTH;
            //store the points
            tempCenter = {(double)x,(double)y};
            //declare a temporary egg
            Egg temp(tempCenter);

            //check if it collides with the snake
            //snake is stored in indexes 1 and up
            for(int i = 1; i < game.size(); ++i){
                for(int j= 0; j < 4; ++j){
                    if (temp.isOverlapping(game[i]->corners[j])){
                        foodCollides = true;
                    }
                }
            }
        }
        //exits the loop if it is not colliding
        eggCenter = tempCenter;
        needFood = false;
        //replace the egg with the new coordinates
        game[0] = make_unique<Egg>(eggCenter.x,eggCenter.y);
        }
    }



int main(int argc, char** argv){
    init();

    glutInit(&argc, argv);          // Initialize GLUT

    glutInitDisplayMode(GLUT_RGBA);

    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(0, 0); // Position the w
    wd = glutCreateWindow("Snake Game");

    glutDisplayFunc(display);

    initGL();
    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);

    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);

    // handles mouse movement
    glutPassiveMotionFunc(cursor);

    // handles mouse click
    glutMouseFunc(mouse);

    // handles timer
    glutTimerFunc(100, autoMove, 0);




    glutMainLoop();

    return 0;
}