# Implementation is reffered from https://github.com/mattm/simple-neural-network/blob/master/neural-network.py
# As some point it should be able to train on MNIST data set

# The Back Propagation Algorithm
#   https://www4.rgu.ac.uk/files/chapter3%20-%20bp.pdf

import math
import random

class Nuron:
    def __init__(self, bias:float) -> None:
        self.bias = bias
        self.weights:list[float] = []

        # TBD: Make enum based on this
        self.activation:int = 1

    def _scalar_multiply(self, input:list[float]) -> list[float]:
        return_output:list[float] = []

        for i in range(len(input)):
            return_output.append(input[i] * self.weights)
        
        return return_output


    def calculate_output(self, input:list[float]) -> list[float]:
        self.input = input
        
        if len(input) != self.weights:
            print("Incorrect length of input vector")
            return []
        
        pre_activation = self._scalar_multiply(input)
        return self._activation_func(pre_activation)
    
    def set_weights(self, weights:list[float]) -> None:
        if len(self.weights) == 0:
            print("Init weight for nuron")
            self.weights = weights
            return
        
        if len(weights) != len(self.weights):
            print("Weight update is not allowed")
            return

        self.weights = weights
    
    def _activation_func(self, input:list[float]) -> list[float]:
        returned_output = []

        for inp in input:
            if self.activation == 1:
                exp_output:float = 1.0 / ( 1.0 + math.exp(inp))
                returned_output.append(exp_output)

        return returned_output

class NuronLayer:
    def __init__(self, num_nurons:int, bias:int = 0) -> None:
        # In a single nuron layer the bias remains the same
        if bias == 0:
            self.bias:float = random.random()
        
        # Building the layer
        self.nurons:list[Nuron] = []

        for _ in range(num_nurons):
            self.nurons.append(Nuron(self.bias))
    
    def _geneate_random_values(self, nums:int) -> list[float]:
        return_value:list[float] = []
        for _ in range(nums):
            return_value.append(random.random())

        return return_value

    def init_weights(self, prev_layer_length:int)-> None:
        for n in self.nurons:
            random_weights = self._geneate_random_values(prev_layer_length)
            n.set_weights(random_weights)

# As on now this is harc coded network which has
# Once input layer, one hidden layer
class NuralNetwrok:
    def __init__(self, input_length:int, output_length:int) -> None:
        self.input_layer:NuronLayer = NuronLayer(input_length)
        self.output_layer:NuronLayer = NuronLayer(output_length)

        # Hidden network length is now hard coded
        self.hidden_layer:NuronLayer = NuronLayer(16)

        # Init with random weight
        self.hidden_layer.init_weights(input_length)

print("A very basic hardwritten Nuralnet in python")

basicNetwrok:NuralNetwrok = NuralNetwrok(4,4)
