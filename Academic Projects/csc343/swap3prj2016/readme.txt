# Name:			Christian Carreras
# File:			readme.txt
# Date:			11/21/2016
# Course:		CSC343 Kutztown University
# Professor:	Dr. Parson
# Assignment:	3
# About:
# These questions are worth 30% of the exam, 5% each.
# Proper code implementation is worth 70%.

ffmn:SUM_GETMEMORY=4034979
abfmn:SUM_GETMEMORY=4067505
bfmn:SUM_GETMEMORY=4068780
affmn:SUM_GETMEMORY=4099920
bffifo:SUM_GETMEMORY=4745912
fffifo:SUM_GETMEMORY=4912970
afffifo:SUM_GETMEMORY=4943877
abffifo:SUM_GETMEMORY=5083657

QUESTIONS TO BE ANSWERED FOR THE ASSIGNMENT.
See http://acad.kutztown.edu/~parson/SUM_GETMEMORY.png and the above values.
Note that SUM_GETMEMORY is the sum of ticks spent in the checkIfMemory +
waitForMemory states.

1. Why might best fit on a FIFO processor.waitMemQ that sends memoryReady
to only one waiting thread (bffifo) have better performance than first fit
on the same type of queue (fffifo)?

Finding the first fit will potentially waste memory when only one waiting 
thread leaves the waitMemQ at a time. When the next thread wakes up there might 
not be enough space for it due to the previous thread taking up more than it
should have. Taking the time to find the best fit for a thread will reduce the 
chance of not having enough space for the next thread and thus reduce the 
overall time waiting.

2. Why might best fit on a FIFO processor.waitMemQ that sends memoryReady
to all waiting threads (abffifo) have *worse* performance than first fit
on the same type of queue (afffifo)?

When every thread wakes up when the event is sent some threads can fit in
multiple spaces. If each thread takes the first space that can fit it instead
of looking for the best fit the time it takes to find the best fit is cut out.
Since all the threads are awake the chance increases that another thread can
fit in the space that is left without sending another wake up event. With 
better fit it will take longer for bigger spaces to open up for threads that
need them. With first fit bigger spaces will open up when memory is released
because of the memory wasting nature of first fit. This increases the chance 
for more threads to fit and overall decreasing time spent waiting.

Explain the following advantages of first fit on a min-queue processor.waitMemQ
sorted on logical memory size, that sends memoryReady to only one waiting
thread (ffmn), that makes it the lowest-overhead of all of the above with
respect to SUM_GETMEMORY time.  Answer 3 and 4 separately.

3. Why is the ffmn min-queue algorithm especially appropriate when sending
memoryReady to only one waiting thread in the min-queue, compared to its
"all" counterpart affmn?

It is the most appropriate because the first thread in the queue will always be
the smallest in the queue. The min queue is a priority queue which sorts the 
smallest threads to the front of the queue. If all the threads wake up, most
will be placed back in the min queue in the same least to greatest order. Thus
a majority of threads will be awake for nothing, they still have to 
wait their turn in the min queue.

4. Why is the ffmn min-queue algorithm especially appropriate when sending
memoryReady to only one waiting thread in the min-queue, compared to its
best fit counterpart bfmn?

It is the most appropriate because of how the min queue works. The smallest
thread in the waiting min queue will always be first so there is no need to 
find the best fit. The first thread in the queue will always be the first and
smallest thread in the queue until the memory is ready. So it is better just 
to place it in the first available space.

5. Why do you think abfmn (sends memoryReady to all waiting threads, using
best fit with a min-queue) comes in second for minimum time spent in
SUM_GETMEMORY?

Since the waiting min queue is ordered least to greatest it will be easier to
assign threads to memory that best fit them. When all threads wake up this
expedites the process by allowing the smallest threads to fit together better
when taking memory. Naturally this will be faster than the one-at-a-time
version because multiple threads will have the chance to schedule. It is also
better than the first fit version because more than likely the thread will
always be able to fit in the first space it finds. Therefore it is better to
find the best fit so other threads can have a chance to fit as well.

6. Why do the min-queue implementations of processor.waitMemQ outperform
all of the FIFO queue implementations?

The min-queue implementations outperform all of the FIFO queue implementations
because the min-queue is always ordered least to greatest. The FIFO queue
is in the order of how the threads show up so threads of all sizes can be
distributed all throughout the queue. This creates a situation where a thread 
that wakes up might not be able to fit anywhere so it has to go back in the 
FIFO queue and wait until it is first again to try to fit again. The min-queue
eliminates this by having the smallest thread first so it will always fit when
it goes to schedule memory. The min-queue also eliminates any possibility that
a large thread will take up memory so that smaller threads are unable to use
it and use the memory more sparingly/faster.
