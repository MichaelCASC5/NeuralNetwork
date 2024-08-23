#pragma once

#ifndef DRIVER_HPP
#define DRIVER_HPP

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

class Driver
{
public:
    /**
     * Constructor
     */
    Driver();

    /**
     * Destructor
     */
    ~Driver();

    /**
     * Start the threaded game
     */
    void start();

    /**
     * Perform game logic
     */
    void loop();

    /**
     * Paint to screen
     */
    void paintComponent();

private:
    /**
     * Threading and window variables
     */
    sf::RenderWindow window;
    std::thread loopThread;
    std::mutex mutex;

    // Program running boolean
    bool runProgram;

    /**
     * GAME PRIVATE MEMBERS
     */
    std::chrono::steady_clock::time_point startTimer;

    std::vector<Car> cars;

    std::vector<Point> obstacles;
    bool obs[20][20] = {};

    int startPoint[2] = { 50, 50 };
    int end[2] = { 390, 390 };

    //Generation counter
    int generation = 0;
};

#endif
