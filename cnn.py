
from __future__ import print_function
import tensorflow as tf
import numpy as np

data_root_path = "D:\\dataset\\GTRSB\\"
image_array = np.load(data_root_path + 'imag.npy')
label_data = np.load(data_root_path + 'label.npy')
label_array = np.zeros(shape=[39209, 43], )
for i in range(0, 39209):
    label_array[i][label_data[i]] = 1


def compute_accuracy(v_xs, v_ys):
    global prediction
    y_pre = sess.run(prediction, feed_dict={xs: v_xs})
    correct_prediction = tf.equal(tf.argmax(y_pre, 1), tf.argmax(v_ys, 1))
    accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))
    result = sess.run(accuracy, feed_dict={xs: v_xs, ys: v_ys})
    return result


def weight_variable(shape):
    initial = tf.random.truncated_normal(shape, stddev=0.1)
    return tf.Variable(initial)


def bias_variable(shape):
    initial = tf.constant(0.1, shape=shape)
    return tf.Variable(initial)


def conv2d(x, W, padding_style='SAME'):
    return tf.nn.conv2d(x, W, strides=[1, 1, 1, 1], padding=padding_style)


def max_pool_2x2(x, padding_style='SAME'):
    return tf.nn.max_pool2d(x, ksize=[1, 2, 2, 1], strides=[1, 2, 2, 1], padding=padding_style)


# define placeholder for inputs to network
xs = tf.compat.v1.placeholder(tf.float32, [32, 32])
ys = tf.compat.v1.placeholder(tf.float32, [43])
x_image = tf.reshape(xs, [-1, 32, 32, 1])

## conv1 layer ##
W_conv1 = weight_variable([5, 5, 1, 32])
b_conv1 = bias_variable([32])
h_conv1 = tf.nn.relu(conv2d(x_image, W_conv1, padding_style='VALID') + b_conv1)  # output 28*28*32
h_pool1 = max_pool_2x2(h_conv1)  # 14*14*32
## conv2 layer ##
W_conv2 = weight_variable([5, 5, 32, 64])
b_conv2 = bias_variable([64])
h_conv2 = tf.nn.relu(conv2d(h_pool1, W_conv2, padding_style='VALID') + b_conv2)  # output 10*10*64
h_pool2 = max_pool_2x2(h_conv2)  # 5*5*64
## func1 layer ##
W_fcl = weight_variable([5 * 5 * 64, 1024])
b_fcl = bias_variable([1024])
h_pool2_flat = tf.reshape(h_pool2, [-1, 5 * 5 * 64])  # [n_samples, 5, 5, 64] ->> [n_sample, 5*5*64]
h_fcl = tf.nn.relu(tf.matmul(h_pool2_flat, W_fcl) + b_fcl)
## func2 layer ##
W_fcl2 = weight_variable([1024, 43])
b_fcl2 = bias_variable([43])
prediction = tf.matmul(h_fcl, W_fcl2) + b_fcl2

# the error between prediction and real data
cross_entropy = tf.reduce_mean(-tf.reduce_sum(ys * tf.log(prediction),
                                              reduction_indices=[1]))  # loss
train_step = tf.train.AdamOptimizer(1e-4).minimize(cross_entropy)

sess = tf.Session()
# important step
# tf.initialize_all_variables() no long valid from
# 2017-03-02 if using tensorflow >= 0.12
if int((tf.__version__).split('.')[1]) < 12 and int((tf.__version__).split('.')[0]) < 1:
    init = tf.initialize_all_variables()
else:
    init = tf.global_variables_initializer()
sess.run(init)

for i in range(39209):
    # batch_xs, batch_ys = mnist.train.next_batch(100)
    batch_xs = image_array[i]
    batch_ys = label_array[i]
    sess.run(train_step, feed_dict={xs: batch_xs, ys: batch_ys})
    print(format(i, '05d'))
