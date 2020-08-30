import tensorflow.compat.v1 as tf
import numpy as np
import math

from data_loader import load_data

tf.disable_v2_behavior()


def nn_layer(layer_input, weight_shape, bias_shape):
    weight_init = tf.random_uniform_initializer(minval=-1, maxval=1)
    bias_init = tf.constant_initializer(value=0)

    W = tf.get_variable('Weight', weight_shape, initializer=weight_init, dtype=tf.float32)
    b = tf.get_variable('bias', bias_shape, initializer=bias_init, dtype=tf.float32)

    return tf.matmul(layer_input, W) + b


def my_network_model(data_input, number_of_features, output_class):
    output_1 = nn_layer(data_input, [number_of_features, output_class], [output_class])

    return output_1


# Actual inference function to be used
def inference_with_softmax(data_input, number_of_features, output_class):
    network_output = my_network_model(data_input, number_of_features, output_class)
    softmax_output = tf.nn.softmax(network_output)

    return softmax_output


def gradient_decent_training(cost, global_step):
    optimizer = tf.train.GradientDescentOptimizer(learning_rate)

    # Should be minimizing the cost
    min_cost = optimizer.minimize(cost, global_step=global_step)
    return min_cost


def training_loss(predicted_output, actual_output):
    dot_product = actual_output * tf.log(predicted_output)

    entropy = - tf.reduce_mean(dot_product, reduction_indices=1)
    loss = tf.reduce_mean(entropy)

    return loss


# TODO: This not a good way of using variable have to use some type of object related functionality
# As of now using them as global variable
train_i, test_i, train_out, test_out = load_data()
input_shape = 4
output_shape = 3
learning_rate = 0.01


def do_training(tf_session, input_batch, output_batch):
    input_placeholder = tf.placeholder(tf.float32, shape=(None, input_shape))
    predicted_output = inference_with_softmax(input_placeholder, input_shape, output_shape)

    encoded_output = np.eye(output_shape)[output_batch]
    cost = training_loss(predicted_output, encoded_output)

    # TODO There should be a better way to add it in tensorboard which can be tracked
    # This won't provide the actual value as this is a tensor variable
    print("Cost:", cost)

    gl_steps = tf.Variable(0, name="global_step", trainable=False)
    grad_train_op = gradient_decent_training(cost, gl_steps)

    init = tf.initialize_all_variables()
    tf_session.run(init)

    session.run(grad_train_op, feed_dict={input_placeholder: input_batch})


with tf.Session(config=tf.ConfigProto(log_device_placement=False)) as session:
    start_index = 0
    batch_size = 10

    input_count = train_i.shape[0]
    batch_count = math.floor(input_count / batch_size)

    with tf.variable_scope("shared_variable") as scope:
        # This is just one epoch
        for i in range(batch_count):
            train_data = train_i[start_index:start_index + batch_size]
            train_actual_output = train_out[start_index:start_index + batch_size]

            # Does the actual computation
            do_training(session, train_data, train_actual_output)

            start_index += batch_size
            scope.reuse_variables()
