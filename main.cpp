#include "Network.hpp"
#include "TicTacToe.hpp"
#include "Car.hpp"
#include "Point.hpp"
#include <iostream>
#include <chrono>
#include <SFML/Graphics.hpp>

/*
    * PUBLIC VARS
*/
std::vector<Car> cars;
// std::vector<std::vector<bool>> obstacles(400, std::vector<bool>(400, false));
std::vector<Point> obstacles;
//Need to refractor this to points
int start[] = {50, 50};
int end[] = {390, 390};

/*
    * SIMULATION LOGIC
*/
template <typename T>
void loop (T & startTimer, sf::RenderTarget& window) {

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
        cars[i].move(obstacles, window);

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
    if (inactiveCount == cars.size() || duration > 20000) {
        // std::cout << "ALL INACTIVE" << std::endl;
        
        int saveShortest = cars[0].getDistanceTo(end);;

        //If all cars are inactive, find which one is closer to the finish
        for (int i = 1; i < cars.size(); i++) {
            //Calculate distance to the finish
            int dist = cars[i].getDistanceTo(end);

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
                cars[i].mutate(0.1);
            }

            // cars[i].setXPos(start[0]);
            // cars[i].setYPos(start[1]);
            cars[i].reset(start);
            startTimer = std::chrono::steady_clock::now();
        }
    }
}

int main() {
    /*
        * SETUP WINDOW
    */
    // sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "SFML works!", sf::Style::Fullscreen);
    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!", sf::Style::Default);

    //Enable VSync
    window.setVerticalSyncEnabled(true);
    
    //Get desktop video data
    auto desktop = sf::VideoMode::getDesktopMode();

    //Display window before obtaining desktop
    window.display();

    //Short delay to allow window to be positioned properly
    sf::sleep(sf::milliseconds(100));

    //Center Screen
    sf::Vector2i position(desktop.width/2 - window.getSize().x/2, desktop.height/2 - window.getSize().y/2);
    window.setPosition(position);

    

    /*
        * SETUP SIMULATION
    */
    for (int i = 0; i < 20; i++) {
        Network network = {5, 6, 4};
        Car car(start[0], start[1], 0, 0, 1, network);

        cars.push_back(car);
    }
    
    //Start timer
    auto startTimer = std::chrono::steady_clock::now();



    /*
        * START SIMULATION ENVIRONMENT LOOP
    */
    while (window.isOpen()) {
        //SFML Window
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
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
            obstacles.push_back(obstacle);
        }

        /**
            * PERFORM LOGIC
        */
        // loop(window);

        /**
            * DRAW
        */
        //Clear window
        window.clear();

        loop(startTimer, window);

        //Draw obstacles
        for (int i = 0; i < obstacles.size(); i++) {
            obstacles[i].draw(window);
        }
        window.draw(cursor);

        //Draw each car
        for (int i = 0; i < cars.size(); i++) {
            cars[i].draw(window);
            // cars[i].radar(0, obstacles, window);
        }

        //Display the window
        window.display();
    }

    return 0;
}
