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
        //A 2D vector that represents the layers of the network.
        std::vector<std::vector<Node>> layers_;
    public:
        /**
            CONSTRUCTORS
        */
        Network(std::initializer_list<int> arr);

        /**
            ACCESSOR METHODS
        */
        std::vector<std::vector<Node>>& getLayers();

        /**
            NEURAL NETWORK FUNCTIONS
        */
        /**
            * Sets the values of all the nodes of a specified layer to the elements of a vector of doubles.
        */
        void setLayerValues(int layerNum, std::vector<double> input);

        /**
            * Performs a single forward pass on all the nodes of a specified layer by combining rear-connected weights and values.
        */
        void forwardPassLayer(int layerNum);

        /**
            * Gets the dot product of the weights and values of a specified layer, in regards to a particular node ahead.
        */
        double getDotProduct(int layerNum, int edge);

        /**
            * Returns the values of all the nodes of a specified layer as a vector of doubles.
        */
        std::vector<double> getLayerValues(int layerNum);

        /**
            * Forward propagates an input through the network and returns the softmaxed values of the output layer nodes.
        */
        //NOTICE: SOFTMAX FUNCTION HAS NOT BEEN IMPLEMENTED YET. THE VALUES ARE RETURNED AS-IS.
        std::vector<double> forwardPropagation(std::vector<double> input);

        /**
            * PRINT METHODS
        */
        void printLayer(int layerNum) const;
};

#include "Network.cpp"
#endif