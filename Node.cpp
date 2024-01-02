/**
 * Created by Michael Calle, Allison Lee, Angus Hu on December 27, 2023
*/

/**
    * CONSTRUCTORS
*/

/**
    * Default Constructor
    *
    * @post: Sets all values to 0 and edges_ to empty
*/
Node::Node():value_(0), bias_(0) {
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
Node::Node(double value, double bias, std::vector<double> edges):Node() {
    value_ = value;
    bias_ = bias;
    edges_ = edges;
}

/**
 * COPY CONSTRUCTOR
 *
 * @param: const reference to another node
 * @post: sets all values to another_node's values
*/
Node::Node(const Node& another_node){
    value_ = another_node.value_;
    bias_ = another_node.bias_;
    edges_ = another_node.edges_;
}

/**
 * COPY ASSIGNMENT OPERATOR
 *
 * @param: const reference to another node
 * @post: assigns all values to another_node's values
 * @return: this node
*/
Node& Node::operator=(const Node& another_node){
    value_ = another_node.value_;
    bias_ = another_node.bias_;
    edges_ = another_node.edges_;
    return *this;
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
    * RELU activation function
    *
    * Accepts an input and assigns the value_ to the maximum of
    * either zero or the input itself.  max(0, input)
    * Essentially, if the input is less than 0, assign it to 0
    * if the input is greater than 0, leave it as it is.
    *
    * @param d A double of the supposed input to activate the node
*/
void Node::RELU(double d) {
    value_ = std::max(0.0, d);
}

/**
    PRINT METHODS
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