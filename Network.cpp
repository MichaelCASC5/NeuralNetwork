/**
 * Created by Michael Calle, Allison Lee, Angus Hu on December 27, 2023
*/

#define e 2.7182818284590452353602874713527

/**
    * CONSTRUCTORS
*/
/**
    * Connects the neural network
    *
    * The input of the array is read as an initializer_list. e.g.({1,2,3}) or vector, etc.
    * This array is then traversed, and for each element a new vector of nodes of
    * that length is created. Each new vector of nodes is then pushed to the
    * layers_ 2D vector.
    * As each node is pushed to a layer, it builds as many edges as there are nodes
    * in the next layer.
    *
    * @param initializer_list Represents how many nodes should be in each layer of the network.
*/
Network::Network(std::initializer_list<int> arr) {
    //Get input size
    int arrSize = arr.size();

    //Convert intializer_list into an array for ease of use.
    //  The ability to see one element ahead is necessary.
    int* input = new int[arrSize];
    std::copy(arr.begin(), arr.end(), input);

    //For each element create vector of that length and push that vector to layers_
    for (int i = 0; i < arrSize; i++) {
        //For each node added to a layer the connection constructor will connect the node
        std::vector<Node> nodes;

        //j < input[i]  Push as many nodes into the layer as was specified in the input
        for (int j = 0; j < input[i]; j++) {
            //Node(input[i+1])  This is a call to the connection constructor.
            //  Give the node as many edges as there are nodes in the next layer.
            nodes.push_back(Node(input[i+1]));
        }

        layers_.push_back(nodes);
    }

    //Deallocate
    delete[] input;
}

/**
    * ACCESSOR METHODS
*/
/**
    * @return The address to layers_ 2D vector.
*/
std::vector<std::vector<Node>>& Network::getLayers() {
    return layers_;
}

/**
    * NEURAL NETWORK FUNCTIONS
*/
/**
    * Normalizes the values to be beteen zero and one.
    *
    * This is a min-max normalization.
*/
void Network::normalization(int layerNum, std::vector<double> input) {
    double min = *std::min_element(input.begin(), input.end());
    double max = *std::max_element(input.begin(), input.end());

    //Print to console if the input vector size and specified layer size are different
    if (layers_[layerNum].size() != input.size()) {
        std::cerr << "WARNING: Input vector size does not match specified layer size." << std::endl;
    }

    //So long as i is less than the amount of nodes AND the input, set each nodes' value
    //  to the respective element in the specified layer_ vector.
    for (int i = 0; i < layers_[layerNum].size() && i < input.size(); i++) {
        layers_[layerNum][i].setValue((input[i] - min) / (max - min));
    }
}

/**
    * Sets the values of the nodes of a layer to those specified in a vector.
    *
    * Iterates through the specified layer of nodes and assigns each one's value
    * to the equivalent item in the input vector.
    * If the input vector size is smaller than the amount of nodes in the layer,
    * some nodes' values will not be overwritten.
    * This is useful for setting the values of the input layer nodes, in
    * preparation for forward propagation; layerNum would be equal to 0
    *
    * @param layerNum The layer to set the values of (layers_[layerNum])
    * @param input The std::vector<double> to assign to respective nodes' values.
*/
void Network::setLayerValues(int layerNum, std::vector<double> input) {
    //Print to console if the input vector size and specified layer size are different
    if (layers_[layerNum].size() != input.size()) {
        std::cerr << "WARNING: Input vector size does not match specified layer size." << std::endl;
    }

    //So long as i is less than the amount of nodes AND the input, set each nodes' value
    //  to the respective element in the specified layer_ vector.
    for (int i = 0; i < layers_[layerNum].size() && i < input.size(); i++) {
        layers_[layerNum][i].setValue(input[i]);
    }
}

/**
    * Performs a single propagation of the specified layer.
    *
    * Iterates through the nodes of a layer and calculates the value of that node
    * based on the preceeding layer of weighted connections of nodes and their values.
    * The dot product of the preceeding connected node-edge pairs are taken.
    * That dot product is added with each node's bias_.
    * That sum is then passed through an activation function, and the node is activated.
    *
    * @param layerNum The specified layer to perform a single propagation
*/
void Network::forwardPassLayer(int layerNum) {
    //For each node in the layer
    for (int i = 0; i < layers_[layerNum].size(); i++) {

        //E wi xi   or  y = mx + b
        layers_[layerNum][i].RELU(getDotProduct(layerNum-1, i) + layers_[layerNum][i].getBias());
    }
}

