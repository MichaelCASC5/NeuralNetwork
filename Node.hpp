/**
 * Created by Michael Calle, Allison Lee, Angus Hu on December 27, 2023
*/

#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <vector>
#include <random>

class Node{
private:
    double value_;
    double bias_;
    std::vector<double> edges_;
public:
    //Constructors
    Node();
    Node(double value, double bias, std::vector<double> edges);
    Node(const Node& other);
    Node& operator=(const Node& other);
    ~Node();
    
    //Connection Constructor
    Node(int edgeNum);

    //Accessor methods
    double getValue() const;
    double getBias() const;
    std::vector<double> getEdges() const;

    //Mutator methods
    void setValue(double value);
    void setBias(double bias);
    void setEdges(std::vector<double> edges);

    //Neuron methods
    void linear(double d);
    void ReLU(double d);
    void LeakyReLU(double d);
    void mutate(double threshold);

    //Print
    void printNode() const;
};

#include "Node.cpp"
#endif