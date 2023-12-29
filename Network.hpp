/**
 * Created by Michael Calle, Allison Lee, Angus Hu on December 27, 2023
*/

#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <iostream>
#include "Node.hpp"

class Network{
    private:
        Node layer_[1];
    public:
        //Default Constructor
        Network();
};

#include "Network.cpp"

#endif