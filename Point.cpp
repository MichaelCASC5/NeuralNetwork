Point::Point(int x_pos, int y_pos) {
    x_pos_ = x_pos;
    y_pos_ = y_pos;
}

int Point::getXPos() const {
    return x_pos_;
}

int Point::getYPos() const{
    return y_pos_;
}

/**
    * Draw Functions
*/
void Point::draw(sf::RenderTarget& window) const {
    //Set the diameter of the circle
    sf::CircleShape shape(2.f);

    //Set the color of the circle
    shape.setFillColor(sf::Color::Red);

    //Set the position of the circle
    sf::Vector2f position = {(float) x_pos_, (float) y_pos_};
    shape.setPosition(position);

    //Draw the circle to the target window
    window.draw(shape);
}