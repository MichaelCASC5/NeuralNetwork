#pragma once

#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <cmath>
#include <SFML/Graphics.hpp>

class Vertex {
private:
    int x_pos_;
    int y_pos_;

    int value_;

public:
    // Parameterized constructor
    Vertex(int x_pos, int y_pos);
    Vertex(int x_pos, int y_pos, int value);

    /**
     * Accessor
    */
    int getX() const;
    int getY() const;
    int getValue() const;

    /**
     * Mutator Methods
     */
    void setX(int n);
    void setY(int n);
    void setValue(int n);

    /**
        * Draw Functions
    */
    void draw(sf::RenderTarget& window) const;
};

#endif
