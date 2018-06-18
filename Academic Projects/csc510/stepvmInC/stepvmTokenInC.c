/**
 *  stepvmTokenInC.c Dale Parson Summer & Fall 2017
 *  This is a token-threaded VM example that we will use in
 *  assignment 1 of CSC510 Advanced Operating Systems, Fall 2017.
 *  See stepvmInC.h for the primary documentation comments.
**/
#include <stdio.h>
#include <assert.h>
#include "stepvmInC.h"
#ifndef DEBUGVM
#define NDEBUG 1
#endif
/* NDEBUG disables assert checks */

/* C non-encapsulated alternatives to C++ member functions: */
/* Initialize the data fields and arrays per docs in stepvmInC.h. */
void stepvmInC_constructor(struct stepvmInC *addressOfVM,
    stepdata_t *dataStackParam, int32_t topdsParam,
    stepdata_t *staticMemoryParam, int32_t staticMemoryParamElems,
    stepaddr_t *callStackParam, int32_t topcsParam,
    stepcode_t *codeMemoryParam, int32_t codeMemoryParamSize,
    int8_t isSupervisorModeParam) {
    memset(addressOfVM, 0, sizeof(struct stepvmInC)); /* zero all data */
    addressOfVM->topds = (topdsParam > 0) ? topdsParam : 0 ;
    addressOfVM->topcs = (topcsParam > 0) ? topcsParam : 0 ;
    addressOfVM->isSupervisorMode = (isSupervisorModeParam != 0) ;
    if (dataStackParam != NULL && topdsParam > 0) {
        memcpy(addressOfVM->dataStack, dataStackParam,
            topdsParam * sizeof(addressOfVM->dataStack[0]));
    }
    if (staticMemoryParam != NULL && staticMemoryParamElems > 0) {
        memcpy(addressOfVM->staticMemory, staticMemoryParam,
            staticMemoryParamElems * sizeof(addressOfVM->staticMemory[0]));
    }
    if (callStackParam != NULL && topcsParam > 0) {
        memcpy(addressOfVM->callStack, callStackParam,
            topcsParam * sizeof(addressOfVM->callStack[0]));
    }
    if (codeMemoryParam != NULL && codeMemoryParamSize > 0) {
        memcpy(addressOfVM->codeMemory, codeMemoryParam,
            codeMemoryParamSize * sizeof(addressOfVM->codeMemory[0]));
    }
}

void dump_stepvmInC(struct stepvmInC *vm) {
    int i ;
    fprintf(stderr,"DUMP OF VM:\n");
    fprintf(stderr,"\tip = %d, isSupervisorMode = %d, topds = %d, topcs = %d\n",
        (int)(vm->ip),
        (int)(vm->isSupervisorMode),(int)(vm->topds),(int)(vm->topcs));
    fprintf(stderr,"\tlower_user_ip = %d, upper_user_ip = %d\n",
        (int)(vm->lower_user_ip),(int)(vm->upper_user_ip));
    fprintf(stderr,"\tlower_user_static = %d, upper_user_static = %d\n",
        (int)(vm->lower_user_static),(int)(vm->upper_user_static));
    for (i = vm->topds-1 ; i >= 0 ; i--) {
        fprintf(stderr,"\t\tdataStack[%d] = %ld\n",i,(long)(vm->dataStack[i]));
    }
    for (i = vm->topcs-1 ; i >= 0 ; i--) {
        fprintf(stderr,"\t\tcallStack[%d] = %d\n",i,(int)(vm->callStack[i]));
    }
    for (i = 0 ; i <= ((int)(vm->upper_user_static)) ; i++) {
        fprintf(stderr,"\t\tstaticMemory[%d] = %ld\n",i,(long)(vm->staticMemory[i]));
    }
    for (i = 0 ; i <= ((int)(vm->upper_user_ip)) ; i++) {
        fprintf(stderr,"\t\tcodeMemory[%d] = %d\n",i,(int)(vm->codeMemory[i]));
    }
    fflush(stderr);
}

