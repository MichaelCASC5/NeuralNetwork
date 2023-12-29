/**
 * Created by Michael Calle, Allison Lee, Angus Hu on December 27, 2023
*/

/**
    * CONSTRUCTORS
*/
/**
    * Default Constructor
    *
    * Sets all values to 0 and edges_ to empty
*/
Node::Node():value_(0), bias_(0) {
    edges_ = {};
}

/**
    * Parameterized Constructor
    *
    * Sets all values to input and edges_ to a vector
    *
    * @param value Sets value_
    * @param bias Sets bias_
    * @param edges Is a std::vector<double> and sets edges_
*/
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

/**
    * ACCESSOR METHODS
*/
/**
    * Returns value_
    * @return value_
*/
double Node::getValue() const {
    return value_;
}
/**
    * Returns bias_
    * @return bias_
*/
double Node::getBias() const {
    return bias_;
}
/**
    * Returns edges_
    * @return std::vector<double> edges_
*/
std::vector<double> Node::getEdges() const { 
    return edges_;
}

/**
    * MUTATOR METHODS
*/
/**
    * Sets value_
    * @param value Sets value_
*/
void Node::setValue(double value) {
    value_ = value;
}
/**
    * Sets bias_
    * @param value Sets bias_
*/
void Node::setBias(double bias) {
    bias_ = bias;
}
/**
    * Sets std::vector<double> edges_
    * @param value Sets std::vector<double> edges_
*/
void Node::setEdge(std::vector<double> edges) {
    edges_ = edges;
}

/**
    EXTRA FUNCTIONS
*/
/**
    * Prints the information in the node to console.
*/
void Node::printNode() const {
    std::cout << "Value: "  << value_ << "\nBias: " << bias_ << "\nEdges: ";
    for (int i = 0; i < edges_.size(); i++){
        std::cout << edges_[i] << " ";
    }
    std::cout << std::endl;
}