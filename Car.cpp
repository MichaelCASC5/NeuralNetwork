/**
 * Created by Michael Calle, Allison Lee, Angus Hu on December 27, 2023
*/

#include "Car.hpp"

/**
 * Big 5 Methods
*/

// Default constructor
Car::Car():x_pos_(0), y_pos_(0){
    Network network;
    network_ = network;
}

// Parameterized constructor
Car::Car(double x_pos, double y_pos, Network network){
    x_pos_ = x_pos;
    y_pos_ = y_pos;
    network_ = network;
}

// Copy constructor
Car::Car(const Car& another_car){
    x_pos_ = another_car.x_pos_;
    y_pos_ = another_car.y_pos_;
    network_ = another_car.network_;
}

// Copy Assignment operator
Car& Car::operator=(const Car& another_car){
    x_pos_ = another_car.x_pos_;
    y_pos_ = another_car.y_pos_;
    network_ = another_car.network_;
    return *this;
}

// Destructor
Car::~Car(){

}

/**
 * Accessors
*/

double Car::getXPos() const {
    return x_pos_;
}

double Car::getYPos() const{
    return y_pos_;
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

void Car::setNetwork(Network network){
    network_ = network;
}

/**
 * Print Functions
*/

/**
 * @post: prints values of x and y position, prints entire network
*/
void Car::printCar() const {
    std::cout << "x position: " << x_pos_ << "\Ny position: " << y_pos_ << std::endl;
    network_.printNetwork();
}