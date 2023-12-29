/**
 * Created by Michael Calle, Allison Lee, Angus Hu on December 27, 2023
*/

#ifndef NEURAL_NETWORK_NODE_HPP
#define NEURAL_NETWORK_NODE_HPP

#include <iostream>
#include <vector>

class Node{
private:
    double value_;
    std::vector<double> edges_;
    int position_;
    int layer_;
public:
    bool addNode();
    bool removeNode();
};
#endif