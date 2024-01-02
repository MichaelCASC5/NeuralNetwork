#include <iostream>
#include "Network.hpp"
#include "TicTacToe.hpp"

int main() {
    //Initializing neural network
    Network network = {3,2,3};

    //Printing the start state of the network before input
    network.printNetwork();

    //Input and Output
    std::vector<double> input = {1024,1920,1080};
    std::vector<double> output = network.forwardPropagation(input);

    //Printing the final state of the network after output
    network.printNetwork();

    //Test node
    // Node * n = &(network.getLayers()[0][0]);
    // n->setBias(1024);
    // n->printNode();

    //Printing the output
    std::cout << "\nOutput: " << std::endl;
    for (int i = 0; i < output.size(); i++) {
        std::cout << output[i] << " ";
    }
    std::cout << std::endl;

    TicTacToe board;
    std::cout << board.onePlayerGame() << std::endl;

    return 0;
}