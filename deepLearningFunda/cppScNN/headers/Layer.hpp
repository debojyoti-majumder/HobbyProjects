#ifndef _LAYER_HPP
#define _LAYER_HPP

#include <vector>

using namespace std;

class Layer {
    private:
        vector<float> _input;
        vector<float> _output;

    public:
        // This is ctor is for input layer
        Layer(vector<float>& input, int outputLength, bool passthrough = false);

        // This ctor would be used mainly to add layers
        Layer(const Layer& prevLayer, int outputLength, bool passthrough = false);

        // This would be used by the neurons for as of now to calculate the value
        const vector<float>& getOutputValues() const;
};

#endif