void run_stepvmInC(struct stepvmInC *vm, int dumpOnTermination) {
    stepdata_t accum ;
    int scanbuf ;
    vm->ip = 0 ;
    while (1) {
        stepcode_t opcode = vm->codeMemory[vm->ip];
#ifdef DEBUGVM
        dump_stepvmInC(vm);
#endif
        vm->ip += 1 ;   /* point to in-line data or next instruction */
        switch(opcode) {
            /** USER MODE INSTRUCTIONS, see stepvmInC.h **/
            case STEP_LADD :
                vm->dataStack[vm->topds-2]
                    = vm->dataStack[vm->topds-2] + vm->dataStack[vm->topds-1];
                vm->topds -= 1 ;
                break ;
            case STEP_LSUB :
                vm->dataStack[vm->topds-2]
                    = vm->dataStack[vm->topds-2] - vm->dataStack[vm->topds-1];
                vm->topds -= 1 ;
                break ;
            case STEP_LMULT :
                vm->dataStack[vm->topds-2]
                    = vm->dataStack[vm->topds-2] * vm->dataStack[vm->topds-1];
                vm->topds -= 1 ;
                break ;
            case STEP_LDIV :
                vm->dataStack[vm->topds-2]
                    = vm->dataStack[vm->topds-2] / vm->dataStack[vm->topds-1];
                vm->topds -= 1 ;
                break ;
            case STEP_LMOD :
                vm->dataStack[vm->topds-2]
                    = vm->dataStack[vm->topds-2] % vm->dataStack[vm->topds-1];
                vm->topds -= 1 ;
                break ;
            case STEP_LSHL :
                vm->dataStack[vm->topds-2]
                    = vm->dataStack[vm->topds-2] << vm->dataStack[vm->topds-1];
                vm->topds -= 1 ;
                break ;
            case STEP_LSHR :
                vm->dataStack[vm->topds-2]
                    = vm->dataStack[vm->topds-2] >> vm->dataStack[vm->topds-1];
                vm->topds -= 1 ;
                break ;
            case STEP_LBITAND :
                vm->dataStack[vm->topds-2]
                    = vm->dataStack[vm->topds-2] & vm->dataStack[vm->topds-1];
                vm->topds -= 1 ;
                break ;
            case STEP_LBITOR :
                vm->dataStack[vm->topds-2]
                    = vm->dataStack[vm->topds-2] | vm->dataStack[vm->topds-1];
                vm->topds -= 1 ;
                break ;
            case STEP_LBITXOR :
                vm->dataStack[vm->topds-2]
                    = vm->dataStack[vm->topds-2] ^ vm->dataStack[vm->topds-1];
                vm->topds -= 1 ;
                break ;
            case STEP_LCOMPLEMENT :
                vm->dataStack[vm->topds-1] = ~vm->dataStack[vm->topds-2] ;
                break ;
            case STEP_LLOGAND :
                vm->dataStack[vm->topds-2]
                    = vm->dataStack[vm->topds-2] && vm->dataStack[vm->topds-1];
                vm->topds -= 1 ;
                break ;
            case STEP_LLOGOR :
                vm->dataStack[vm->topds-2]
                    = vm->dataStack[vm->topds-2] || vm->dataStack[vm->topds-1];
                vm->topds -= 1 ;
                break ;
            case STEP_LLOGNOT :
                vm->dataStack[vm->topds-1] = !vm->dataStack[vm->topds-2] ;
                break ;
            case STEP_DUP :
                vm->dataStack[vm->topds] = vm->dataStack[vm->topds-1] ;
                vm->topds += 1 ;
                break ;
            case STEP_DUP2 :
                vm->dataStack[vm->topds] = vm->dataStack[vm->topds-1] ;
                vm->dataStack[vm->topds+1] = vm->dataStack[vm->topds-1] ;
                vm->topds += 2 ;
                break ;
            case STEP_OVER :
                vm->dataStack[vm->topds] = vm->dataStack[vm->topds-2] ;
                vm->topds += 1 ;
                break ;
            case STEP_OVER2 :
                vm->dataStack[vm->topds] = vm->dataStack[vm->topds-3] ;
                vm->topds += 1 ;
                break ;
            case STEP_SWAP :
                accum = vm->dataStack[vm->topds-1];
                vm->dataStack[vm->topds-1] = vm->dataStack[vm->topds-2];
                vm->dataStack[vm->topds-2] = accum ;
                break ;
            case STEP_SWAP2 :
                accum = vm->dataStack[vm->topds-1];
                vm->dataStack[vm->topds-1] = vm->dataStack[vm->topds-3];
                vm->dataStack[vm->topds-3] = accum ;
                break ;
            case STEP_LFETCH :
                accum = vm->dataStack[vm->topds-1];
                assert(accum >= vm->lower_user_static
                    && accum <= vm->upper_user_static);
                /* assert stands in for an MMU check */
                vm->dataStack[vm->topds-1]
                    = vm->staticMemory[accum];
                break ;
            case STEP_LSTORE :
                accum = vm->dataStack[vm->topds-1];
                assert(accum >= vm->lower_user_static
                    && accum <= vm->upper_user_static);
                /* assert stands in for an MMU check */
                vm->staticMemory[accum] = vm->dataStack[vm->topds-2];
                vm->topds -= 2 ;
                break ;
            case STEP_GOTO :
                accum = vm->codeMemory[vm->ip];
                /* vm->ip += 1 ; */
                assert(accum >= vm->lower_user_ip
                    && accum <= vm->upper_user_ip);
                vm->ip = accum ;
                break ;
            case STEP_GOTO0 :
                accum = vm->codeMemory[vm->ip];
                vm->ip += 1 ;
                if (vm->dataStack[vm->topds-1] == 0) {
                    vm->ip = accum ;
                    assert(accum >= vm->lower_user_ip
                        && accum <= vm->upper_user_ip);
                }
                vm->topds -= 1 ;
                break ;
            case STEP_CALL :
                accum = vm->codeMemory[vm->ip];
                vm->callStack[vm->topcs] = vm->ip + 1 ; /* next instruction */
                vm->topcs += 1 ;
                assert(accum >= vm->lower_user_ip
                    && accum <= vm->upper_user_ip);
                vm->ip = accum ;
                break ;
            case STEP_RETURN :
                vm->topcs -= 1 ;
                accum = vm->callStack[vm->topcs] ;
                vm->ip = accum ;
                assert(accum >= vm->lower_user_ip
                    && accum <= vm->upper_user_ip);
                break ;
            case STEP_SYSCALL :
                /* Implementation note - instead of running emulated code,
                 * we'll just do the valid syscalls here.
                */
                vm->isSupervisorMode = 1 ;
                accum = vm->dataStack[vm->topds-1];
                if (accum == 0) {
                    int buf ;
                    buf = 0 ;
#ifdef DEBUGVM
                    fprintf(stderr, "INPUTTING STDIN\n");
                    fflush(stderr);
#endif
                    fscanf(stdin, "%d", &buf);
                    vm->dataStack[vm->topds-1] = buf ;
                } else if (accum == 1) {
                    fprintf(stdout, "%ld\n",
                        (long)(vm->dataStack[vm->topds-2]));
                    vm->topds -= 2 ;
                } else if (accum == 2) {
                    vm->topds -= 1 ;
                    if (dumpOnTermination) {
                        dump_stepvmInC(vm);
                        fprintf(stderr,"SYSCALL(2) termination.\n");
                    }
                    return ;
                } else {
                    dump_stepvmInC(vm);
                    fprintf(stderr,"INVALID SYSCALL(%ld)\n",(long)accum);
                    return ;
                }
                break ;
            case STEP_CONST :
                vm->dataStack[vm->topds] = vm->codeMemory[vm->ip];
                vm->topds += 1 ;
                vm->ip += 1 ;
                break ;
            case STEP_DROP :
                vm->topds -= 1 ;
                break ;
            case STEP_DROP2 :
                vm->topds -= 2 ;
                break ;
            /* PRIVILEGED INSTRUCTIONS */
            case STEP_SYSRETURN :
                if (! vm->isSupervisorMode) {
                    dump_stepvmInC(vm);
                    fprintf(stderr,"ILLEGAL STEP_SYSRETURN from User mode.\n");
                    return ;
                }
                vm->isSupervisorMode = 0 ;
                vm->topcs -= 1 ;
                accum = vm->callStack[vm->topcs] ;
                vm->ip = accum ;
                assert(accum >= vm->lower_user_ip
                    && accum <= vm->upper_user_ip);
                break ;
            case STEP_LINPUT :
                if (! vm->isSupervisorMode) {
                    dump_stepvmInC(vm);
                    fprintf(stderr,"ILLEGAL STEP_LINPUT from User mode.\n");
                    return ;
                }
#ifdef DEBUGVM
                fprintf(stderr, "INPUTTING STDIN\n");
                fflush(stderr);
#endif
                scanbuf = 0 ;
                fscanf(stdin, "%d", &scanbuf);
                vm->dataStack[vm->topds] = scanbuf ;
                vm->topds += 1 ;
                break ;
            case STEP_LOUTPUT :
                if (! vm->isSupervisorMode) {
                    dump_stepvmInC(vm);
                    fprintf(stderr,"ILLEGAL STEP_LOUTPUT from User mode.\n");
                    return ;
                }
                fprintf(stdout, "%ld\n",
                        (long)(vm->dataStack[vm->topds-1]));
                vm->topds -= 1 ;
                break ;
            case STEP_LDATAMEM :
                if (! vm->isSupervisorMode) {
                    dump_stepvmInC(vm);
                    fprintf(stderr,"ILLEGAL STEP_LDATAMEM from User mode.\n");
                    return ;
                } else if (! (vm->dataStack[vm->topds-2]
                        <= vm->dataStack[vm->topds-1])) {
                    dump_stepvmInC(vm);
                    fprintf(stderr,"STEP_LDATAMEM invalid args: %ld %ld\n",
                        (long)(vm->dataStack[vm->topds-2]),
                        (long)(vm->dataStack[vm->topds-1]));
                    return ;
                }
                vm->lower_user_static = vm->dataStack[vm->topds-2] ;
                vm->upper_user_static = vm->dataStack[vm->topds-1];
                vm->topds -= 2 ;
                break ;
            case STEP_LCODEMEM :
                if (! vm->isSupervisorMode) {
                    dump_stepvmInC(vm);
                    fprintf(stderr,"ILLEGAL STEP_LCODEMEM from User mode.\n");
                    return ;
                } else if (! (vm->dataStack[vm->topds-2]
                        <= vm->dataStack[vm->topds-1])) {
                    dump_stepvmInC(vm);
                    fprintf(stderr,"STEP_LCODEMEM invalid args: %ld %ld\n",
                        (long)(vm->dataStack[vm->topds-2]),
                        (long)(vm->dataStack[vm->topds-1]));
                    return ;
                }
                vm->lower_user_ip = vm->dataStack[vm->topds-2] ;
                vm->upper_user_ip = vm->dataStack[vm->topds-1];
                vm->topds -= 2 ;
                break ;
            case STEP_STARTUSER :
                if (! vm->isSupervisorMode) {
                    dump_stepvmInC(vm);
                    fprintf(stderr,"ILLEGAL STEP_STARTUSER from User mode.\n");
                    return ;
                }
                vm->ip = vm->lower_user_ip ;
                vm->isSupervisorMode = 0 ;
                break ;
            case STEP_TERMINATE_VM :
                if (! vm->isSupervisorMode) {
                    dump_stepvmInC(vm);
                    fprintf(stderr,"ILLEGAL STEP_TERMINATE_VM from User mode.\n");
                    return ;
                }
                if (dumpOnTermination) {
                    dump_stepvmInC(vm);
                    fprintf(stderr,"VM terminated via STEP_TERMINATE_VM\n");
                }
                return ;
            default :
                dump_stepvmInC(vm);
                fprintf(stderr,"ILLEGAL OPCODE %d\n",(int)opcode);
                return;
        }
    }
}

