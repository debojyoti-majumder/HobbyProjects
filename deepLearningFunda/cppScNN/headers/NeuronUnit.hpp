#ifndef _NEURONUNIT_HPP
#define _NEURONUNIT_HPP

#include <vector>

using namespace std;
class Layer;

class NeuronUnit {
    private:
        const vector<float>&  _input;
        vector<float>   _weight;
        float           _bias;

    public:
        NeuronUnit(const vector<float>& input, float bias);
        NeuronUnit(const Layer& prevLayer, float bias);

        float computeOutput() const;
};

#endif