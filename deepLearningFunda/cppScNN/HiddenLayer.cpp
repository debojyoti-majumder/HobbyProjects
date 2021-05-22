#include "headers/HiddenLayer.hpp"

HiddenLayer::HiddenLayer(const InputLayer &layer) : _inputData(layer.getInputs()) {
    // Which means this would be the last layer for back propagation
    _isConstructedFromInput = true;
}

HiddenLayer::HiddenLayer(const HiddenLayer& layer) : _inputData(layer.getPrediction()) {
    // Back ward propagation to continue
    _isConstructedFromInput = false;
}

std::vector<double> HiddenLayer::getPrediction() const {
    // TODO: Make actual implementation
    return {};
}