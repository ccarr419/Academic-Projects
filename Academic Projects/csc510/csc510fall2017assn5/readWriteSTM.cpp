/*
Author:     Christian Carreras
Date:       12/04/17
Due Date:   12/12/17
File:       readWriteSTM.cpp
Assignment: #5
Course:     CSC510 Advanced Operating Systems
Professor:  Dr. Parson
University: Kutztown University of Pennsylvania
About:      This project's goal is to create a state machine that successfully
            implements solutions to the Readers/Writers Problem. There are
            five solutions that this project implements. Weak Reader Preference,
            Strong Reader Preference, Weak Writer Preference, Strong Writer
            Preference, and Fair. Each successfully deals with the problem
            but some are faster and more efficient than others. A problem that
            occurs with some of the methods (namely the 'strong' preferences)
            is starvation. The Readers/Writers problem has no remedy for
            starvation since it is a byproduct of some of its more harsh
            implementations. Thus starvation must be weighed against the
            benefits and what the scheduler is trying to achieve. FCFS is
            added as a control algorithm to show the benefits of alternate
            solutions which implement concurrency among readers. Implementation
            of the scheduler functions are to be carried out in their own
            individual files. As such only functions which set up and tear down
            the actual STM are implemented here for consitency. The main
            solution of all the RW alogrithms is the use concurrency among
            readers i.e. multiple readers are allowed in the critical section.
            Writers are not allowed to be concurrent and thus each writer must 
            have exclusive access to the critical section always.
*/
#include <iostream>
#include <fstream> //Log Tools
#include <sstream> //Log Tools
#include <iomanip> //Log Tools
#include <deque> //Thread Queueing
#include <chrono> //Timing
#include <cstdatomic> //Atomic variables
#include <pthread.h> //Threads
#include "readWriteSTM.h"
using namespace std;

//Time variable used to get the programs duration
static auto timeStart = chrono::high_resolution_clock::now();

/*
Function Name:  readWriteStm
Function Type:  constructor
Parameters:     n/a
Returns:        n/a
About:          Constructs the STM object by opening the log and starting
                off each thread to be create at the init state.
*/
readWriteSTM::readWriteSTM() {
    logFile.open("readWriteSTM.log");
}

/*
Function Name:  ~readWriteStm
Function Type:  destructor
Parameters:     n/a
Returns:        n/a
About:          Terminates the STM by closing the log and destroying all
                mutexes and condition objects in use.
*/
readWriteSTM::~readWriteSTM() {
    logFile.close(); //Close the log file to prevent mishaps
    //Destroy all mutexes and conditions just to be sure
    pthread_mutex_destroy(&lMtx);
    pthread_cond_destroy(&lCon);
    pthread_mutex_destroy(&csMtx);
    pthread_cond_destroy(&csCon);
    pthread_mutex_destroy(&rMtx);
    pthread_cond_destroy(&rCon);
    pthread_mutex_destroy(&wMtx);
    pthread_cond_destroy(&wCon);
}

/*
Function Name:  makingThreads
Function Type:  mutator
Parameters:     int - the number representing the algorithm to use
Returns:        n/a
About:          Represents a processor creating threads and delegating tasks
                to them. The processor waits a certain amount of time between
                creating threads to prevent race conditions. Once all threads
                have been succesfully created, the processor waits until all
                threads have completed their task before terminating.
*/
void readWriteSTM::makingThreads(int algor) {
    int t; //Hold return value from thread creation to check for errors
    currentSTM = algor; //Set the testing algorithm
    stringstream sMsg; //Custom log message
    timeStart = chrono::high_resolution_clock::now(); //Get processor start time
    logMsg("creating threads", stmProcessor);
    pthread_t consoleThread; //Thread for console feedback
    t = pthread_create(&consoleThread, NULL, consoleFeedback, NULL);
    //If the thread failed to be created, end the simulation
    if(t) {
        logMsg("error: failed to create console thread", stmProcessor);
        return;
    }
    //Spawn threads and link them to their tasks. All threads will execute
    //a single predetermined algorithm
    for(int i = 0; i < NUM_THREADS; i++) {
        sMsg << "spawning thread " << i;
        logMsg(sMsg.str(), stmProcessor);
        sMsg.str(string());
        t = pthread_create(&threads[i].th, NULL, linkThread, (void*)this);
        //If the thread failed to be created, end the simulation
        if(t) {
            logMsg("error: failed to create thread", stmProcessor);
            return;
        }
        usleep(SLEEP_THREAD); //Sleep a small amount between spawning threads to prevent
        //race conditions and deadlock
    }
    logMsg("done spawning threads", stmProcessor);
    //Wait here until all threads terminate
    while(threadsToGo) {}
    //Print how long it took to complete the simulation
    cout << endl << "real\t" << stmDuration() << endl;
    logMsg("simulation complete, exiting", stmProcessor);
    //Wait until the consoleThread terminates and joins
    pthread_join(consoleThread, NULL);
}

