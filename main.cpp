#include <iostream>
#include "Network.hpp"
#include "TicTacToe.hpp"

int main() {
    Network network;

    network.readFile("output.json");

    network.printNetwork();
    
    std::vector<double> input = {1920, 1080};
    std::vector<double> output = network.forwardPropagation(input);

    network.printNetwork();

    return 0;
}
