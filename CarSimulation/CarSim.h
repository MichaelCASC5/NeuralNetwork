#pragma once

#ifndef CARSIM_HPP
#define CARSIM_HPP

// Classes include
#include "Network.h"
#include "Car.h"
#include "Point.h"

// C include
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

// External library include
#include <SFML/Graphics.hpp>

class CarSim
{
public:
    /**
     * Default Constructor
     */
    CarSim();

    /**
     * Destructor
     */
    ~CarSim();

    /**
     * Move cars
     */
    void moveCars(sf::RenderWindow& window);

    /**
     * Find closests
     */
    void findClosest();

    /**
     * Mutate cars
     */
    void mutateCars();

    /**
     * Perform game logic (window is passed only for debug purposes)
     */
    void logic(sf::RenderWindow& window);

    /**
     * Paint to screen
     */
    void paint(sf::RenderWindow& window);

    /**
     * Key events
     */
    void mouseEvents(sf::RenderWindow& window);

private:
    /**
     * GAME PRIVATE MEMBERS
     */

     // Timers
    std::chrono::steady_clock::time_point startTimer;

    // Simulation Objects
    std::vector<Car> cars;
    std::vector<std::vector<bool>> obstacles;
    //bool obs[20][20] = {};
    int startPoint[2] = { 50, 50 };
    int end[2] = { 390, 390 };

    //Generation counter
    int generation = 0;
    int mostFitCar;
};

#endif
