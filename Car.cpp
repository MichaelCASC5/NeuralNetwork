/**
 * Created by Michael Calle, Allison Lee, Angus Hu on December 27, 2023
*/

#define PI 3.1415926535897932384626433832795

/**
 * Big 5 Methods
*/

// Default constructor
Car::Car():x_pos_(0), y_pos_(0), angle_(0), velocity_(0), active_(1) {
    Network network;
    network_ = network;
}

// Parameterized constructor
Car::Car(double x_pos, double y_pos, double angle, double velocity, bool active, Network network) {
    x_pos_ = x_pos;
    y_pos_ = y_pos;
    angle_ = angle;
    velocity_ = velocity;
    active_ = active;
    network_ = network;
}

// Copy constructor
Car::Car(const Car& other) {
    x_pos_ = other.x_pos_;
    y_pos_ = other.y_pos_;
    angle_ = other.angle_;
    velocity_ = other.velocity_;
    active_ = other.active_;
    network_ = other.network_;
}

// Copy Assignment operator
Car& Car::operator=(const Car& other) {
    x_pos_ = other.x_pos_;
    y_pos_ = other.y_pos_;
    angle_ = other.angle_;
    velocity_ = other.velocity_;
    active_ = other.active_;
    network_ = other.network_;
    return *this;
}

// Destructor
Car::~Car() {}

/**
 * Accessors
*/

double Car::getXPos() const {
    return x_pos_;
}

double Car::getYPos() const {
    return y_pos_;
}

double Car::getAngle() const {
    return angle_;
}

double Car::getVelocity() const {
    return velocity_;
}

bool Car::getActive() const {
    return active_;
}

Network Car::getNetwork() const {
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

void Car::setVelocity(double velocity){
    velocity_ = velocity;
}

void Car::setActive(bool active){
    active_ = active;
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

void Car::move(std::vector<Point> obstacles, sf::RenderTarget& window) {
    double radar1 = radar(0, obstacles, window);
    double radar2 = radar(-60, obstacles, window);
    double radar3 = radar(-30, obstacles, window);
    double radar4 = radar(30, obstacles, window);
    double radar5 = radar(60, obstacles, window);
    // std::cout << radar1 << std::endl;

    if (active_) {
        std::vector<double> input = {radar1, radar2, radar3, radar4, radar5};
        network_.forwardPropagation(input);
        std::vector<double> output = network_.getOutputLayerValues();

        // network_.printNetwork();
        // for (int i = 0; i < output.size(); i++ ) {
        //     std::cout << output[i] << " ";
        // }
        // std::cout << std::endl;

        // double speed = output[4];
        angle_ += output[0];
        angle_ -= output[1];
        velocity_ += output[2];
        velocity_ -= output[3];

        //Velocity cap
        if (velocity_ > 10) {
            velocity_ = 1;
        } else if (velocity_ < 0) {
            velocity_ = 0;
        }

        //Rotation
        x_pos_ += velocity_ * cos(angle_ * (PI/180));
        y_pos_ += velocity_ * sin(angle_ * (PI/180));
    }
}

void Car::mutate(double threshold) {
    network_.mutate(threshold);
}

double Car::getDistanceTo(int point[]) const {
    return sqrt(pow(point[0] - x_pos_, 2) + pow(point[1] - y_pos_, 2));
}

bool Car::checkObstacle(int radarX, int radarY, std::vector<Point> obstacles) {
    bool output = false;
    for (int i = 0; i < obstacles.size(); i++) {
        double dist = sqrt(pow(radarX - obstacles[i].getXPos(), 2) + pow(radarY - obstacles[i].getYPos(), 2));
        // std::cout << "what" << std::endl;
        if(dist <= 10) {
            output = true;
            // std::cout << "what" << std::endl;
            break;
        }
    }

    //Border obstacles
    if (radarX < 10 || radarX > 390 || radarY < 10 || radarY > 390) {
        output = true;
    }
    return output;
}

double Car::radar(double radarAngle, std::vector<Point> obstacles, sf::RenderTarget& window) {
    double length = 0;
    double radarX = x_pos_;
    double radarY = y_pos_;

    while (!checkObstacle(radarX, radarY, obstacles) && length < 100) {
        length += 10;

        radarX = (int)(x_pos_ + cos((PI/180) * (radarAngle + angle_)) * length);
        radarY = (int)(y_pos_ + sin((PI/180) * (radarAngle + angle_)) * length);

        /**
            * Draw radar for testing purposes
        */
        if (0) {
            //Set the diameter of the circle
            sf::CircleShape shape(1.f);

            //Set the color of the circle
            shape.setFillColor(sf::Color::White);

            //Set the position of the circle
            sf::Vector2f position = {(float) radarX, (float) radarY};
            shape.setPosition(position);

            //Draw the circle to the target window
            window.draw(shape);
        }
    }

    //If the car has collided with the obstacle, set active to false
    if (length < 10 || x_pos_ < 10 || x_pos_ > 390 || y_pos_ < 10 || y_pos_ > 390) {
        active_ = 0;
    }
    return length;
}

void Car::reset(int point[]) {
    x_pos_ = point[0];
    y_pos_ = point[1];
    angle_ = 45;
    velocity_ = 0;
    active_ = 1;
}

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