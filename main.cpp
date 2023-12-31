#include <iostream>
#include "Network.hpp"
#include "TicTacToe.hpp"

int main() {
    //Initializing neural network
    Network network = {3,2,3};

    //Printing the start state of the network before input
    for (int i = 0; i < network.getLayers().size(); i++) {
        std::cout << "\n\nLayer: " << i << " Size: " << network.getLayers()[i].size() << std::endl;
        network.printLayer(i);
    }

    //Test node
    // Node * n = &(network.getLayers()[0][0]);
    // n->setBias(1024);
    // n->printNode();

    //Input and Output
    std::vector<double> input = {1024,1920,1080};
    std::vector<double> output = network.forwardPropagation(input);

    //Printing the final state of the network after output
    for (int i = 0; i < network.getLayers().size(); i++) {
        std::cout << "\n\nLayer: " << i << " Size: " << network.getLayers()[i].size() << std::endl;
        network.printLayer(i);
    }

    //Printing the output
    std::cout << "\nOutput: " << std::endl;
    for (int i = 0; i < output.size(); i++) {
        std::cout << output[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}