#ifndef _NEURALNETWORK_
#define _NEURALNETWORK_

#include "Layer.hpp"
#include <vector>

using namespace std;

class NeuralNetwork {
    private:
        Layer           _inputLayer;
        Layer           _outputLayer;

        vector<Layer>   _hiddenLayers;
        Layer&          _currnetLayer;

    public:
        NeuralNetwork(vector<float> inputValues, size_t outputLength);

        // TODO: To add actual impelementation, should be retruning a layer instead
        bool addHiddenLayer(size_t inputLength, size_t outputLength);

        // TODO: Add actual impl
        vector<float> doForwardPass();
};

#endif