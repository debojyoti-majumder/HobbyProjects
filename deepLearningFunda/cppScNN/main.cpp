#include <iostream>
#include <vector>

// User includes
#include "headers\Layer.hpp"

using namespace std;

class NeuralNetwork {
    private:
        Layer inputLayer;
        Layer outputLayer;

        vector<Layer> hiddenLayer;

    public:
        NeuralNetwork(vector<float> inputValues, size_t outputLength) : 
            inputLayer(inputValues, inputValues.size() ),  
            outputLayer(inputLayer, outputLength) {

        }

        // TODO: To add actual impelementation, should be retruning a layer instead
        bool addHiddenLayer(size_t inputLength, size_t outputLength) {
            return true;
        }

        // TODO: Add actual impl
        vector<float> doForwardPass() {
            vector<float> returnValue;

            return returnValue;
        }
};

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
