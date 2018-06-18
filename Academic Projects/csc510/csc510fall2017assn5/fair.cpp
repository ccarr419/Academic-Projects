/*
Author:     Christian Carreras
Date:       12/04/17
Due Date:   12/12/17
File:       fair.cpp
Assignment: #5
Course:     CSC510 Advanced Operating Systems
Professor:  Dr. Parson
University: Kutztown University of Pennsylvania
About:      This file defines the code for the fair solution to the readers
            writers problem. Once compiled this project will also be able to
            simulate the fair solution. The fair solution uses a FIFO queue to 
            sort incoming readers and writers along with mutexes to lock the 
            critical section. However, it is more special than a basic FIFO
            queue in the fact that it allows for (along with most other R/W 
            solutions) concurrent readers in the critical section. Thus, when
            a reader is in the critical section and a reader is waiting, the
            waiting reader will be able to enter the critical section along
            with other readers and so on. This concurrency allows for quite a
            remarkable speed-up with little worry of starvation. Behaves 
            exactly like weak readers preference but with a queue.
*/
#include <iostream>
#include <functional> //ref() function to wrap atomic variable parameters
#include "readWriteSTM.h"
using namespace std;

/*
Function Name:  fair
Function Type:  mutator
Parameters:     thread - the calling thread and all its information
Returns:        int - the status of the state machine
About:          Evaluates the fair preference solution to the readers writers
                problem. This solution states that whoever arrives next gets
                to go next. This is the default algorithm.
*/
int readWriteSTM::fair(thread evalThread) {
    switch (currentStates[evalThread.tid]) {
        case STATE_INIT: //Initial state where freshly created threads start
            logMsg("init, ARRIVE", evalThread);
            currentStates[evalThread.tid] = STATE_WAIT; //Go wait to get in cs
            logMsg("init, DEPART", evalThread);
            return(KEEP_GOING);
        
        //All threads will wait their turn to go into the critical section
        //This state makes writers wait until all readers exit the critical
        //section and lets the next reader inline enter the critical section if
        //there is a reader in the critical section already
        case STATE_WAIT: //Wait here for the critical section to open
            logMsg("wait, ARRIVE", evalThread);
            //Be put in a waiting queue and wait your turn
            waitingQueue.push(evalThread.tid);
            //Do not go any further unless it is your turn
            while(waitingQueue.front() != evalThread.tid) {}

            logMsg("trying lock on mutex", evalThread, 1);
            if(evalThread.rw == READER) { //Readers Only  
                //Make sure you are the only reader doing this
                lockMutex(rMtx, rCon, ref(rOpen));
                // BEGIN READER COUNT CRITICAL SECTION
                if(++readersCount == 1) { //Increment the active reader count
                    //Lock or wait for the cs lock if the first reader
                    lockMutex(csMtx, csCon, ref(csOpen));
                }
                // END READER COUNT CRITICAL SECTION
                unlockMutex(rMtx, rCon, ref(rOpen)); //Let other readers come in
                logMsg("acquired the mutex", evalThread, 1);
                waitingQueue.pop(); //Remove yourself from the waiting queue
                currentStates[evalThread.tid] = STATE_CRITSECT;
            }
            //Writers are non-concurrent and must have exclusive access
            else { //(evalThread.rw == WRITER) Writers Only
                lockMutex(csMtx, csCon, ref(csOpen)); //Lock or wait for the cs lock
                logMsg("acquired the mutex", evalThread, 1);
                //Going to the critical section, remove self from waiting queue
                waitingQueue.pop();
                currentStates[evalThread.tid] = STATE_CRITSECT;
            }
            logMsg("wait, DEPART", evalThread);
            return(KEEP_GOING);
        
        //The critical section can concurrently hold multiple readers or
        //only one writer at a time
        case STATE_CRITSECT:
            logMsg("critSec, ARRIVE", evalThread);
            //If a reader is in the critical section, the critical section will
            //remained locked until all readers exit
            if(evalThread.rw == READER) {
                logMsg("reader in critical section, sleeping...", evalThread, 1);
                usleep(SLEEP_READER); //Sleep to represent doing something
                lockMutex(rMtx, rCon, ref(rOpen));
                // BEGIN READER COUNT CRITICAL SECTION
                if(--readersCount == 0) { //Unlock the cs mutex if no more readers
                    unlockMutex(csMtx, csCon, ref(csOpen));
                }
                unlockMutex(rMtx, rCon, ref(rOpen)); //Let other readers in
                // END READER COUNT CRITICAL SECTION
            }
            //Writers are non-concurrent and must have exclusive access
            else { //(evalThread.rw == WRITER)
                logMsg("writer in critical section, sleeping...", evalThread, 1);
                usleep(SLEEP_WRITER); //Sleep to represent doing something
                unlockMutex(csMtx, csCon, ref(csOpen)); //Unlock the cs
            }
            //The task is done go to the terminate state
            currentStates[evalThread.tid] = STATE_TERMINATE;
            logMsg("critSec, DEPART", evalThread);
            return(KEEP_GOING);

        case STATE_TERMINATE: //End the current task for the thread
            logMsg("terminate, ARRIVE", evalThread);
            return(STOP_GOING); //Reached the accept state

        default: //Should never reach this state but for good measure
            logMsg("error: illegal state", evalThread);
            //I do no know how you got here but I am putting a stop to it!
            return(STOP_GOING);
    }
}

//Put other solution function declarations here so readWriteSTM.cpp can know 
//they exist when it selects which algorithm to use. Otherwise the program
//will not compile because these functions will not be defined.
int readWriteSTM::wrp(thread evalThread) {}
int readWriteSTM::srp(thread evalThread) {}
int readWriteSTM::wwp(thread evalThread) {}
int readWriteSTM::swp(thread evalThread) {}
int readWriteSTM::fcfs(thread evalThread) {}

int main(int argc, char **argv) {
    readWriteSTM * stm = new readWriteSTM();
    cout << "Fair Preference" << endl;
    stm->makingThreads(STM_FAIR); //Start the STM with Fair Preference
    return 0;
}
