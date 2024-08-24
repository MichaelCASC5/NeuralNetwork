#include "CarSim.h"

CarSim::CarSim()
{
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

CarSim::~CarSim() {}

/**
 * All simulation logic
 */
void CarSim::logic(sf::RenderWindow &window)
{
    //Index of the winning car to be the parent. Set to -1 to indicate no winner
    int parentIndex = -1;

    //Count the time passed since the generation started
    auto finishTimer = std::chrono::steady_clock::now();
    auto numberTimer = std::chrono::duration_cast<std::chrono::milliseconds> (finishTimer - startTimer);
    auto duration = numberTimer.count();

    //Iterate through all the cars in the vector and move them all
    for (int i = 0; i < cars.size(); i++) {
        cars[i].move(obs, window);

        //Check to see if a car made it to the exit
        if (cars[i].getDistanceTo(end) < 20) {
            //Save the index of the car that made it to the exit
            parentIndex = i;
            break;
        }
    }

    //Check if all the cars in the vector are inactive
    if (duration > 10000) {

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

            cars[i].reset(startPoint);
            startTimer = std::chrono::steady_clock::now();
        }

        generation++;
    }
}

/**
 * Drawing the game
 */
void CarSim::paint(sf::RenderWindow &window)
{
    // Draw obstacles
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            if (obs[i][j]) {
                // Set the diameter of the circle
                sf::CircleShape shape(10.f);

                // Set the color of the circle
                shape.setFillColor(sf::Color::Red);

                // Set the position of the circle
                sf::Vector2f position = { (float)(i * 20), (float)(j * 20) };
                shape.setPosition(position);

                // Draw the circle to the target window
                window.draw(shape);
            }
        }
    }

    //Draw each car
    for (int i = 0; i < cars.size(); i++) {
        cars[i].draw(window);
    }
}

/**
 * Mouse events
 */
void CarSim::mouseEvents(sf::RenderWindow& window)
{
    //sf::CircleShape cursor(10.f);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        //Set the color of the circle
        //cursor.setFillColor(sf::Color::Green);

        //Set the position of the circle
        //cursor.setPosition(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

        //Creating obstacle
        Point obstacle(static_cast<int>(mousePos.x), static_cast<int>(mousePos.y));
        obs[static_cast<int>(mousePos.x) / 20][static_cast<int>(mousePos.y) / 20] = 1;
    }
}
