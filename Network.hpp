/**
 * Created by Michael Calle, Allison Lee, Angus Hu on December 27, 2023
*/

#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <iostream>
#include <vector>
#include <initializer_list>
#include "Node.hpp"

class Network{
    private:
        std::vector<std::vector<int>> layers_;
    public:
        //Constructors
        Network(std::initializer_list<int> arr);

        //Accessor
        std::vector<std::vector<int>> getLayers();
};

#include "Network.cpp"
#endif