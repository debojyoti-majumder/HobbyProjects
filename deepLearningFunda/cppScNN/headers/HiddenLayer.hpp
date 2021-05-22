#ifndef _HIDDEN_LAYER_H
#define _HIDDEN_LAYER_H

#include <vector>
#include "InputLayer.hpp"

class HiddenLayer {
    private:
        const std::vector<double>& _inputData;
        bool _isConstructedFromInput;

    public:
        HiddenLayer(const InputLayer& layer);
        HiddenLayer(const HiddenLayer& layer);

        // Member functions
        std::vector<double> getPrediction() const;      
};

#endif