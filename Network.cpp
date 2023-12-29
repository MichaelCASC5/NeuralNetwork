/**
 * Created by Michael Calle, Allison Lee, Angus Hu on December 27, 2023
*/

Network::Network(std::initializer_list<int> arr) {
    std::vector<std::vector<int>> layers;

    int i = 0;
    for (int value : arr) {
        std::vector<int> nodes(value, 0);
        layers.push_back(nodes);
        
        i++;
    }

    layers_ = layers;
}

std::vector<std::vector<int>> Network::getLayers() {
    return layers_;
}