/** TEST PROGRAMS FOR THE VM:
 *  Rather than write a loader in C or write one in Python coupled
 *  here, we will just hard code a series of test cases in arrays,
 *  then load and run them as they appear on main's command line.
 *  Cheap and fast.
 *  STEP_SYSCALL(0) does a STEP_LINPUT.
 *  STEP_SYSCALL(1) does a STEP_LOUTPUT.
 *  STEP_SYSCALL(2) terminates the VM program.
 *  STEP_LDATAMEM gets set at entry and is never modified in the first test.
 *  STEP_LCODEMEM gets set at entry and is never modified in the first test.
**/

/* Start BASIC test: */
static stepcode_t BASIC_codeMemory[] = {
    /* STARTUP CODE IN SUPERVISOR MODE: */
    STEP_CONST, 0, STEP_CONST, (STATIC_MEMORY_SIZE-1), STEP_LDATAMEM,
    STEP_CONST, 17 /* see start of user code below */,
    STEP_CONST, 57 /* see end of user code below */,
    STEP_LCODEMEM,
    STEP_STARTUSER, /* just in case: */ STEP_TERMINATE_VM,
    /* We are now at location [12] in code for syscall(0). */
    STEP_LINPUT, STEP_SYSRETURN,
    /* We are now at location [14] in code for syscall(1). */
    STEP_LINPUT, STEP_SYSRETURN,
    /* We are now at location [16] in code for syscall(2). */
    STEP_TERMINATE_VM,
    /* User program starts at location [17], see STEP_LCODEMEM above. */
    /* User program computes BASE**POWER, hard code long-running values. */
    /* [17] */ STEP_CONST, 2, STEP_CONST, 3, STEP_CALL, 38, /* 2**3 */
                STEP_CONST, 1, STEP_SYSCALL, /* output the result of call */
    /* [26] */ STEP_CONST, 2, STEP_CONST, 62, STEP_CALL, 38, /* 2**62 */
                STEP_CONST, 1, STEP_SYSCALL, /* output the result of call */
    /* [35] */ STEP_CONST, 2, STEP_SYSCALL, /* exit() system call */
    /* [38] is start of the subroutine that computes v1**v2 from stack */
    /* [38] */ STEP_CONST, 1, /* data stack is BASE, POWER, 1 at THIS POINT,
        iterate until power hits 0, then jump to function exit at bottom,
        which cleans up data stack and returns the value. accumulator on top.
    */
    /* [40] */ STEP_OVER /* POWER */, STEP_GOTO0, 53, /* to bottom on done */
    /* [43] */ STEP_OVER2, STEP_LMULT,  /* multiply BASE into accumulator */
    /* [45] */ STEP_OVER, STEP_CONST, 1, STEP_LSUB, STEP_SWAP2, STEP_DROP,
    /* [51] at this point we have updated BASE, POWER, ACCUM, goto loop top */
    /* [51] */ STEP_GOTO, 40, /* 40 is the top of loop */
    /* [53] */ STEP_SWAP, STEP_DROP, STEP_SWAP, STEP_DROP, /* drop POWER BASE */
    /* [57] ACCUM is on stack */
    /* [57] */ STEP_RETURN /* 57 is the last valid user code address */
};
/* End BASIC test: */

