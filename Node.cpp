/**
 * Created by Michael Calle, Allison Lee, Angus Hu on December 27, 2023
*/

Node::Node():value_(0), bias_(0) {
    edges_ = {};
}

Node::Node(double value, double bias, std::vector<double> edges):Node() {
    value_ = value;
    bias_ = bias;
    edges_ = edges;
}

/**
    * Connection constructor that connects the node to the rest of the network.
    *
    * This gives the node the amount of edges it needs to connect to the nodes in the next layer.
    * The number of edges that it requires is given in the parameter. This constructor
    * also randomizes all necessary values of the node, to prepare for training.
    * This constructor is used when filling each layer with nodes during Network creation.
    * 
    * @param edgeNum The number of edges that are required to connect to every node of the next layer.
*/
Node::Node(int edgeNum){
    //THE VALUES ARE NOT YET RANDOMIZED
    value_ = 0;
    bias_ = 0;

    //Set edges_ to the proper amont of edges needed with their values.
    std::vector<double> edges(edgeNum, 0);
    edges_ = edges;
}

double Node::getValue() const {
    return value_;
}

double Node::getBias() const {
    return bias_;
}

std::vector<double> Node::getEdges() const { 
    return edges_;
}


//Mutator
void Node::setValue(double value) {
    value_ = value;
}
void Node::setBias(double bias) {
    bias_ = bias;
}
void Node::setEdge(std::vector<double> edges) {
    edges_ = edges;
}

//Print
void Node::printNode() const {
    std::cout << "Value: "  << value_ << "\nBias: " << bias_ << "\nEdges: ";
    for (int i = 0; i < edges_.size(); i++){
        std::cout << edges_[i] << " ";
    }
    std::cout << std::endl;
}