#include <iostream>
#include "Network.hpp"
#include "TicTacToe.hpp"
#include "Car.hpp"
#include <SFML/Graphics.hpp>

/*
    * PUBLIC VARS
*/
std::vector<Car> cars;

/*
    * SIMULATION LOGIC
*/
void loop () {
    int parentIndex = -1;

    //Iterate through all the cars in the vector and move them all
    for (int i = 0; i < cars.size(); i++) {
        cars[i].move();

        //Check to see if a car made it to the exit
        if(cars[i].getXPos() > 350 && cars[i].getXPos() <= 400 && cars[i].getYPos() > 350 && cars[i].getYPos() <= 400) {
            //Save the index of the car that made it to the exit
            parentIndex = i;
            break;
        }
    }

    if(parentIndex != -1) {
        Car parent = cars[parentIndex];
        for (int i = 0; i < cars.size(); i++) {
            cars[i] = parent;
            // cars[i].getNetwork().mutate(1);
            cars[i].mutate(0.1);

            cars[i].setXPos(50);
            cars[i].setYPos(50);
        }
    }

    // std::cout << cars.size() << std::endl;
}

int main() {
    //Use this upper section to train the network (there's a problem with reading files?)

    // Network network = {9, 11, 9};
    // // network.readFile("network.json");

    // for (int i = 0; i < 1000; i++) {
    //     network = tournament(network, 1024);

    //     if (i % 10 == 0) {
    //         std::cout << i << std::endl;
    //     }
    // }
    
    // network.writeFile("network.json");

    /*
        * ==== ==== ==== ==== *
    */
    // std::vector<double> input = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    // network.forwardPropagation(input);
    // std::vector<double> output = network.getOutputLayerValues();
    // network.printNetwork();
    // for (int i = 0; i < output.size(); i++) {
    //     std::cout << output[i] << " ";
    // }
    // std::cout << std::endl;
    // return 0;

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
    for (int i = 0; i < 500; i++) {
        Network network = {4, 6, 5};
        Car car(50, 50, network);

        cars.push_back(car);
    }



    /*
        * START SIMULATION ENVIRONMENT
    */
    while (window.isOpen()) {
        //SFML Window
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        /*
            * PERFORM LOGIC
        */
        loop();

        /*
            * DRAW THE CARS
        */
        //Clear window
        window.clear();

        //Draw each car
        for (int i = 0; i < cars.size(); i++) {
            cars[i].draw(window);
        }

        //Display the window
        window.display();
    }

    return 0;
}
