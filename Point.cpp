/**
 * Created by Michael Calle, Allison Lee, Angus Hu on December 27, 2023
*/

// Default constructor
Point::Point(): x_pos_(0), y_pos_(0){}

// Parameterized constructor
Point::Point(int x_pos, int y_pos) {
    x_pos_ = x_pos;
    y_pos_ = y_pos;
}

// Copy constructor
Point::Point(const Point& point){
    x_pos_ = point.x_pos_;
    y_pos_ = point.y_pos_;
}

// Copy assignment
Point& Point::operator=(const Point& point){
    x_pos_ = point.x_pos_;
    y_pos_ = point.y_pos_;
    return *this;
}

// Destructor
Point::~Point(){}

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
    sf::CircleShape shape(10.f);

    //Set the color of the circle
    shape.setFillColor(sf::Color::Red);

    //Set the position of the circle
    sf::Vector2f position = {(float) (x_pos_ - 5), (float) (y_pos_ - 5)};
    shape.setPosition(position);

    //Draw the circle to the target window
    window.draw(shape);
}