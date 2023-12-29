/**
 * Created by Michael Calle, Allison Lee, Angus Hu on December 27, 2023
*/

#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <vector>

class Node{
private:
    double value_;
    double bias_;
    std::vector<double> edges_;
public:
    //Constructors
    Node();
    Node(double value, double bias, std::vector<double> edges);

    //Accessor
    double getValue() const;
    double getBias() const;
    std::vector<double> getEdges() const;//I forgot the correct syntax for this. Just have it return the array. I think you need to return a pointer.
    void printNode() const;//Just prints out the information in the node

    //Mutator
    void setValue(double value);
    void setBias(double bias);
    void setEdge(std::vector<double> edges);
};

#include <Node.cpp>
#endif