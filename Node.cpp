/**
 * Created by Michael Calle, Allison Lee, Angus Hu on December 27, 2023
*/

#include "Node.hpp"

Node::Node():value_(0), bias_(0){
    edges_ = {};
}

Node::Node(double value, double bias, std::vector<double> edges):Node(){
    value_ = value;
    bias_ = bias;
    edges_ = edges;
}

double Node::getValue() const{
    return value_;
}

double Node::getBias() const{
    return bias_;
}

//I forgot the correct syntax for this. Just have it return the array. I think you need to return a pointer.
std::vector<double> Node::getEdges() const{ 
    return edges_;
}
    
void Node::printNode() const{ //Just prints out the information in the node
    std::cout << "Value: "  << value_ << "\nBias: " << bias_ << "\nEdges: ";
    for (int i = 0; i < edges_.size(); i++){
        std::cout << edges_[i] << " ";
    }
    std::cout << std::endl;
}

//Mutator
void Node::setValue(double value){
    value_ = value;
}
void Node::setBias(double bias){
    bias_ = bias;
}
void Node::setEdge(std::vector<double> edges){
    edges_ = edges;
}