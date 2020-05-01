# ME-Final-Project-Graphics

## Snake Game Using OpenGL

This project is my own take on the classic Snake Game. It is a simplified rendition to showcase usage of openGL and 
incorporate polymorphism. The object of the game is to move your snake via the arrow keys and eat as many eggs as you
can. Each egg you eat (by overlapping the head of the snake with the egg) your snake increases in size. Some versions 
have extra rules determining death such as running into walls, but the only death in my game is running into your own 
tail. The game will simply shut down if you happen to run into yourself. You may also exit the game at any time by 
pressing the escape key.

To run the program you will need these files:
> - graphics.h & graphics.cpp - main C++ program
> - shape.h & shape.cpp - the parent class for the object
> - snake.h & snake.cpp - child to the shape class and object making up the snake
> - egg.h & egg.cpp - child to the shape class and object used for the food

The game is initialized with a vector of unique pointers. Contained in the vector is the egg (located at the first index) 
and all of the segments of the snake. You begin the game with three segments and then a new piece is pushed onto the 
vector every time you eat an egg. Polymorphism is used when displaying the vector, due to the overriden draw() function.
Both the snake and the egg objects are derived from the shape class, but by overriding the draw methods different blocks
of code are executed when object->draw() is called.

While playing the game a timer function repeatedly calls a moveSnake function so that the movement of the snake is automatic
and the speed is regulated. If you call the function too frequently the snake will move too quickly. Every round of movement 
checks whether the snake has eaten an egg or run into itself. If an egg has been eaten then a 
new one is produced and stored in the vector while the tail gets an extra segment. The iconic movement of the snake game
was tricky to replicate. For the snake to follow corners and 'slither' the head of the snake is moved in the inputted 
direction first. Then the following segments are updated to their predecessor's location. 






