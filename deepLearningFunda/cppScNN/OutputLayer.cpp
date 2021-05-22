#include "headers/OutputLayer.hpp"

OutputLayer::OutputLayer(std::vector<double> output) {
    for(auto& v:output) _output.emplace_back(v);
}

const std::vector<double> OutputLayer::getOutput() const {
    return _output;
}

double OutputLayer::getLoss(const std::vector<double> &predictedOutput, const OutputLayerLossType &lossType) const {
    // This for saving from acidental errors
    if( predictedOutput.size() != _output.size() ) throw "Bad input";
    
    return 0.0;
}