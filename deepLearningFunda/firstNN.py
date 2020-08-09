import tensorflow.compat.v1 as tf
import pandas as pd
import numpy as np

tf.disable_v2_behavior()


# TODO: Make this a class with constructor so there are reusable
# methods for other common task
def load_data():
    data = pd.read_csv('data/Iris.csv')
    data_shape = data.shape

    # the ID field is not required
    del data['Id']

    # Species is categorical variable let's change to int
    data['Species'], mapping_index = pd.Series(data['Species']).factorize()
    print(data.head())
    print(mapping_index)

    # Splitting the training and testing data
    mask = np.random.rand(data_shape[0]) < 0.8
    train_set = data[mask]
    test_set = data[~mask]

    # For debugging
    train_input = train_set[['SepalLengthCm', 'SepalWidthCm', 'PetalLengthCm', 'PetalWidthCm']]
    train_output = train_set['Species']

    test_input = test_set[['SepalLengthCm', 'SepalWidthCm', 'PetalLengthCm', 'PetalWidthCm']]
    test_output = test_set['Species']

    return train_input, test_input, train_output, test_output


print("Stating the training model")

# TODO: This not a good way of using variable have to use some type of object related functionality
train_i, test_i, train_out, test_out = load_data()

print(train_i.head())
print(test_i.head())
print(train_out.head())
print(test_out.head())