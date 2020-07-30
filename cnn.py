import matplotlib.pyplot as plt
import tensorflow as tf
from tensorflow.keras import layers, datasets, models
import pickle
import numpy as np
import os

# config graphic storage allocate automatically
gpu_devices = tf.config.experimental.list_physical_devices(device_type='GPU')
for gpu in gpu_devices:
    tf.config.experimental.set_memory_growth(gpu, True)

# to print texture without ignorance
np.set_printoptions(threshold=np.inf)

# datasets path
training_file = r'D:\dataset\traffic_data\train.p'
validation_file = r'D:\dataset\traffic_data\valid.p'
testing_file = r'D:\dataset\traffic_data\test.p'

# load dataset
with open(training_file, mode='rb') as f:
    train = pickle.load(f)
with open(validation_file, mode='rb') as f:
    valid = pickle.load(f)
with open(testing_file, mode='rb') as f:
    test = pickle.load(f)

# get and handle x and labels, train, verify, test
X_train, y_train = train['features'], train['labels']
X_valid, y_valid = valid['features'], valid['labels']
X_test, y_test = test['features'], test['labels']

# convert image to float32
X_train = X_train / 255.
X_valid = X_valid / 255.
X_test = X_test / 255.

# cnn construction
model = models.Sequential()
# conv layer 1
model.add(layers.Conv2D(32, (5, 5), activation='relu', input_shape=(32, 32, 3)))  # output size: 28*28*32
# max pooling 1
model.add(layers.MaxPooling2D((2, 2)))  # output size: 14*14*32
# conv layer 2
model.add(layers.Conv2D(32, (5, 5), activation='relu'))  # output size: 10*10*64
# max pooling 2
model.add(layers.MaxPooling2D((2, 2)))  # output size: 5*5*32
# print information
model.summary()
# flat data
model.add(layers.Flatten())  # 800 neurons
# full connection 1
model.add(layers.Dense(64, activation='relu'))  #
# full connection 2, output is soft-maxed
model.add(layers.Dense(43, activation='softmax'))
# print information
model.summary()
model.compile(optimizer='adam',
              loss='sparse_categorical_crossentropy',
              metrics=['accuracy'])

# train the model 60 times
model.fit(X_train, y_train, epochs=60)
model.fit(X_test, y_test, epochs=30)

# test the model
test_loss, test_acc = model.evaluate(X_test, y_test)

datatexture_path = "D:\\dataset"
for i in range(0, 7):
    f = open(datatexture_path + '\\weight_layer_' + format(i, '01d') + '.txt', 'w')
    print(np.array(model.layers[i].get_weights()), file=f)
    f.close()
