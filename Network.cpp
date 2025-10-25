/**
 * Created by Michael Calle, Allison Lee, Angus Hu on December 27, 2023
*/

#define e 2.7182818284590452353602874713527

/**
    * CONSTRUCTORS
*/

/**
    * DEFAULT CONSTRUCTOR
    * 
    * @post: initializes a default network
*/
Network::Network(){
    //Initialize the 2D vector of nodes
    layers_ = {};
}

/**
    * PARAMETERIZED CONSTRUCTOR Connects the neural network
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
 * COPY CONSTRUCTOR
 *
 * @param: const reference to another network
 * @post: sets all values to other's values
*/
Network::Network(const Network& other){ 
    // initialize a 2D vector of nodes  
    std::vector<std::vector<Node>> layers;

    // for every element (layer/vector of nodes) in other layer, iterate through the vector of nodes
    // use a parameterized constructor to create a node with the same value, bias, and edge
    for(int i = 0; i < other.layers_.size(); i++) {
        // initialize a vector of nodes
        std::vector<Node> nodes;

        // iterate through every node in other layer
        for(int j = 0; j < other.layers_[i].size(); j++) {

            // construct a new node using the values in other node
            Node add_node(other.layers_[i][j].getValue(), other.layers_[i][j].getBias(), other.layers_[i][j].getEdges());

            // add node to nodes vector
            nodes.push_back(add_node);
        }

        // add nodes vector to layers
        layers.push_back(nodes);
    }

    // private member variable layers_ is set to layers
    layers_ = layers;
}

/**
 * COPY ASSIGNMENT OPERATOR
 *
 * @param: const reference to another network
 * @post: assigns all values to other's values
 * @return: this network
*/
Network& Network::operator=(const Network& other){
    // initialize a 2D vector of nodes  
    std::vector<std::vector<Node>> layers;

    // for every element (layer/vector of nodes) in other layer, iterate through the vector of nodes
    // use a parameterized constructor to create a node with the same value, bias, and edge
    for(int i = 0; i < other.layers_.size(); i++) {
        // initialize a vector of nodes
        std::vector<Node> nodes;

        // iterate through every node in other layer
        for(int j = 0; j < other.layers_[i].size(); j++) {
            // construct a new node using the values in other node
            Node add_node(other.layers_[i][j].getValue(), 
                other.layers_[i][j].getBias(),
                other.layers_[i][j].getEdges());

            // add node to nodes vector
            nodes.push_back(add_node);
        }

        // add nodes vector to layers
        layers.push_back(nodes);
    }

    // private member variable layers_ is set to layers
    layers_ = layers;
    return *this;
}

/*
    * DESTRUCTOR
*/
Network::~Network(){}

/**
    * ACCESSOR METHODS
*/
/**
    * @return the size of the 2D vector layers_
*/
int Network::size() const{
    return layers_.size();
}

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
    * Performs a min-max normalize on the values of a specified layer to be between zero and one.
    *
    * The values of "min" and "max" are first initialized to the value of the first node in 
    * the specified layer. The layer is first traversed in search of the max and min node values.
    * The layer is traversed a second time and normalizes each value using the mix-max data
    * that was collected from the first pass.
    * Each value is normalized with the following expression: (value - min) / (max - min)
    *
    * @param layerNum The layer to perform the min-max normalize on.
