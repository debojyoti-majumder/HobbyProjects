#include "headers/HiddenLayer.hpp"

#include <chrono>
#include <random>

HiddenLayer::HiddenLayer(const InputLayer& inp, int layerSize) : 
                _pPreviousLayer(nullptr),
                _inputLayer(inp),
                _layerSize(layerSize),
                _layerWeights(layerSize, 0.0),
                _layerOutput(layerSize, 0.0)
{
    intialiseWeightsAndBias();
}

HiddenLayer::HiddenLayer(HiddenLayer* prevLayer, int layerSize) : 
        _pPreviousLayer(prevLayer),
        _layerSize(layerSize),
        _inputLayer(InputLayer{}),
        _layerWeights(layerSize, 0.0),
        _layerOutput(layerSize, 0.0)
{
    intialiseWeightsAndBias();
}

void HiddenLayer::intialiseWeightsAndBias() {
    std::random_device dev;
    std::mt19937 rng(dev());
    const int maxValue = 10000;

    // distribution in range [1, 10000]
    std::uniform_int_distribution<std::mt19937::result_type> uniformDist(1,maxValue); 

    for(int i=0; i<_layerSize; i++) {
        double randomNumber = uniformDist(rng);
        randomNumber /= maxValue;

        // As the values were added before assignment operatior works
        _layerWeights[i] = randomNumber;
    }

    // Initializing the bais
    _layerBias = uniformDist(rng);
    _layerBias /= maxValue;
}

int HiddenLayer::getLength() const {
    return _layerSize;
}

std::vector<double> HiddenLayer::getPrediction() {
    std::vector<double> inputNumbers = _pPreviousLayer != nullptr ? 
        _pPreviousLayer->getPrediction() : 
        _inputLayer.getInputs();

    // part of the calculation w*x + b
    for( size_t i=0; i<_layerSize; i++ ) {
        for ( size_t j=0; j<inputNumbers.size(); j++ ) 
            _layerOutput[i] += _layerWeights[i] * inputNumbers[j];
        
        _layerOutput[i] += _layerBias;
    }

    return _layerOutput;
}