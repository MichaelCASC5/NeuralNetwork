#pragma once
/**
 * Created by Michael Calle, Allison Lee, Angus Hu on December 27, 2023
*/

#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <iostream>
#include <vector>
#include <initializer_list>
#include <algorithm>
#include <fstream>
#include <random>
#include <cstdlib>
#include <string>

#include "Node.h"

class Network {
private:
    //A 2D vector that represents the layers of the network.
    std::vector<std::vector<Node>> layers_;
public:
    /**
        CONSTRUCTORS
    */

    /**
        * DEFAULT CONSTRUCTOR
            *
            * @post: initializes a default network, with 2 layers each consisting of a vector of one node
            *        Node values are default
    */
    Network();

    /**
        * PARAMETERIZED CONSTRUCTOR
    */
    Network(std::initializer_list<int> arr);

    /**
        COPY CONSTRUCTOR
    */
    Network(const Network& other);

    /**
        COPY ASSIGNMENT OPERATOR
    */
    Network& operator=(const Network& other);

    /**
        DESTRUCTOR
    */
    ~Network();



    /**
        ACCESSOR METHODS
    */
    /**
        * Returns the size of the 2D vector layers_
    */
    int size() const;

    /**
        * Returns an address to layers_, which is the entire network (a 2D vector)
    */
    std::vector<std::vector<Node>>& getLayers();



    /**
        NEURAL NETWORK FUNCTIONS
    */
    /**
        * Performs a min-max normalization on a given layer.
    */
    void minmaxnormalize(int layerNum);

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
        * Returns the values of all the nodes of the output layer as a vector of doubles.
    */
    std::vector<double> getOutputLayerValues();

    /**
        * Gives a softmax probability distribution of all the given layer's nodes' values as a vector of doubles.
    */
    std::vector<double> softmax(int layerNum);

    /**
        * Forward propagates an input through the network and returns the softmaxed values of the output layer nodes.
    */
    std::vector<double> forwardPropagation(std::vector<double> input);

    /**
        * Mutates the weights and biases of every node in a specified layer by a certain threshold
    */
    void mutateLayer(int layerNum, double threshold);

    /**
        * Mutates the weights and biases of every node in the network by a certain threshold
    */
    void mutate(double threshold);



    /**
        * PRINT METHODS
    */
    /**
        * Print a specified layer
    */
    void printLayer(int layerNum) const;

    /**
        * Print the entire network
    */
    void printNetwork() const;



    /**
        * FILE METHODS
    */
    /**
        * Reads a neural network from JSON
    */
    void readFile(std::string fileName);

    /**
        * Writes a neural network from JSON
    */
    void writeFile(std::string fileName);
};

#endif