*/
void Network::minmaxnormalize(int layerNum) {
    //Getting size of layer
    int size = layers_[layerNum].size();

    //If there aren't any nodes in the layer, don't continue with the function
    if (size < 1) {
        std::cerr << "MIN-MAX NORM ERROR: Layer " << layerNum << " has no nodes to work with." << std::endl;
        return;
    }

    //Intializing min and max to the value of the first node in the layer
    double min = layers_[layerNum][0].getValue();
    double max = layers_[layerNum][0].getValue();

    //Initializing double val that holds the value of a node
    double val;

    //Traverse the layer once in search of the min and max values
    for (int i = 0; i < size; i++) {
        val = layers_[layerNum][i].getValue();
        if (val < min) { 
            min = val;
        } else if (val > max) {
            max = val;
        }
    }

    //Traverse the layer again and normalize each value
    for (int i = 0; i < size; i++) {
        val = layers_[layerNum][i].getValue();

        //Avoid divide by zero error
        if (max == min) {
            //If all the values in the layer are the same, each normalized item is 1 / size
            val = 1.0 / size;
        } else {
            //min-max normalizing the value
            val = (val - min) / (max - min);
        }

        //Setting the node's value to the normalized value
        layers_[layerNum][i].setValue(val);
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
        layers_[layerNum][i].LeakyReLU(getDotProduct(layerNum-1, i) + layers_[layerNum][i].getBias());
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

    //Iterate through each node in the output layer, pushing each node's value to the output vector
    for (int i = 0; i < layers_[layerNum].size(); i++) {
        output.push_back(layers_[layerNum][i].getValue());
    }

    return output;
}

/**
    * Returns the values of the output layer as a vector of doubles
    *
    * Traverses the output layer and gets the value_ of each node within. This value
    * is pushed into a vector of doubles, which is returned after every node
    * has been visited.
    *
    * @return A vector of doubles containing the values of the output layer's nodes
*/
std::vector<double> Network::getOutputLayerValues() {
    std::vector<double> output;

    //Get the last layer index
    int layerNum = layers_.size() - 1;

    //Iterate through each node in the output layer, pushing each node's value to the output vector
    for (int i = 0; i < layers_[layerNum].size(); i++) {
        output.push_back(layers_[layerNum][i].getValue());
    }

    return output;
}

/**
    * Performs the softmax function on a given layer
    *
    * Each element in a given layer is pushed to a vector. While this is happening
    * the summation is being calculated. The summation involves raising Euler's number
    * to the power of the value, i.e., e^(value_), while calculating the sum of this operation
    * across all possible values.
    * Once the summation was calculated, perform the same operation on each item in
    * the vector, but dividing each one by the summation, i.e., e^(value_) / summation
    *
    * @param layerNum The layer to perform the softmax on
    * @return A vector of doubles with the softmaxed values
*/
std::vector<double> Network::softmax(int layerNum) {
    //Getting layer size
    int size = layers_[layerNum].size();

    //Initializing vars for use in the loop
    std::vector<double> output;
    double val;
    double summation = 0.0;

    //Push each value in the node to the output vector while calculating summation along the way
    for (int i = 0; i < size; i++) {
        //Push values into vector
        val = layers_[layerNum][i].getValue();
        output.push_back(val);

        //Calculate summation
        summation += std::pow(e, val);
    }

    //Iterate through the output vector and for each element perform the softmax
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

    //Set input layer to the input vector. "0" specifies the first layer
    setLayerValues(0, input);

    //min-max normalize the input layer. "0" specifies the first layer
    minmaxnormalize(0);

    //For every layer ahead of the output, do a forward pass. Time complexity O(N^3)
    for(int i = 1; i < size; i++) {
        forwardPassLayer(i);
        minmaxnormalize(i);
    }

    //Return the softmaxed values of all the nodes of the output layer as a vector of doubles
    return softmax(size-1);   //getLayerValues(size-1); is the non-softmax alternative
}

/**
    * Mutates all the nodes of a specified layer by a random amount
    * 
    * Iterate through every node of a specified layer, and mutate each one
    *
    * @param layerNum The specified layer to mutate
    * @param threshold A double that represents the bounds of the mutation value
*/
void Network::mutateLayer(int layerNum, double threshold){
    //Traverse all the nodes of a layer
    for (int i = 0; i < layers_[layerNum].size(); i++) {
        
        //Mutate each node by the threshold
        layers_[layerNum][i].mutate(threshold);
    }
}

/**
    * Mutate every node in every layer of the network.
    *
    * The layers of the network are traversed and each one is mutated.
    *
    * @param threshold The positive upper and negative lower bounds of the mutation
    * @post: add a random number (bounded by -threshold and threshold) from all the edge weights and all the biases of the network
*/
void Network::mutate(double threshold){
    //Iterate through each layer
    for(int i = 0; i < layers_.size(); i++) {
        
        //Mutate each layer, while passing threshold
        mutateLayer(i, threshold);
    }
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

/**
    * FILE METHODS
*/
/**
    * Reads a network from a JSON file
    *
    * Every line is read for value, bias, and weights, which are assigned to a node.
    * After weights have been read, the node is pushed to a vector that represents a
    * single layer. (readLayer) If the end of a node array in the JSON is reached, the
    * layer is pushed to the actual Network layers_ private member, and the readLayer
    * is cleared in preparation to read a new set of nodes.
    *
    * @param file The file to read from
*/
void Network::readFile(std::string fileName) {

    //Loads file
    std::ifstream file(fileName);

    //Clear layers_
    layers_.clear();

    //Initialzing node to read data into
    Node readNode;

    //Initializing layer to read nodes into
    std::vector<Node> readLayer;

    //Counter to keep track of when a node is being read or not
    int nodeLine = 0;

    //Reading each line in the file
    std::string line;
    while (getline(file, line)) {

        //Information representing the substrings that hold the data's length
        int dataB, dataE, subLen;

        //If the line holds a value
        if (line.find("value") != std::string::npos) {
            //Find the beginning of the relevant data
            dataB = line.find(": ");
            dataB += 2;//bringing index up to where the data is

            //Find the end of the relevant data
            dataE = line.find(",");

            //Find the length of the substring that holds the data
            subLen = dataE - dataB;

            //Set the node's value to the double in that substr
            readNode.setValue(stod(line.substr(dataB, subLen)));

        //If the line holds a bias
        } else if (line.find("bias") != std::string::npos) {
            //Find the beginning of the relevant data
            dataB = line.find(": ");
            dataB += 2;//bringing index up to where the data is

            //Find the end of the relevant data
            dataE = line.find(",");

            //Find the length of the substring that holds the data
            subLen = dataE - dataB;

            //Set the node's value to the double in that substr
            readNode.setBias(stod(line.substr(dataB, subLen)));

        //If the line holds the edges
        } else if (line.find("edges") != std::string::npos) {
            
            //Initializing the vector of doubles that will be set to the node's edges_
            std::vector<double> readEdges;

            //Find the beginning and end of the first item in the array
            dataB = line.find(": ");
            dataB += 3;//add 3 for ": ["
            dataE = line.find(",");

            //If there are no commas, take the closing bracket (might be one element)
            if (dataE == std::string::npos) {
                dataE = line.find("]");
            }

            //Find the length of the substring that holds the data
            subLen = dataE - dataB;

            //Only add the edge weight if there is a value there
            if(line.substr(dataB, subLen).size() > 0) {

                //Push the edge weight to the vector that is storing the node's weights
                readEdges.push_back(stod(line.substr(dataB, subLen)));
            }

            //Move the substring onto the next item
            line = line.substr(dataE + 1);
            
            while (line.size() > 1) {

                //Find the end of the relevant data
                dataE = line.find(",");

                //If there are no more commas, take the closing bracket
                if (dataE == std::string::npos) {
                    dataE = line.find("]");
                }

                //If the JSON edge array has spaces after the , (1, dataE - 1), if not (0, dataE)
                readEdges.push_back(stod(line.substr(1, dataE - 1)));

                //Move the substring onto the next item
                line = line.substr(dataE + 1);
            }

            //Once edges have been read, set the node's edges
            readNode.setEdges(readEdges);

            //Once the node is ready, push the node to the vector of nodes
            readLayer.push_back(readNode);

            //Clear node for next parse
            readNode = Node();
            
        //If the line holds nothing but the close bracket, it signifies an arry of nodes has been read
        } else if (line.find("        ]") != std::string::npos) {

            //Push the layer to network layers_
            layers_.push_back(readLayer);

            //Clear readLayer for next parse
            readLayer.clear();
        }
    }

    //Closes file
    file.close();
}

/**
    * Writes a network to JSON file
*/
void Network::writeFile(std::string fileName) {
    //Writes file
    std::ofstream file(fileName);

    //Open JSON braces
    file << "{\n    \"layers_\": [\n";

    //For every layer
    for (int i = 0; i < layers_.size(); i++) {
        //Open layer array brackets
        file << "        [\n";

        //For every node in the layer
        for (int j = 0; j < layers_[i].size(); j++) {
            // std::cout << layers_[i].size() << std::endl;

            //Open object brace
            file << "            {\n";

            //Printing the value and bias of the node
            file << "                \"value\": " << layers_[i][j].getValue() << ",\n";
            file << "                \"bias\": " << layers_[i][j].getBias() << ",\n";

            //Printing the edges of the node
            file << "                \"edges\": [";
            for (int k = 0; k < layers_[i][j].getEdges().size(); k++) {

                //Put a comma after each item
                if(k < layers_[i][j].getEdges().size() - 1) {
                    file << layers_[i][j].getEdges()[k] << ", ";

                //If this item is the last one, don't put a comma after it, rather put a bracket
                } else {
                    file << layers_[i][j].getEdges()[k] << "";
                }
            }

            //Closing the edges of the node
             file << "]\n";

            //Put a comma after the brace
            if(j < layers_[i].size() - 1) {
                file << "            },\n";

            //If this node is the last one, don't put a comma after the brace
            } else {
                file << "            }\n";
            }
        }

        //Close layer array brackets
        //Put a comma after the bracket
        if(i < layers_.size() - 1) {
            file << "        ],\n";

        //If this layer is the last one, don't put a comma after the bracket
        } else {
             file << "        ]\n";
        }
    }

    //Close JSON braces
    file << "    ]\n}";

    //Closes file
    file.close();
}