#include <iostream>
#include <vector>

#include "headers/InputLayer.hpp"
#include "headers/OutputLayer.hpp"
#include "headers/HiddenLayer.hpp"

int main(int argc, char** argv) {
    // This area would later be put in Network class

    // As of now this layer would work with normalized data alone
    std::vector<double> input{0.45, 0.96, 0.77, 0.45, 0.71, 0.33};
    InputLayer inpLayer(input);

    // This layer is 6x3 sized
    HiddenLayer hiddenLayer1(inpLayer,3);

    // This is the actual data
    OutputLayer outLayers({0.0, 0.0, 1.0});
    auto& pred {hiddenLayer1.getPrediction()};

    // This is error with predcited data
    std::cout << outLayers.getLoss(pred) << std::endl;    
    return 0;
}