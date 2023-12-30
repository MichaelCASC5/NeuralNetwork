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

    //Connection Constructor
    Node(int edgeNum);

    //Accessor
    double getValue() const;
    double getBias() const;
    std::vector<double> getEdges() const;

    //Mutator
    void setValue(double value);
    void setBias(double bias);
    void setEdges(std::vector<double> edges);

    //Print
    void printNode() const;
};

#include "Node.cpp"
#endif