import time
import tensorflow as tf

def main(argv):
    with tf.device('/cpu:0'):
        t0 = time.time()
        """ Do Something """
        t1 = time.time()
        total = t1-t0
        print(total)
    
    with tf.device('/device:GPU:0'):
        t0 = time.time()
        """ Do Something """
        t1 = time.time()
        total = t1-t0
        print(total)
        
if __name__ == '__main__':
    tf.app.run(main)
    