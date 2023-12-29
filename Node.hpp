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

    double edges_[];
public:
    //Accessor
    double getValue();
    double getBias();
    double getEdges();//I forgot the correct syntax for this. Just have it return the array. I think you need to return a pointer.
    str::string printNode();//Just prints out the information in the node

    //Mutator
    void setValue();
    void setBias();
    void setEdge(int arr[]);
};
#endif