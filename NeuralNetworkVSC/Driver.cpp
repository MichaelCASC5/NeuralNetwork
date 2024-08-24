#include "Driver.h"

 /**
  * Constructor
  *
  * This sets up the SFML window and all relevant information.
  * At the bottom the initial game logic that isn't meant to be looped
  * continuously is placed.
  */
Driver::Driver() : window(sf::VideoMode(400, 400), "Neural Network", sf::Style::Default), runProgram(true)
{
    // Enable VSync
    window.setVerticalSyncEnabled(true);

    // Get desktop video data
    auto desktop = sf::VideoMode::getDesktopMode();

    // Display window before obtaining desktop
    window.display();

    // Short delay to allow window to be positioned properly
    sf::sleep(sf::milliseconds(100));

    // Center Screen
    sf::Vector2i position(desktop.width/2 - window.getSize().x/2, desktop.height/2 - window.getSize().y/2);
    window.setPosition(position);
}

/**
 * Destructor lets loop() logicThread to catch up and close with everything else
 */
Driver::~Driver()
{
    logicThread.join();
}

/**
 * Handles the game logic
 */
void Driver::logic()
{
    carSim.logic(window);
}

/**
 * Handles the game rendering
 */
void Driver::paint()
{
    carSim.paint(window);
}

/**
 * Handles mouse events
 */
void Driver::mouseEvents()
{
    carSim.mouseEvents(window);
}

/**
 * Contains all game logic
 *
 * This consists of a while loop that works so long as runProgram is true
 * The loop is threaded so that it runs alongside the paintComponent
 * All relevant game logic is run from here.
 * At the bottom a thread sleep causes the loop to run at 60 updates per second
 */
void Driver::logicContainer()
{
    while (runProgram)
    {
        // Prevent other threads from simultaneously accessing the logic thread
        mutex.lock();

        // SFML Window
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                runProgram = false;
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                runProgram = false;
                window.close();
            }
        }

        // Mouse input
        mouseEvents();

        // Game logic
        logic();

        // Unlock the mutex
        mutex.unlock();

        // Sleep the thread to allow for 60 updates per second logic
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60)); // 60 ups
    }
}

/**
 * Contains all rendering
 *
 * This consists of a while loop that continually renders onto the canvas
 * The condition is so long as runProgram is true, and so long as the
 * window is open.
 * During execution a mutex locks and unlocks the thread while drawing is
 * happening to ensure no thread can access this code at the same time.
 */
void Driver::paintContainer()
{
    while (window.isOpen() && runProgram)
    {
        // Prevent other threads from simultaneously accessing the window
        mutex.lock();

        // Clear the screen to black
        window.clear(sf::Color::Black);

        // Draw game
        paint();

        // Display the window
        window.display();

        // Unlock the mutex
        mutex.unlock();

        // Sleep the loop to allow for X frames per second rendering
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60)); // 60 fps
    }
}

/**
 * Start the program
 *
 * This is the jumping-off point where the threaded game logic and screen
 * drawing will begin.
 */
void Driver::start()
{
    // Launch paintContainer after threading logicContainer()
    logicThread = std::thread(&Driver::logicContainer, this);
    paintContainer();
}
