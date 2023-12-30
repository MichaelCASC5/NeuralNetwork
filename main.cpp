#include <iostream>
#include "Network.hpp"
#include "TicTacToe.hpp"

int main() {
    //Initialization
    Network network({27,11,9});

    //Getting each vector
    std::cout << network.getLayers()[0].size() << std::endl;
    std::cout << network.getLayers()[1].size() << std::endl;
    std::cout << network.getLayers()[2].size() << std::endl;

    //Testing propagation
    std::vector<double> input = {5,1,2,4,3,3,9};
    network.forwardPropagation(input);

    //Printing a single node
    Node * n = &(network.getLayers()[0][0]);
    // n->setBias(1024);
    n->printNode();

    Node * n1 = &(network.getLayers()[0][1]);
    n1->printNode();

    return 0;
}