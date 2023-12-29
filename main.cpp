#include <iostream>
#include "Network.hpp"

int main() {
    //Initialization
    Network network({27,11,9});

    //Getting each vector
    std::cout << network.getLayers()[0].size() << std::endl;
    std::cout << network.getLayers()[1].size() << std::endl;
    std::cout << network.getLayers()[2].size() << std::endl;

    //Printing a single node
    Node * n = &(network.getLayers()[0][0]);
    n->setBias(1024);
    n->printNode();

    return 0;
}