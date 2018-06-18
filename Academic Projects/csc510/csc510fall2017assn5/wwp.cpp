/*
Author:     Christian Carreras
Date:       12/04/17
Due Date:   12/12/17
File:       wwp.cpp
Assignment: #5
Course:     CSC510 Advanced Operating Systems
Professor:  Dr. Parson
University: Kutztown University of Pennsylvania
About:      This file defines the code for the weak writer prefence solution to 
            the readers writers problem. Once compiled this project will also 
            be able to simulate the WWP solution. The WWP solution is similar 
            to the WRP solution in that once a reader holds the critical 
            section, it will continue to hold the critical section until all 
            readers are done. In addition to that, if a writer holds the
            critical section, it will continue to hold the critical section
            until all writers are done (minus the concurrency). This results
            in a flipping back and worth between a writer-controlled cs and a
            reader-controlled cs. Surprisingly because of this flip-floppoing
            and grouping of readers and writers, it is one of the fastest
            solutions to the readers writers problem. But because of the nature
            of this grouping, starvation may become an issue.
*/
#include <iostream>
#include <functional> //ref() function to wrap atomic variable parameters
#include "readWriteSTM.h"
using namespace std;

/*
Function Name:  wwp
Function Type:  mutator
Parameters:     thread - the calling thread and all its information
Returns:        int - the status of the state machine
About:          Evaluates weak writer preference solution to the readers writers
                problem. This solution states that if a writer is writing, then
                waiting writers go first (before readers)
*/
int readWriteSTM::wwp(thread evalThread) {
    switch (currentStates[evalThread.tid]) {
        case STATE_INIT: //Initial state where freshly created threads start
            logMsg("init, ARRIVE", evalThread);
            currentStates[evalThread.tid] = STATE_WAIT; //Go wait to get in cs
            logMsg("init, DEPART", evalThread);
            return(KEEP_GOING);
        
        //This state makes writers wait until all readers exit the critical
        //section and lets the waiting readers enter the critical section if
        //there is a reader in the critical section already
        case STATE_WAIT: //Wait here for the critical section to open
            logMsg("wait, ARRIVE", evalThread);
            logMsg("trying lock on mutex", evalThread, 1);
            if(evalThread.rw == READER) { //Readers Only
                lockMutex(rMtx, rCon, ref(rOpen));
                // BEGIN READER COUNT CRITICAL SECTION
                readersCount++;//Increment the active reader count
                // END READER COUNT CRITICAL SECTION
                unlockMutex(rMtx, rCon, ref(rOpen)); //Let other readers come in
                if(writersCount > 0) {
                    while(!free2read) {} //Wait until there are no active writers
                }
                if(readersCount == 1) { //Increment the active reader count
                    //Lock or wait for the cs lock if the first reader
                    lockMutex(csMtx, csCon, ref(csOpen));
                    free2write = false;
                }
                else { free2read = true; }
                logMsg("acquired the mutex", evalThread, 1);
                currentStates[evalThread.tid] = STATE_CRITSECT;
            }

            else { //(evalThread.rw == WRITER) Writers Only
                lockMutex(wMtx, wCon, ref(wOpen));
                // BEGIN WRITER COUNT CRITICAL SECTION
                writersCount++; //Let other threads know there is an active writer
                // END WRITER COUNT CRITICAL SECTION
                unlockMutex(wMtx, wCon, ref(wOpen));
                if(writersCount > 1) {
                    while(!free2write) {} //Wait until there are no active writers
                }
                lockMutex(csMtx, csCon, ref(csOpen)); //Lock or wait for the cs lock
                //Make sure readers are not allowed in the critical section 
                //until all writers are done writing
                free2read = false;
                free2write = false; //Only one writer allowed in cs at a time
                logMsg("acquired the mutex", evalThread, 1);
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
                    free2write = true; //No more readers, let the writers in
                    unlockMutex(csMtx, csCon, ref(csOpen));
                }
                unlockMutex(rMtx, rCon, ref(rOpen)); //Let other readers in
                // END READER COUNT CRITICAL SECTION
            }
            //Writers are non-concurrent and must have exclusive access
            else { //(evalThread.rw == WRITER) 
                logMsg("writer in critical section, sleeping...", evalThread, 1);
                usleep(SLEEP_WRITER); //Sleep to represent doing something
                lockMutex(wMtx, wCon, ref(wOpen));
                // BEGIN WRITER COUNT CRITICAL SECTION
                if(--writersCount > 0) { //Let other threads know there is an active writer
                    free2write = true; //Still more writers, let them in first
                }
                else {
                    free2read = true; //No more writers, let the readers in
                }
                // END WRITER COUNT CRITICAL SECTION
                unlockMutex(wMtx, wCon, ref(wOpen));
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
int readWriteSTM::fair(thread evalThread) {}
int readWriteSTM::wrp(thread evalThread) {}
int readWriteSTM::srp(thread evalThread) {}
int readWriteSTM::swp(thread evalThread) {}
int readWriteSTM::fcfs(thread evalThread) {}

int main(int argc, char **argv) {
    readWriteSTM * stm = new readWriteSTM();
    cout << "Weak Writer Preference" << endl;
    stm->makingThreads(STM_WWP); //Start the STM with WWp Preference
    return 0;
}
