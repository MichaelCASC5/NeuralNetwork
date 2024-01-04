#include <iostream>
#include "Network.hpp"
#include "TicTacToe.hpp"

Network tournament(Network & network, int child) {
    std::vector<Network> population;

    for (int i = 0; i < child; i++) {
        Network copy = network;
        copy.mutate(0.01);

        population.push_back(copy);
    }

    while (population.size() > 1) {
        for (int i = 0; i < population.size() / 2; i++) {
            TicTacToe board;

            Network * net1 = &population[i];
            Network * net2 = &population[i + (population.size() / 2)];

            if (!board.play(*net1, *net2)) {
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
    //Use this upper section to train the network (there's a problem with reading files over 10k generations?)

    // Network network = {9, 11, 9};
    // // network.readFile("network.json");

    // for (int i = 0; i < 10000; i++) {
    //     network = tournament(network, 32);

    //     if (i % 100 == 0) {
    //         std::cout << i << std::endl;
    //     }
    // }
    
    // network.writeFile("network.json");

    /*
        * ==== ==== ==== ==== *
    */

    //Use this lower section to play against the network

    Network network;
    network.readFile("network.json");

    TicTacToe board;
    std::cout << board.onePlayerGame(network) << std::endl;



    return 0;
}
