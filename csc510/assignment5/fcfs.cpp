/*
Author:     Christian Carreras
Date:       12/04/17
Due Date:   12/12/17
File:       fcfs.cpp
Assignment: #5
Course:     CSC510 Advanced Operating Systems
Professor:  Dr. Parson
University: Kutztown University of Pennsylvania
About:      This file serves a control algorithm compared to the other solutions
            to the readers writers problem. This solution does not allow for
            concurrency among readers and therefore only one reader or writer
            is allowed in the critical section at a time. By not having 
            concurrency, this implementation should easily show the benefits of 
            concurrent readers as part of a solution. With more readers than
            writers this will become even more apparent. It is suggested to
            run this program along with another solution to see how much time
            is saved with concurrency implemented. Is similar to the fair
            solution with the FIFO queue but without effects of concurrency.
*/
#include <iostream>
#include <functional> //ref() function to wrap atomic variable parameters
#include "readWriteSTM.h"
using namespace std;

/*
Function Name:  fcfs
Function Type:  mutator
Parameters:     thread - the calling thread and all its information
Returns:        int - the status of the state machine
About:          Evaluates first come first serve solution to the readers writers
                problem. Each thread must wait their turn to enter the critical
                section. Only one thread may be in the critical section at a
                time regardless of reader/writer status.
*/
int readWriteSTM::fcfs(thread evalThread) {
    switch (currentStates[evalThread.tid]) {
        case STATE_INIT: //Initial state where freshly created threads start
            logMsg("init, ARRIVE", evalThread);
            currentStates[evalThread.tid] = STATE_WAIT; //Go wait to get in cs
            logMsg("init, DEPART", evalThread);
            return(KEEP_GOING);

        case STATE_WAIT: //Wait here for the critical section to open
            logMsg("wait, ARRIVE", evalThread);
            waitingQueue.push(evalThread.tid);
            //Wait in line for your turn, first in first out
            while(waitingQueue.front() != evalThread.tid) {}
            //Mutex lock is first come first serve
            logMsg("trying lock on mutex", evalThread, 1);
            lockMutex(csMtx, csCon, ref(csOpen)); //Only admit one R or W
            logMsg("acquired the mutex", evalThread, 1);
            waitingQueue.pop(); //Remove yourself from the waiting queue
            currentStates[evalThread.tid] = STATE_CRITSECT;
            logMsg("wait, DEPART", evalThread);
            return(KEEP_GOING);
        
        //This control critical section can only hold one reader or writer at a
        //time i.e. no concurrancy is allowed in this critical section.
        case STATE_CRITSECT:
            logMsg("critSec, ARRIVE", evalThread);
            if(evalThread.rw == READER) { //Readers Only
                logMsg("reader in critical section, sleeping...", evalThread, 1);
                usleep(SLEEP_READER); //Sleep to represent doing something
            }
            else { //(evalThread.rw == WRITER) Writers Only
                logMsg("writer in critical section, sleeping...", evalThread, 1);
                usleep(SLEEP_WRITER); //Sleep to represent doing something
            }
            unlockMutex(csMtx, csCon, ref(csOpen)); //Unlock the cs
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
int readWriteSTM::fair(thread evalThread) {}
int readWriteSTM::wrp(thread evalThread) {}
int readWriteSTM::srp(thread evalThread) {}
int readWriteSTM::wwp(thread evalThread) {}
int readWriteSTM::swp(thread evalThread) {}

int main(int argc, char **argv) {
    readWriteSTM * stm = new readWriteSTM();
    cout << "FCFS Preference" << endl;
    stm->makingThreads(STM_FCFS); //Start the STM with FCFS Preference
    return 0;
}