/*
Function Name:  startProcess
Function Type:  mutator
Parameters:     int - the current thread (i.e. the threads tid)
Returns:        n/a
About:          Executes the thread's main purpose. The thread will be assigned
                a reader or writer role and be directed to the intitial state
                inside the state machine. The thread will stay in the state
                machine until it reaches the accept (terminate) state. The
                thread will repeat the above steps including the assignment
                of a (possibly different) reader or writer role until the
                amount of loops are completed. Reader and Writer roles are
                psuedo-randomly selected although ratios of readers to writers
                will remain the same.
*/
void readWriteSTM::startProcess(int thrTid) {
    threads[thrTid].tid = thrTid; //Assign a tid to the thread
    for(int lc = 0; lc < NUM_LOOPS; lc++) {
        currentStates[thrTid] = STATE_INIT; //Start the thread at the initial state
        threads[thrTid].lpCnt = lc; //Show which loop iteration the thread is on
        //Get same ratio of R/W but without exact duplicates by using a pseudo-
        //random number generator using a seed number plus the time.
        srand((rwSeed++) + time(NULL));
        int num = rand() % rwTotal; //Create a percentage split between R/W
        threads[thrTid].rw = (num < rwSplit) ? READER : WRITER;
        if(threads[thrTid].rw) logMsg("new writer thread", threads[thrTid], 1);
        else logMsg("new reader thread", threads[thrTid], 1);
        scheduleSTM(thrTid);
        usleep(SLEEP_THREAD); //Sleep between new R/W roles to prevent race conditions
    }
    logMsg("<defunct>", threads[thrTid]);
    threadsToGo--; //Decrement thread count and terminate the thread
    pthread_exit(NULL);
}

/*
Function Name:  scheduleSTM
Function Type:  mutator
Parameters:     int - the current thread (i.e. the threads tid)
Returns:        n/a
About:          Select what algorithm the threads will execute. The default
                algorithm used is the fair algorithm if no algorithm is selected
*/
void readWriteSTM::scheduleSTM(int thrTid) {
    switch(currentSTM) {
        case STM_FAIR: //Use the fair algorithm
            while (fair(threads[thrTid])) {}
            break;
        case STM_WRP: //Use weak reader preference
            while (wrp(threads[thrTid])) {}
            break;
        case STM_SRP: //Use strong reader preference
            while (srp(threads[thrTid])) {}
            break;
        case STM_WWP: //Use weak writer preference
            while (wwp(threads[thrTid])) {}
            break;
        case STM_SWP: //Use strong writer preference
            while (swp(threads[thrTid])) {}
            break;
        case STM_FCFS: //Use first come first serve (No concurrency) preference
            while (fcfs(threads[thrTid])) {}
            break;
        default: //Default will be the fair algorithm
            while (fair(threads[thrTid])) {}
    }
}

/*
Function Name:  *linkThread
Function Type:  mutator
Parameters:     void* - Reference to the current STM object
Returns:        n/a
About:          Since pthreads can only be passed static functions as a 
                parameter, this function acts as a middle man by accepting the 
                STM as a parameter and linking the thread to its actual task.
                This function will also assign a tid to every thread by
                incrementing an atomic thread counter every time a thread
                is linked to a process. The STM has to be passed as a void*
                since pthreads will not accept variables of any other type
                for their function parameter.
*/
void *readWriteSTM::linkThread(void *stmArg) {
    readWriteSTM *stm = (readWriteSTM*) stmArg; //cast back to readWriteSTM
    stm->startProcess(++lastThreadMade); //Give the thread its tid
}

/*
Function Name:  *consoleFeedback
Function Type:  mutator
Parameters:     void* - dummy parameter since pthreads need a parameter
Returns:        n/a
About:          Prints a dot to the screen for every two seconds of real time
                during the STM's execution. This is simply a courtesy to the
                user so they are aware the program is still working properly.
*/
void *readWriteSTM::consoleFeedback(void *d) {
    //Keep printing dots until all threads have completed and terminated
    while(threadsToGo) {
        sleep(2); //Sleep so dots are not printed too fast
        //Check to make sure the threads have not completed while sleeping
        if(!threadsToGo) break;
        cout << '.';
        cout.flush();
    }
    pthread_exit(NULL); //Terminate the console thread once simulation is complete
}

/*
Function Name:  lockMutex
Function Type:  mutator
Parameters:     pthread_mutex_t - the mutex to lock or block
                pthread_cond_t - the signaling condition to wait for if blocked
                atomic<bool> - Represents if the mutex is locked or unlocked
Returns:        n/a
About:          Attempts to acquire the given mutex. If acquired the atmoic bool
                will be switch to false and all future attempts to acquire this
                mutex will block until it is unlocked.
*/
void readWriteSTM::lockMutex(pthread_mutex_t &m, pthread_cond_t &c, atomic<bool> &b) {
    pthread_mutex_lock(&m); //Attempt to acquire mutex
        while(!b) { //Or wait to be signalled that the mutex is open
            pthread_cond_wait(&c, &m);
    }
    b.store(false); //Let others know that the mutex has already been acquired
}

