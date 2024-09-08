#include "Vertex.h"

Vertex::Vertex(int x_pos, int y_pos)
{
    x_pos_ = x_pos;
    y_pos_ = y_pos;

    value_ = -1;
}

Vertex::Vertex(int x_pos, int y_pos, int value)
{
    x_pos_ = x_pos;
    y_pos_ = y_pos;
    value_ = value;
}

/**
 * Accessor methods
 */

int Vertex::getX() const
{
    return x_pos_;
}

int Vertex::getY() const
{
    return y_pos_;
}

int Vertex::getValue() const
{
    return value_;
}

/**
 * Accessor functions
 */

void Vertex::setX(int n)
{
    x_pos_ = n;
}

void Vertex::setY(int n)
{
    y_pos_ = n;
}

void Vertex::setValue(int n)
{
    value_ = n;
}

/**
    * Draw Functions
*/
void Vertex::draw(sf::RenderTarget& window) const
{
    //Set the diameter of the circle
    sf::RectangleShape shape(sf::Vector2f(1.f, 1.f));

    //Set the color of the circle
    shape.setFillColor(sf::Color::White);

    //Set the position of the circle
    sf::Vector2f position = { (float)(x_pos_), (float)(y_pos_) };
    shape.setPosition(position);

    //Draw the circle to the target window
    window.draw(shape);
}
