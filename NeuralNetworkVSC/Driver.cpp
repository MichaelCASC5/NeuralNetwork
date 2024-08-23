/**
 * COMPUTER SCIENCE 49900 MAJOR CAPSTONE HUNTER 2024
 *
 * 2D MONSTER GAME
 * CREATED BY ANTON, MICHAEL
 * 01/30/24 Spring Semester
 *
 */

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

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

    /**
     * INITIAL GAME LOGIC
     */
     /*
         * SETUP SIMULATION
     */
    for (int i = 0; i < 1000; i++) {
        Network network = { 5, 6, 4 };
        Car car(startPoint[0], startPoint[1], 45, 0, 1, network);

        cars.push_back(car);
    }

    // Start timer
    startTimer = std::chrono::steady_clock::now();
}

/**
 * Destructor lets loop() loopThread to catch up and close with everything else
 */
Driver::~Driver()
{
    loopThread.join();
}

/**
 * Start the program
 *
 * This is the jumping-off point where the threaded game logic and screen
 * drawing will begin.
 */
void Driver::start()
{
    /**
     * Launch paintComponent after threading loop()
     * https://www.reddit.com/r/cpp_questions/comments/p4z5nv/invalid_use_of_nonstatic_member_function/
     * https://stackoverflow.com/questions/266168/simple-example-of-threading-in-c
     */
    loopThread = std::thread(&Driver::loop, this);
    paintComponent();
}

/**
 * Performs all game logic
 *
 * This consists of a while loop that works so long as runProgram is true
 * The loop is threaded so that it runs alongside the paintComponent
 * All relevant game logic is run from here.
 * At the bottom a thread sleep causes the loop to run at 60 updates per second
 */
void Driver::loop()
{
    while (runProgram)
    {
        /**
         * SFML WINDOW
         */
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                runProgram = false;
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                runProgram = false;
                window.close();
            }
        }

        /**
         * MOUSE INPUT
         */
        sf::CircleShape cursor(10.f);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            //Set the color of the circle
            cursor.setFillColor(sf::Color::Green);

            //Set the position of the circle
            cursor.setPosition(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

            //Creating obstacle
            Point obstacle(static_cast<int>(mousePos.x), static_cast<int>(mousePos.y));
            // obstacles.push_back(obstacle);
            obs[static_cast<int>(mousePos.x) / 20][static_cast<int>(mousePos.y) / 20] = 1;
            // std::cout << static_cast<int>(mousePos.x) << ", " << static_cast<int>(mousePos.y) << std::endl;
        }

        /**
         * GAME LOGIC
         */

         //Index of the winning car to be the parent. Set to -1 to indicate no winner
        int parentIndex = -1;

        //Count the time passed since the generation started
        auto finishTimer = std::chrono::steady_clock::now();
        auto numberTimer = std::chrono::duration_cast<std::chrono::milliseconds> (finishTimer - startTimer);
        auto duration = numberTimer.count();
        // if (duration / 10 == 0)
            // std::cout << duration << " " << cars.size() << std::endl;

        //Count the number of cars in the vector that are inactive/have hit an obstacle
        int inactiveCount = 0;

        //Iterate through all the cars in the vector and move them all
        for (int i = 0; i < cars.size(); i++) {
            cars[i].move(obs, window);

            //If the car is inactive, add one to the inactive cars counter
            if (!cars[i].getActive()) {
                inactiveCount++;
            }

            //Check to see if a car made it to the exit
            if (cars[i].getDistanceTo(end) < 20) {
                //Save the index of the car that made it to the exit
                parentIndex = i;
                break;
            }
        }

        //Check if all the cars in the vector are inactive
        if (inactiveCount == cars.size() || duration > 10000) {
            // std::cout << "ALL INACTIVE" << std::endl;
            if (duration > 20000) {
                std::cout << "TIME UP" << std::endl;
            }

            double saveShortest = cars[0].getDistanceTo(end);
            parentIndex = 0;

            //If all cars are inactive or time is up, find which one is closer to the finish
            for (int i = 1; i < cars.size(); i++) {
                //Calculate distance to the finish
                double dist = cars[i].getDistanceTo(end);

                //If the distance is shorter than the shortest recorded thus far, save it
                if (dist < saveShortest) {
                    saveShortest = dist;

                    //Set a new parent
                    parentIndex = i;
                }
            }
        }

        if (parentIndex != -1) {
            Car parent = cars[parentIndex];
            for (int i = 0; i < cars.size(); i++) {
                cars[i] = parent;

                //Don't mutate parent
                if (i > 0) {
                    //Each generation the mutation threshold lowers
                    double threshold = 1 * pow(0.75, generation);

                    //Threshold limit
                    if (threshold < 0.001) {
                        threshold = 0.001;
                    }

                    //Mutate generationally only a certain proportion of the cars, the rest undergo more severe mutation
                    if (i < (int)(cars.size() * 0.95)) {
                        cars[i].mutate(threshold);
                    }
                    else {
                        cars[i].mutate(1);
                    }
                }

                // cars[i].setXPos(start[0]);
                // cars[i].setYPos(start[1]);
                cars[i].reset(startPoint);
                startTimer = std::chrono::steady_clock::now();
            }
            generation++;
        }

        // Sleep the thread to allow for 60 updates per second logic
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60)); // 60 ups
    }
}

/**
 * Performs all rendering
 *
 * This consists of a while loop that continually renders onto the canvas
 * The condition is so long as runProgram is true, and so long as the
 * window is open.
 * During execution a mutex locks and unlocks the thread while drawing is
 * happening to ensure no thread can access this code at the same time.
 */
void Driver::paintComponent()
{
    while (window.isOpen() && runProgram)
    {
        // Prevent other threads from simultaneously accessing the window
        mutex.lock();

        // Clear the screen to black
        window.clear(sf::Color::Black);

        /**
         * DRAWING THE GAME
         */

         //Draw obstacles
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                // obstacles[i].draw(window);

                if (obs[i][j]) {
                    //Set the diameter of the circle
                    sf::CircleShape shape(10.f);

                    //Set the color of the circle
                    shape.setFillColor(sf::Color::Red);

                    //Set the position of the circle
                    sf::Vector2f position = { (float)(i * 20), (float)(j * 20) };
                    shape.setPosition(position);

                    //Draw the circle to the target window
                    window.draw(shape);
                }
            }
        }

        // loop(startTimer, window);

        //Draw each car
        for (int i = 0; i < cars.size(); i++) {
            cars[i].draw(window);
        }

        /**
         * END DRAWING GAME
         */


         // Display the window
        window.display();

        // Unlock the mutex
        mutex.unlock();

        // Sleep the loop to allow for X frames per second rendering
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60)); // 60 fps
    }
}
