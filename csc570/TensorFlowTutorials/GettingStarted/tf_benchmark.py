import os
import time
import tensorflow as tf
import premade_estimator as pe

"""
Author:     Christian Carreras
Date:       05/08/18
Couse:      CSC 570 Independent Study
Professor:  Dr. Parson
University: Kutztown University
Purpose:    Shows the overhead of the gpu version of TensorFlow when using
            certain operations. The setting up and tearing down of the gpu
            device adds up and makes the gpu device perform worse than the
            cpu. Also not all TensorFlow operations are  gpu-supported.
"""

def main():
    for d in ['/cpu:0', '/device:GPU:0']:
        with tf.device(d):
            t0 = time.time()
            print('Starting ' + d + ' calculation')

            a = tf.constant([1.0, 2.0, 3.0, 4.0, 5.0, 6.0], shape=[2, 3], name='a')
            b = tf.constant([1.0, 2.0, 3.0, 4.0, 5.0, 6.0], shape=[3, 2], name='b')
            c = tf.matmul(a, b)
            with tf.Session() as sess:
                for _ in range(0,50000):
                    sess.run(c)

            """
            # For showing overhead of the gpu when used on an estimator
            for _ in range(0,10):
                pe.main("")
            """
            
            t1 = time.time()
            total = t1-t0
            print(total)
        
if __name__ == '__main__':
    os.environ['TF_CPP_MIN_VLOG_LEVEL'] = '3'
    os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3'
    #tf.logging.set_verbosity(tf.logging.INFO)
    main()
    