/**
    * Gets the dot product of nodes in a layer that connect to a particular node
    *
    * For all the nodes of a specified layer, get each node's value_ and edges_
    * In the edges_ array, get the edge weight at a particular index. This is useful as
    * the position of an edge that connects to a node one layer ahead, is the same
    * as the position of that ahead node in its layer ahead.
    * For example, if a node is in position 3 in its layer, then the weights of its
    * rear-connected edges are all at index 3 in the edges_ vector of the nodes of the layer behind.
    * 
    * Calculate the dot product: node's value * node's relevant edge weight
    * Add the product to the output until all nodes have been visited.
    *
    * @param layerNum The specified layer to calculate the dot product
    * @param edge The index of the relevant edge weight
    * @return The sum of all the products of node values and relevant edges weights
*/
double Network::getDotProduct(int layerNum, int edge) {
    double dot = 0.0;

    for (int i = 0; i < layers_[layerNum].size(); i++) {
        dot += layers_[layerNum][i].getValue() * layers_[layerNum][i].getEdges()[edge];
    }

    return dot;
}
/**
    * Returns the values of a layer as a vector of doubles
    *
    * Traverses the specified layer and gets the value_ of each node within. This value
    * is pushed into a vector of doubles, which is returned after every node
    * has been visited.
    *
    * @param layerNum The specified layer to read the value_ of all the nodes
    * @return A vector of doubles containing the values of the layer's nodes
*/
std::vector<double> Network::getLayerValues(int layerNum) {
    std::vector<double> output;
    for (int i = 0; i < layers_[layerNum].size(); i++) {
        output.push_back(layers_[layerNum][i].getValue());
    }
    return output;
}

/**
    * Softmax function
*/
std::vector<double> Network::softmax(int layerNum) {
    int size = layers_[layerNum].size();
    std::vector<double> output;

    double val;
    double summation = 0.0;
    for (int i = 0; i < size; i++) {
        val = layers_[layerNum][i].getValue();
        output.push_back(val);

        summation += std::pow(e, val);
    }

    for (int i = 0; i < size; i++) {
        output[i] = std::pow(e, output[i]) / summation;
    }

    return output;
}

/**
    * Performs the forward propagation operation on the neural network.
    *
    * The network first recieves the input in the form of an std::vector<double>
    * Then assign the values of the input layer of the network to the vector's specifications
    * Then for each layer ahead of the input layer, perform a forward pass. This is
    * done all the way until the values of the output layer have been set.
    * The function returns a vector representing the values of the output layer.
    *
    * @param input std::vector<double> containing data to set the values of the input layer's nodes'.
    * @return std::vector<double> representing the values of the output layer.
*/
std::vector<double> Network::forwardPropagation(std::vector<double> input) {
    //Getting layer size
    int size = layers_.size();

    //Set input layer to the input vector after a min-max normalization. "0" specifies the first layer
    normalization(0, input);    //setLayerValues(0, input); is the non-normalize alternative
    //Future plan is combine these two and make normalization only find a layer to normalize

    //For every layer ahead of the output, do a forward pass. Time complexity O(N^3)
    for(int i = 1; i <= size; i++) {
        forwardPassLayer(i);
    }

    //Return the softmaxed values of all the nodes of the output layer as a vector of doubles
    return softmax(size-1);   //getLayerValues(size-1); is the non-softmax alternative
    //Future plan is combine these two
}

/**
    * PRINT METHODS
*/
/**
    * Prints the data contained within a node.
*/
void Network::printLayer(int layerNum) const {
    for (int i = 0; i < layers_[layerNum].size(); i++) {
        layers_[layerNum][i].printNode();
    }
}

/**
    * Prints the entire network
*/
void Network::printNetwork() const {
    for (int i = 0; i < layers_.size(); i++) {
        std::cout << "\n\nLayer: " << i << " Size: " << layers_[i].size() << std::endl;
        printLayer(i);
    }
}