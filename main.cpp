#include <iostream>
#include <fstream>
#include "Network.hpp"
#include "TicTacToe.hpp"

int main() {
    std::ifstream file("network.json");
    
    Network network = {1, 1, 1};
    network.printNetwork();
    network.readFile(file);

    network.printNetwork();
    
    return 0;
}
