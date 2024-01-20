/**
 * Created by Michael Calle, Allison Lee, Angus Hu on December 27, 2023
*/

#ifndef CAR_HPP
#define CAR_HPP

#include "Network.hpp"

class Car {
private:
    double x_pos_;
    double y_pos_;
    Network network_;
public:
    /**
     * Big 5 Methods
    */

    // Default constructor
    Car();

    // Parameterized constructor
    Car(double x_pos, double y_pos, Network network);

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
    Network getNetwork() const;

    /**
     * Mutators
    */
    void setXPos(double x_pos);
    void setYPos(double y_pos);
    void setNetwork(Network network);

    /**
     * Print Functions
    */
    void printCar() const;

};
#endif