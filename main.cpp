#include <iostream>
#include "Network.hpp"
#include "TicTacToe.hpp"

Network tournament(Network & network, int child) {
    //Test vector
    // std::vector<double> input = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<Network> population;

    for (int i = 0; i < child; i++) {
        Network copy = network;

        //Don't mutate parent
        // if (i > 0) {
            copy.mutate(0.1);
        // }

        population.push_back(copy);
    }

    while (population.size() > 1) {
        for (int i = 0; i < population.size() / 2; i++) {
            TicTacToe board;

            Network * net1 = &population[i];
            Network * net2 = &population[i + (population.size() / 2)];

            //Test vectors
            // std::vector<double> output1 = net1->forwardPropagation(input);
            // std::vector<double> output2 = net2->forwardPropagation(input);
            if (!board.play(*net1, *net2)) {

            // if (output1[2] < output2[2]) {
                std::swap(*net1, *net2);
            }
        }

        //Keeping only first half (winners) of population
        size_t const midpoint = population.size() / 2;
        population.erase(population.begin() + midpoint, population.end());
    }

    return population[0];
}

int main() {
    //Use this upper section to train the network (there's a problem with reading files?)

    Network network = {9, 11, 9};
    // network.readFile("network.json");

    for (int i = 0; i < 100; i++) {
        network = tournament(network, 1024);

        if (i % 1 == 0) {
            std::cout << i << std::endl;
        }
    }
    
    network.writeFile("network.json");

    /*
        * ==== ==== ==== ==== *
    */

    //Use this lower section to play against the network

    // Network network;
    // network.readFile("network.json");

    // TicTacToe board;
    // std::cout << board.onePlayerGame(network) << std::endl;



    return 0;
}
