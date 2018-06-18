# Name:			Christian Carreras
# File:			readme.txt
# Date:			10/17/2016
# Course:		CSC343 Kutztown University
# Professor:	Dr. Parson
# Assignment:	2

Analysis on MEAN_lockSum:
	I believe the fact that the Atomic20 bar is so high is due to the fact that
	more threads create more contention for the lock. Since there is no order
	to when threads go through the lock, the threads will wait a longer time
	spinning in this state. This is due to the nature of the lock. Each thread
	will keep spinning until the lock is open. Once the lock is open, the first
	thread to reach the lock will get to go through it. Thus some threads wait
	for a long time in the lockSum state. When there is less threads and less
	contention, the mean time will fall dramatically for atomic locks.
	Mutex locks on the other hand have the same mean time in this state
	regardless of how many threads are running. This is due to the
	implementation of a waiting state with a queue. Since the nature of a queue 
	is first in first out, each thread is spending the same amount of time 
	being in the lockSum state by waiting their turn in the waiting state
	until it is time to transition back and go through the lock.
	
	The difference between atomic and mutex locks is: 
		The number of threads do not matter when it comes to mutex locks
		because it is exporting its waiting threads to a queued waiting state.
		But when it comes to atomic locks the average time a thread waits
		increases directly with the number of other threads running because it
		keeps looping back to the same state until the lock opens.
	
Analysis on MEAN_lockDifference:
	The reason every bar is the same height regardless of lock type is because 
	there was a previous lock before lockDifference in every file with locks. 
	Since each thread goes through the first lock one at a time, by the time a 
	thread reaches the next lock it will always be open. Every thread will 
	spend the same amount of time in this state no matter the lock or number of
	threads because there will never be any contention. As to why they are all 
	waiting for exactly three ticks, the state is scheduling three ticks for 
	cpu every time. Since no thread is waiting for the lock, threads will not 
	spend any extra time in that state since the lock is already open.
