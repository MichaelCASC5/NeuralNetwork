/**
 * Created by Michael Calle, Allison Lee, Angus Hu on December 27, 2023
*/

/**
    * Sets up the neural network
    *
    * The user inputs an array, which is read an initializer_list. e.g.({1,2,3})
    * This array is then transversed, and for each element, a new vector of nodes of
    * that length if created. That new vector of nodes is then pushed to the
    * layers_ 2D vector.
    *
    * @param initializer_list Represents how many nodes should be in each layer of the network.
*/
Network::Network(std::initializer_list<int> arr) {
    for (int value : arr) {
        std::vector<Node> nodes(value);
        layers_.push_back(nodes);
    }
}

/**
    * Returns layers
    *
    * @return The layers_ 2D vector.
*/
std::vector<std::vector<Node>> Network::getLayers() {
    return layers_;
}