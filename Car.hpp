/**
 * Created by Michael Calle, Allison Lee, Angus Hu on December 27, 2023
*/

#ifndef CAR_HPP
#define CAR_HPP

#include "Network.hpp"
#include <cmath>
#include <SFML/Graphics.hpp>

class Car {
private:
    double x_pos_;
    double y_pos_;
    double angle_;

    Network network_;
public:
    /**
        * Big 5 Methods
    */

    // Default constructor
    Car();

    // Parameterized constructor
    Car(double x_pos, double y_pos, double angle, Network network);

    // Copy constructor
    Car(const Car& another_car);

    // Copy Assignment operator
    Car& operator=(const Car& another_car);

    // Destructor
    ~Car();

    /**
        * Accessors
    */

    double getXPos() const;
    double getYPos() const;
    double getAngle() const;
    Network getNetwork() const;

    /**
        * Mutators
    */
    void setXPos(double x_pos);
    void setYPos(double y_pos);
    void setAngle(double angle);
    void setNetwork(Network network);

    /**
        * Car functions
    */
    void addXPos(double x_pos_add);
    void addYPos(double y_pos_add);
    void move();
    void mutate(double threshold);
    double getDistanceTo(int point[]) const;
    // void radar(double angle);

    /**
        * Print Functions
    */
    void printCar() const;

    /**
        * Draw Functions
    */
    void draw(sf::RenderTarget& window) const;
};

#include "Car.cpp"
#endif