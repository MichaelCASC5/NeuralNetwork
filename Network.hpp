/**
 * Created by Michael Calle, Allison Lee, Angus Hu on December 27, 2023
*/

#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <iostream>
#include <vector>
#include "Node.hpp"

class Network{
    private:
        int * layer_;
    public:
        //Constructors
        Network(int n);

        //Accessor
        int * getLayer();
};

#include "Network.cpp"
#endif