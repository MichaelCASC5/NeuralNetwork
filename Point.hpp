/**
 * Created by Michael Calle, Allison Lee, Angus Hu on December 27, 2023
*/

#ifndef POINT_HPP
#define POINT_HPP

#include <cmath>
#include <SFML/Graphics.hpp>

class Point {
private:
    int x_pos_;
    int y_pos_;
    int diameter_;
public:
    // Parameterized constructor
    Point(int x_pos, int y_pos);

    /**
        * Accessors
    */
    int getXPos() const;
    int getYPos() const;

    /**
        * Draw Functions
    */
    void draw(sf::RenderTarget& window) const;
};

#include "Point.cpp"
#endif