int main(int argc, char **argv) {
    static char *USAGE =
    "stepvmInC DUMPONTERMINATION? TEST(e.g.BASIC) REPCOUNT\n";
    int isdump = 1 ;
    int i ;
    struct stepvmInC *vm = (struct stepvmInC *)
        malloc(sizeof(struct stepvmInC));
    stepvmInC_constructor(vm,NULL,0,NULL,0,NULL,0,NULL,0,1);
    if (argc < 4 || ((argc & 1) != 0)) {
        fprintf(stderr, "INVALID COMMAND LINE: ");
        for (i = 0 ; i < argc ; i++) {
            fprintf(stderr, "%s ", argv[i]);
        }
        fprintf(stderr, "\n");
        fprintf(stderr, "%s", USAGE);
        exit(1);
    }
    isdump = atoi(argv[1]);
    for (i = 2 ; i < argc ; i+= 2) {
        int reps = 0 ;
        reps = atoi(argv[i+1]);
        if (reps < 1) {
            fprintf(stderr,"Invalid reps count of %d for %s\n",
                reps, argv[i]);
            exit(1);
        }
        if (strcmp(argv[i], "BASIC") == 0) {
            int j ;
            stepvmInC_constructor(vm,
                NULL,0, /* data stack */
                NULL,0, /* static memory */
                NULL,0, /* call stack */
                BASIC_codeMemory,
                    sizeof(BASIC_codeMemory)/sizeof(BASIC_codeMemory[0]),1);
            for (j = 0 ; j < reps ; j++) {
                run_stepvmInC(vm,isdump);
            }
        } else {
            fprintf(stderr, "Invalid command line arg: %s\n", argv[i]);
            exit(1);
        }
    }
    return 0 ;
}
