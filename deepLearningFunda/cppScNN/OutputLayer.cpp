#include "headers/OutputLayer.hpp"

OutputLayer::OutputLayer(const std::vector<double> &output) : _output(output) {
}

const std::vector<double> OutputLayer::getOutput() const {
    return _output;
}

double OutputLayer::getLoss(const std::vector<double> &predictedOutput, const OutputLayerLossType &lossType) const {
    // This for saving from acidental errors
    if( predictedOutput.size() != _output.size() ) throw "Bad input";
    
    return 0.0;
}