#include <iostream>
#include <vector>

#include "headers/InputLayer.hpp"
#include "headers/OutputLayer.hpp"

int main(int argc, char** argv) {
    // As of now this layer would work with normalized data alone
    InputLayer layer({0.45, 0.96, 0.77});
    layer.getInputs();

    OutputLayer outLayers({0.0, 0.0, 1.0});
    std::cout << outLayers.getLoss({0.4, 0.3, 0.2}) << std::endl;
    
    return 0;
}