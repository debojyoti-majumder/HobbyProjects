#include <iostream>
#include <vector>

#include "headers\NeuralNetwork.hpp"

int main(int argc, char** argv) {
    vector<float> actualInput;
    
    argc;
    argv;

    NeuralNetwork network(actualInput, 10);
    
    network.addHiddenLayer(10,10);
    network.addHiddenLayer(10,10);

    network.doForwardPass();

    return 0;
}
