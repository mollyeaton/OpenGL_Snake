
#ifndef ME_FINAL_PROJECT_GRAPHICS_SQUARE_H
#define ME_FINAL_PROJECT_GRAPHICS_SQUARE_H

#include <vector>


struct point {
    double x;
    double y;
};

struct fill {
    double red;
    double blue;
    double green;
};


class Square{

private:
    point center;
    fill color;
    const unsigned int LENGTH = 5;
    std::vector<point> corners;

    void drawPoint(const point &p) const;
    void resetCorners();

public:
    //constructor
    Square();
    Square(point center);

    void draw() const;

    void move(double delta_x, double delta_y) ;
};


#endif //ME_FINAL_PROJECT_GRAPHICS_SQUARE_H
