/**
 * Created by Michael Calle, Allison Lee, Angus Hu on December 27, 2023
*/

#define PI 3.1415926535897932384626433832795

/**
 * Big 5 Methods
*/

// Default constructor
Car::Car():x_pos_(0), y_pos_(0), angle_(0){
    Network network;
    network_ = network;
}

// Parameterized constructor
Car::Car(double x_pos, double y_pos, double angle, Network network){
    x_pos_ = x_pos;
    y_pos_ = y_pos;
    angle_ = angle;
    network_ = network;
}

// Copy constructor
Car::Car(const Car& another_car){
    x_pos_ = another_car.x_pos_;
    y_pos_ = another_car.y_pos_;
    angle_ = another_car.angle_;
    network_ = another_car.network_;
}

// Copy Assignment operator
Car& Car::operator=(const Car& another_car){
    x_pos_ = another_car.x_pos_;
    y_pos_ = another_car.y_pos_;
    angle_ = another_car.angle_;
    network_ = another_car.network_;
    return *this;
}

// Destructor
Car::~Car(){}

/**
 * Accessors
*/

double Car::getXPos() const {
    return x_pos_;
}

double Car::getYPos() const{
    return y_pos_;
}

double Car::getAngle() const{
    return angle_;
}

Network Car::getNetwork() const{
    return network_;
}

/**
 * Mutators
*/

void Car::setXPos(double x_pos){
    x_pos_ = x_pos;
}

void Car::setYPos(double y_pos){
    y_pos_ = y_pos;
}

void Car::setAngle(double angle){
    angle_ = angle;
}

void Car::setNetwork(Network network){
    network_ = network;
}

/**
    * Car functions
*/
void Car::addXPos(double x_pos_add) {
    x_pos_ += x_pos_add;
}

void Car::addYPos(double y_pos_add) {
    y_pos_ += y_pos_add;
}

void Car::move() {
    std::vector<double> input = {0, 0};
    network_.forwardPropagation(input);
    std::vector<double> output = network_.getOutputLayerValues();

    // network_.printNetwork();
    // for (int i = 0; i < output.size(); i++ ) {
    //     std::cout << output[i] << " ";
    // }
    // std::cout << std::endl;

    double speed = output[4];
    x_pos_ += speed * output[0];
    x_pos_ -= speed * output[1];
    y_pos_ += speed * output[2];
    y_pos_ -= speed * output[3];
}

void Car::mutate(double threshold) {
    network_.mutate(threshold);
}

double Car::getDistanceTo(int point[]) const {
    return sqrt(pow(point[0] - x_pos_, 2) + pow(point[1] - y_pos_, 2));
}

// void Car::radar(double angle, std::vector<Point> obstacles, sf::RenderTarget& window) {
//     int length = 0;
//     int radarX = x_pos_;
//     int radarY = y_pos_;

//     while (checkObstacle(radarX, radarY, obstacles) && length < 200) {
//         length++;

//         radarX = (int)(x_pos_ + cos((PI/180) * angle) * length);
//         radarY = (int)(y_pos_ + sin((PI/180) * angle) * length);
//     }
// }

/**
 * Print Functions
*/

/**
 * @post: prints values of x and y position, prints entire network
*/
void Car::printCar() const {
    std::cout << "x position: " << x_pos_ << "\ny position: " << y_pos_ << std::endl;
    network_.printNetwork();
}

/**
    * Draw Functions
*/
void Car::draw(sf::RenderTarget& window) const {
    //Set the diameter of the circle
    sf::RectangleShape shape(sf::Vector2f(20.f, 10.f));

    //Set the color of the circle
    shape.setFillColor(sf::Color::Blue);

    //Set the position of the circle
    sf::Vector2f position = {(float) x_pos_, (float) y_pos_};
    shape.setPosition(position);

    //Rotate
    shape.rotate((float) angle_);

    //Draw the circle to the target window
    window.draw(shape);
}