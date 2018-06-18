/*
Author:     Christian Carreras
Date:       12/04/17
Due Date:   12/12/17
File:       readWriteSTM.h
Assignment: #5
Course:     CSC510 Advanced Operating Systems
Professor:  Dr. Parson
University: Kutztown University of Pennsylvania
About:      As a header file, numerous functions and constants are declared in
            order to better depict what the state machine is doing at each step
            of the way. This file only outlines a general state machine that
            can have any purpose but was originally intended to solve the
            Readers Writers Problem. As such, some functions and constants are
            blueprinted here to help that goal. The Readers Writers Problem
            is solved by five algorithms in this state machine. To test these
            algorithms, multithreaded processes are simulated with multiple
            loops and threads. This is to try and create a similar environment
            a computer deals with expect on a much higher level.
*/
#ifndef READWRTIESTM_H
#define READWRITESTM_H

#define NUM_THREADS 10 //How many threads to run the algorithm
#define NUM_LOOPS 100 //How many loops each thread should run
#define KEEP_GOING 1 //Keep the current loop going
#define STOP_GOING 0 //Terminate the current loop
#define READER 0 //Designate the thread as a reader
#define WRITER 1 //Designate the thread as a writer
#define STATE_INIT 0 //Init state in the STM
#define STATE_WAIT 1 //Wait state in the STM
#define STATE_CRITSECT 2 //Critical Section state in the STM
#define STATE_TERMINATE 3 //Terminate (Accept) state in the STM
#define STM_FAIR 0 //Signifies the fair algorithm
#define STM_WRP 1 //Signifies the weak reader preference algorithm
#define STM_SRP 2 //Signifies the strong reader preference algorithm
#define STM_WWP 3 //Signifies the weak writer preference algorithm
#define STM_SWP 4 //Signifies the strong writer preference algorithm
#define STM_FCFS 5 //Signifies the first come first serve preference algorithm
#define SLEEP_THREAD 100 //Amount of time to sleep between spawing threads
#define SLEEP_READER 25000 //Amount of time to sleep for a reader in the cs
#define SLEEP_WRITER 32500 //Amount of time to sleep for a writer in the cs

#include <iostream>
#include <fstream> //Write to file
#include <queue> //waitingQueue
#include <cstdatomic> //Atomic variables
#include <pthread.h> //Threads
static std::ofstream logFile; //Log file to write to
static atomic<bool> lOpen(true); //Log lock open?
static atomic<bool> rOpen(true); //Reader lock open?
static atomic<bool> wOpen(true); //Writer lock open?
static atomic<bool> csOpen(true); //Critical Section lock open?
static atomic<bool> free2read(true); //Lets readers know they can concurrently read
static atomic<bool> free2write(true); //Lets writers know they can write
static atomic<int> readersCount(0); //Number of active readers
static atomic<int> readersWaiting(0); //Number of waiting readers
static atomic<int> writersCount(0); //Number of active writers
static atomic<int> writersWaiting(0); //Number of waiting writers
static atomic<int> threadsToGo(NUM_THREADS); //Threads until end of simulation
static atomic<int> lastThreadMade(-1); //Tid of the last thread to be made
static atomic<int> rwSeed(42); //Starting seed for thread assignment of R/W
static pthread_mutex_t lMtx = PTHREAD_MUTEX_INITIALIZER; //Mutex for log
static pthread_cond_t lCon = PTHREAD_COND_INITIALIZER; //Condition for log
static pthread_mutex_t csMtx = PTHREAD_MUTEX_INITIALIZER; //Mutex for critical section
static pthread_cond_t csCon = PTHREAD_COND_INITIALIZER; //Condition for critical section
static pthread_mutex_t rMtx = PTHREAD_MUTEX_INITIALIZER; //Mutex for reader count
static pthread_cond_t rCon = PTHREAD_COND_INITIALIZER; //Condition for reader count
static pthread_mutex_t wMtx = PTHREAD_MUTEX_INITIALIZER; //Mutex for writer count
static pthread_cond_t wCon = PTHREAD_COND_INITIALIZER; //Condition for writer count

class readWriteSTM {
public:
    /*
    tid:    The thread's ID (-1 default represents the processor)
    lpCnt:  The current loop the thread is on
    rw:     Is the thread a reader or writer?
    The thread struct keeps all information relevant to a single thread in
    a single object for easy access of information.
    */
    struct thread {
        //Tid is -1 by default, must be given a value
        thread() : tid(-1) {}
        pthread_t th; //The thread to be used
        int tid; //Should be: (0 <= tid < NUM_THREADS)
        int lpCnt; //Should be: (0 <= lpCnt < NUM_LOOPS)
        int rw; //Should be 1 for Writer, 0 for Reader
    };
    const thread stmProcessor; //Dummy thread to represent the processor (used for log)
    //The following two variables are used to create the Reader/Writer
    //distribution amongst the threads. The distribution is as such:
    //If a number given is between 0 and rwSplit, the result is a reader
    //If a number given is between rwSplit and rwTotal, the result is a reader
    //e.g. with a rwTotal of 100 and a rwSplit of 50, there is a 50/50 chance
    //the thread will be a reader or writer
    static const int rwTotal = 100; //Should be greater than rwSplit
    static const int rwSplit = 50; //Should be less than rwTotal
    std::queue<int> waitingQueue; //Queue that is used in some RWP solutions
    //Array of threads that are to be all allocated of used for testing
    thread threads[NUM_THREADS];
    readWriteSTM();
    ~readWriteSTM();
    //Weak Reader Preference: When a reader is in the critical section, a
    //writer must wait until all readers exit
    int wrp(thread);
    //Strong Reader Preference: If a writer is writing and another writer is
    //waiting, an arriving reader will get in first
    int srp(thread);
    //Weak Writer Preference: If a writer is writing, then waiting writers go first
    int wwp(thread);
    //Strong Writer Preference: Arriving writers go next
    int swp(thread);
    //Fair Preference: Whoever arrives next goes next (default option)
    int fair(thread);
    //First Come First Serve: Control algorithm (no concurrency)
    int fcfs(thread);
    //Creates NUM_THREAD amount of threads and then sends them to be linked
    //to the algorithm picked or the default (default is 'fair')
    void makingThreads(int s=0);
    //Writes a message to the log file. Uses mutex locks since multiple
    //threads will be attempting to gain this resource. The third parameter
    //indicates type and will default to 0 indicating a normal log message
    void logMsg(std::string, thread, int t=0);

private:
    //The current state of each thread. Is a parallel array to threads[]
    int currentStates[NUM_THREADS];
    int currentSTM; //The current algoithm to test with each thread
    void scheduleSTM(int); //Sets the current algorithm to test
    void startProcess(int); //Starts the current threads process/job
    //Lock the given mutex if unlocked and block if it is locked already
    void lockMutex(pthread_mutex_t&, pthread_cond_t&, atomic<bool>&);
    //Unlock the given mutex and signal any waiting threads
    void unlockMutex(pthread_mutex_t&, pthread_cond_t&, atomic<bool>&);
    //Necessary function to link the thread to its process to execute. Acts as
    //a middle man between thread initialization and process function
    static void *linkThread(void*);
    //Print dots to the console to show the user the simulation is not stuck
    static void *consoleFeedback(void*);
    //Get the current duration time in microseconds at this point in the simulation
    std::string getTime() const;
    //Get the current duration in hours, minutes and seconds
    std::string stmDuration() const;
};
#endif
