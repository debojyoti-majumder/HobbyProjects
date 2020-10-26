#include <iostream>
#include <vector>

using namespace std;

class Layer;

class NeuronUnit {
    private:
        vector<float>   _input;
        vector<float>   _weight;
        float           _bias;

    public:
        NeuronUnit(const vector<float>& input, float bias) {

        }

        NeuronUnit(const Layer& prevLayer, float bias) {

        }
};

class Layer {
    private:
        vector<float> _input;
        vector<float> _output;

    public:
        Layer(vector<float>& input, int outputLength) {

        }

        Layer(const Layer& prevLayer, int outputLength) {

        }
};

class NeuralNetwork {
    private:
        Layer inputLayer;
        Layer outputLayer;

        vector<Layer> hiddenLayer;

    public:
        NeuralNetwork(vector<float> inputValues, size_t outputLength) : 
            inputLayer(inputValues, outputLength),  
            outputLayer(inputLayer, outputLength) {

        }

        // TODO: To add actual impelementation
        bool addHiddenLayer(size_t inputLength, size_t outputLength) {
            return true;
        }

        // TODO: Add actual impl
        vector<float> doForwardPass() {
            vector<float> returnValue;

            return returnValue;
        }

};

int main(int, char**) {
    cout << "This is test nural network item\n";
}
