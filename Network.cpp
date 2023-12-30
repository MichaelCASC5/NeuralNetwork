/**
 * Created by Michael Calle, Allison Lee, Angus Hu on December 27, 2023
*/

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
    //Print to console if the input vector size and input layer size are different
    if (layers_[layerNum].size() != input.size()) {
        std::cerr << "WARNING: Input vector size does not match input layer size." << std::endl;
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
    setLayerValues(0, input);
    for(int i = 1; i <= layers_.size(); i++) {
        std::cout << "LAYER" << std::endl;
        forwardPassLayer(i);
    }

    std::vector<double> output;
    return output;
}