#pragma once
/**
 * Created by Michael Calle, Allison Lee, Angus Hu on December 27, 2023
*/

#ifndef CAR_HPP
#define CAR_HPP

#include "Network.h"
// #include "Point.h"
#include <cmath>
#include <SFML/Graphics.hpp>

class Car {
private:
    double x_pos_;
    double y_pos_;
    double angle_;
    double velocity_;

    bool active_;

    Network network_;
public:
    /**
        * Big 5 Methods
    */

    // Default constructor
    Car();

    // Parameterized constructor
    Car(double x_pos, double y_pos, double angle, double velocity, bool active, Network network);

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
    double getVelocity() const;
    bool getActive() const;
    Network getNetwork() const;

    /**
        * Mutators
    */
    void setXPos(double x_pos);
    void setYPos(double y_pos);
    void setAngle(double angle);
    void setVelocity(double velocity);
    void setActive(bool active);
    void setNetwork(Network network);

    /**
        * Car functions
    */
    void addXPos(double x_pos_add);
    void addYPos(double y_pos_add);
    void move(std::vector<std::vector<bool>>& obstacles, sf::RenderTarget& window);
    void mutate(double threshold);
    double getDistanceTo(int point[]) const;
    bool checkObstacle(int radarX, int radarY, std::vector<std::vector<bool>>& obstacles);
    double radar(double angle, std::vector<std::vector<bool>>& obstacles, sf::RenderTarget& window);
    void reset(int point[]);

    /**
        * Print Functions
    */
    void printCar() const;

    /**
        * Draw Functions
    */
    void draw(sf::RenderTarget& window) const;
};

#endif