/*
Function Name:  unlockMutex
Function Type:  mutator
Parameters:     pthread_mutex_t - the mutex to unlock
                pthread_cond_t - the condition to signal once unlocked
                atomic<bool> - Represents if the mutex is locked or unlocked
Returns:        n/a
About:          Unlocks the given mutex. Assumes the calling thread is the
                thread that aquired the mutex in the first place.
*/
void readWriteSTM::unlockMutex(pthread_mutex_t &m, pthread_cond_t &c, atomic<bool> &b) {
    b.store(true);
    pthread_cond_signal(&c); //Let other threads know the mutex is unlocked
    pthread_mutex_unlock(&m);
}

/*
Function Name:  logMsg
Function Type:  inspector
Parameters:     string - the message to write the the log
                thread - the current thread calling the log
                int - the type of msg to write
Returns:        n/a
About:          Writes a new line log message in the destination log file. Log
                files will be created if one does not exist or overriden if
                if already exists. Log information includes the time the log
                message was written, the thread writing to the log, the loop
                iteration if applicable, and the message itself. Log messages
                are split into two different types. The default type will
                display 'LOG'. The other type will display 'MSG' and should
                be reserved for special situations or actions in the STM
                i.e. not errors, transitions, thread spawning, termination, etc.
*/
void readWriteSTM::logMsg(string msg, thread th, int type) {
    //Lock the file resource so only one thread can write to it at a time
    lockMutex(lMtx, lCon, lOpen);
    // BEGIN LOG CRITICAL SECTION
        string time = getTime() + ", "; //Display the time of this log entry
        string msgType = (type) ? "MSG, " : "LOG, "; //Display the type of message
        stringstream tORp, lStr;
        //Display whether the calling thread is a normal thread or the processor
        if(th.tid >= 0) { 
            tORp << "thread " << th.tid << ", "; //Display thread's tid
            lStr << "loop " << th.lpCnt << ", "; //Display thread's loop iteration
        }
        else { tORp << "processor, "; }
        logFile << time << msgType << tORp.str() << lStr.str() << msg << endl;
    // END LOG CRITICAL SECTION
    unlockMutex(lMtx, lCon, lOpen); //Unlock and let the next log writer in
}

/*
Function Name:  getTime
Function Type:  facilitator
Parameters:     n/a
Returns:        string - the current duration of the STM in microseconds
About:          Will compute and return the duration since the STM began
                inserted into a string. The time will always be twelve numbers
                long, padded with leading zeroes if necessary. Units use to
                measure duration is microseconds as it fits best since
                milliseconds is not accurate enough and nanoseonds is too
                granular of a level, even for an average computer. 
                Fun fact: Since the string is twelve characters long, there is 
                a maximum duration of around 11 days, 13 hours, 46 minutes and
                40 seconds before the string will have to add another digit.
*/
string readWriteSTM::getTime() const {
    using namespace chrono; //So chrono:: does not have to be typed every time
    stringstream time;
    //Get the time this function was called and subtract the time the STM
    //started to find the current duration
    auto timeEnd = high_resolution_clock::now();
    //Cast duration to microseconds for best accuracy
    auto ticks = duration_cast<microseconds>(timeEnd-timeStart);
    time << setfill('0') << setw(12) << ticks.count(); //Add leading zeroes
    return time.str();
}

/*
Function Name:  stmDuration
Function Type:  facilitator
Parameters:     n/a
Returns:        string - the current duration of the STM in microseconds
About:          Behaves similarly to the function getTime but instead of
                return duration in microseconds, the duration is split between
                hours minutes and seconds. Only seconds will act like a floating-
                point number. Hours and minutes will only be integers. Seconds
                acts like a floating point number by adding a decimal point
                and the left over milliseconds to the string.
*/
string readWriteSTM::stmDuration() const {
    using namespace chrono; //So chrono:: does not have to be typed every time
    stringstream time;
    //Get the time this function was called and subtract the time the STM
    //started to find the current duration
    auto timeEnd = high_resolution_clock::now();
    auto ticks = duration_cast<microseconds>(timeEnd-timeStart);
    //Get the duration in hours, minutes and milliseconds.
    //Microseconds and nanoseconds are too granular for this display
    //Likewise, duration in days makes no sense as well
    hours h = duration_cast<hours>(ticks);
    minutes m = duration_cast<minutes>(ticks);
    seconds s = duration_cast<seconds>(ticks);
    milliseconds ms = duration_cast<milliseconds>(ticks);
    int shortM = (m.count() - (h.count()*60)); //Do not allow over 60 minutes
    int shortS = (s.count() - (m.count()*60)); //Do not allow over 60 seconds
    int shortMs = (ms.count() - (s.count()*1000)); //Do not allow over 1000 ms
    time << h.count() << "h " << shortM << "m " << setfill('0') << setw(2);
    //Make sure the are 3 digits in ms since there is 1/1000 ms in a second
    time << shortS << "." << setfill('0') << setw(3) << shortMs << "s";
    return time.str();
}
