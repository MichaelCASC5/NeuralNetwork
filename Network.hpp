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
        std::vector<std::vector<Node>> layers_;
    public:
        //Constructors
        Network(std::initializer_list<int> arr);

        //Accessor
        std::vector<std::vector<Node>>& getLayers();

        //Neural Network Functions
        void setLayerValues(int layerNum, std::vector<double> input);
        void forwardPassLayer(int layerNum);
        std::vector<double> forwardPropagation(std::vector<double> input);
};

#include "Network.cpp"
#endif