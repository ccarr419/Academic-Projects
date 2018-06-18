from __future__ import print_function
import matplotlib.pyplot as plt
import tensorflow as tf
import time
import os

# -*- coding: utf-8 -*-
"""
Created on Sun May  6 20:13:25 2018

@author: Chris
"""

# https://medium.com/@erikhallstrm/hello-world-tensorflow-649b15aed18c

""" END OF ORIGINAL DOCUMENTATION """

# Basic TensorFlow benchmark comparing gpu times to cpu times.
# Operations used were matrix operations to simulate learning algorithms.
# Slight modifications by Christian Carreras, Kutztown University

def get_times(maximum_time):
    os.environ['TF_CPP_MIN_VLOG_LEVEL'] = '3'
    os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3'
    tf.logging.set_verbosity(tf.logging.INFO)
    
    device_times = {
        "/gpu:0":[],
        "/cpu:0":[]
    }
    matrix_sizes = range(500,50000,50)

    for size in matrix_sizes:
        for device_name in device_times.keys():
            
            print("####### Calculating on the " + device_name + " #######")

            shape = (size,size)
            data_type = tf.float16
            with tf.device(device_name):
                r1 = tf.random_uniform(shape=shape, minval=0, maxval=1, dtype=data_type)
                r2 = tf.random_uniform(shape=shape, minval=0, maxval=1, dtype=data_type)
                dot_operation = tf.matmul(r2, r1)


            with tf.Session(config=tf.ConfigProto(log_device_placement=True)) as session:
                    start_time = time.time()
                    result = session.run(dot_operation)
                    time_taken = time.time() - start_time
                    print(result)
                    device_times[device_name].append(time_taken)

            print(device_times)

            if time_taken > maximum_time:
                return device_times, matrix_sizes


device_times, matrix_sizes = get_times(1.5)
gpu_times = device_times["/gpu:0"]
cpu_times = device_times["/cpu:0"]

print("TOTAL GPU TIME")
total_gpu_time = 0
for time in gpu_times:
    total_gpu_time += time
print(str(round(total_gpu_time, 4)) + ' s')
    
print("TOTAL CPU TIME")
total_cpu_time = 0
for time in cpu_times:
    total_cpu_time += time
print(str(round(total_cpu_time, 4)) + ' s')

# matplotlib visualization
"""
plt.plot(matrix_sizes[:len(gpu_times)], gpu_times, 'o-')
plt.plot(matrix_sizes[:len(cpu_times)], cpu_times, 'o-')
plt.ylabel('Time')
plt.xlabel('Matrix size')
plt.show()
"""
