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

Node::Node(double value, double bias, int edgeNum):Node() {
    value_ = value;
    bias_ = bias;
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