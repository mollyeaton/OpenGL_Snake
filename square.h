
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

    void drawPoint(const point &p) const;
    void resetCorners();

public:
    static const int LENGTH = 5;
    //constructor
    Square();
    Square(point center, fill color);

    void draw() const;

    void move(double delta_x, double delta_y) ;

    bool isOverlapping(point &p);

    int getLeftX() const;
    int getRightX() const;
    int getTopY() const;
    int getBottomY() const;

    point getCenter() const;

    std::vector<point> corners;
};


#endif //ME_FINAL_PROJECT_GRAPHICS_SQUARE_H
