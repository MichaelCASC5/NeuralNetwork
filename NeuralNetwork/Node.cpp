/**
 * Created by Michael Calle, Allison Lee, Angus Hu on December 27, 2023
*/
#include "Node.h"
/**
    * CONSTRUCTORS
*/

/**
    * Default Constructor
    *
    * @post: Sets all values to 0 and edges_ to empty
*/
Node::Node() :value_(0), bias_(0) {
    edges_ = {};
}

/**
    * Parameterized Constructor
    *
    * @param value Sets value_
    * @param bias Sets bias_
    * @param edges Is a std::vector<double> and sets edges_
    * @post: sets all values to input and edges_ to a vector
*/
Node::Node(double value, double bias, std::vector<double> edges) :Node() {
    value_ = value;
    bias_ = bias;
    edges_ = edges;
}

/**
 * COPY CONSTRUCTOR
 *
 * @param: const reference to another node
 * @post: sets all values to other's values
*/
Node::Node(const Node& other) {
    value_ = other.value_;
    bias_ = other.bias_;
    edges_ = other.edges_;
}

/**
 * COPY ASSIGNMENT OPERATOR
 *
 * @param: const reference to another node
 * @post: assigns all values to other's values
 * @return: this node
*/
Node& Node::operator=(const Node& other) {
    value_ = other.value_;
    bias_ = other.bias_;
    edges_ = other.edges_;
    return *this;
}

/**
    * DESTRUCTOR
*/
Node::~Node() {}

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
Node::Node(int edgeNum) {
    //Generating random device to seed the RNG
    std::random_device rd;
    std::mt19937 gen(rd());//Mersenne Twister
    std::uniform_real_distribution<double> dis(-1.0, 1.0);//range [-1,1)

    //Setting values to random doubles
    value_ = 0;
    bias_ = dis(gen);

    //Populate edges with random doubles
    std::vector<double> edges;
    for (int i = 0; i < edgeNum; i++) {
        edges.push_back(dis(gen));
    }

    //Set edges_ to this vector
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
void Node::setEdges(std::vector<double> edges) {
    edges_ = edges;
}

/**
    * NEURON METHODS
*/
/**
    * LINEAR activation function
    *
    * Accepts an input and assigns the value_ to the input
    *
    * @param d A double of the supposed input to activate the node
*/
void Node::linear(double d) {
    value_ = d;
}

/**
    * RELU activation function
    *
    * Accepts an input and assigns the value_ to the maximum of
    * either zero or the input itself.  max(0, input)
    * Essentially, if the input is less than 0, assign it to 0
    * if the input is greater than 0, leave it as it is.
    *
    * @param d A double of the supposed input to activate the node
*/
void Node::ReLU(double d) {
    value_ = std::max(0.0, d);
}

/**
    * LEAKY RELU activation function
    *
    * Accepts an input and assigns the value_ to the maximum of
    * either zero or the input times a small linear component, e.g., max(0.01*input, input)
    *
    * @param d A double of the supposed input to activate the node
*/
void Node::LeakyReLU(double d) {
    value_ = std::max(0.001 * d, d);
}

/**
    * Mutates the weights and biases of a node by a bounded random amount
    *
    * The threshold represents the upper positive and lower negative bounds of a random
    * double. Such a random number will be added both to each edge and to the bias.
    *
    * @param threshold The upper positive and lower negative bounds of a random double.
*/
void Node::mutate(double threshold) {
    //Random number generator, bounds are -threshold and threshold
    std::random_device rd;
    std::mt19937 gen(rd());//Mersenne Twister
    std::uniform_real_distribution<double> dis(-threshold, threshold);

    //Iterate through the edges, for each one add the random double
    for (int i = 0; i < edges_.size(); i++) {
        edges_[i] = edges_[i] + dis(gen);
    }

    //Add the random double the the bias_
    bias_ = bias_ + dis(gen);
}

/**
    PRINT METHODS
*/

/**
    * Prints the information in the node to console.
*/
void Node::printNode() const {
    std::cout << "Value: " << value_ << "\nBias: " << bias_ << "\nEdges: ";
    for (int i = 0; i < edges_.size(); i++) {
        std::cout << edges_[i] << " ";
    }
    std::cout << std::endl;
}
