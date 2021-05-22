#ifndef _HIDDEN_LAYER_H
#define _HIDDEN_LAYER_H

#include <vector>
#include "InputLayer.hpp"

class HiddenLayer {
    private:
        const InputLayer&   _inputLayer;   
        HiddenLayer*        _pPreviousLayer;
        int                 _layerSize;

        // There two are the core items, Domian objects
        double                      _layerBias;
        std::vector<double>         _layerWeights;
        std::vector<double>         _layerOutput;
        
        void intialiseWeightsAndBias();
    
    public:
        HiddenLayer(const InputLayer& inp, int layerSize);
        HiddenLayer(HiddenLayer* prevLayer, int layerSize);

        // Member functions
        std::vector<double> getPrediction();
        int getLength() const;      
};

#endif