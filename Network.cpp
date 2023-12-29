/**
 * Created by Michael Calle, Allison Lee, Angus Hu on December 27, 2023
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
    * @return The address to layers_ 2D vector.
*/
std::vector<std::vector<Node>>& Network::getLayers() {
    return layers_;
}