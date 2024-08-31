#pragma once

#ifndef DRIVER_HPP
#define DRIVER_HPP

// C include
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

// Classes include
#include "CarSim.h"

// External library include
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

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
     * Game logic
     */
    void logic();

    /**
     * Game paint
     */
    void paint();

    /**
     * Handles mouse events
     */
    void mouseEvents();

    /**
     * Hosts the game logic
     */
    void logicContainer();

    /**
     * Hosts the painting
     */
    void paintContainer();

    /**
     * Start the threaded game
     */
    void start();

private:
    /**
     * Threading and window variables
     */
    sf::RenderWindow window;
    std::thread logicThread;
    std::mutex mutex;
    bool runProgram;

    /**
     * Simulation
     */
    CarSim carSim;
};

#endif
