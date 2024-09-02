#pragma once

#ifndef CARSIM_HPP
#define CARSIM_HPP

// Classes include
#include "Network.h"
#include "Car.h"
//#include "Point.h"

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
    CarSim(int width, int height);

    /**
     * Destructor
     */
    ~CarSim();

    /**
     * Move cars
     */
    void moveCars();

    /**
     * Find closests
     */
    void findClosest();

    /**
     * Mutate cars
     */
    void mutateCars();

    /**
     * Perform game logic (displayRadar is passed only for debug purposes)
     */
    void logic();

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
    int startPoint[2] = { 50, 50 };
    int end[2] = { 790, 790 };

    // Generation counter
    int generation = 0;
    int mostFitCar;
};

#endif
