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
public:
    // Default constructor
    Point();
    // Parameterized constructor
    Point(int x_pos, int y_pos);
    // Copy constructor
    Point(const Point& point);
    // Copy assignment
    Point& operator=(const Point& point);
    // Destructor
    ~Point();
    
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