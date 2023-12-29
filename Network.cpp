/**
 * Created by Michael Calle, Allison Lee, Angus Hu on December 27, 2023
*/

Network::Network(int n){
    int layer[n] = {};
    layer_ = layer;
}

int * Network::getLayer(){
    return layer_;
}