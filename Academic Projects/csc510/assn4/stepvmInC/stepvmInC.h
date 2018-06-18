#ifndef STEPVMINC_H
#define STEPVMINC_H
/**
 *  stepvmInC.h Dale Parson Summer & Fall 2017
 *  This is a token-threaded VM example that we will use in
 *  assignment 1 of CSC510 Advanced Operating Systems, Fall 2017,
 *  to examine additonal types of threaded emulated code in
 *  one or two assignments. I am writing the handout code in
 *  gcc's C language (which includes the && operator for an assignment
 *  See https://gcc.gnu.org/onlinedocs/gcc-3.1.1/gcc/Labels-as-Values.html
 *  C++ would be a bit more modular, e.g., in provision of class member
 *  functions, and provide a nicer I/O library, but I thought it worth
 *  coding this in C as an example, since most O.S. implementation is
 *  done in C for portability combined with effciency.
 *  Documentation for an earlier, token-threaded, more complicated
 *  C++ VM is here:
 *  http://faculty.kutztown.edu/parson/spring2009/step.pdf
 *  Documentation for a more complex stack-based VM in Java is here:
 *  http://acad.kutztown.edu/~parson/javadoc/stepvm/ This Java VM
 *  uses a Java variant of subroutine-threaded code that I suppose
 *  we could call method-threaded code; each emulated op code entails
 *  the overhead of a method call; we could investigate speeding that
 *  one up by changing its threading model. The current VM in stepvmTokenInC.c
 *  follows the original C++ based example, but is missing the
 *  commands buffer of Figure 1. I have changed some of the state
 *  variable names to make them more mnemonic. This one is also a
 *  smaller instruction set.
 *  See https://en.wikipedia.org/wiki/Threaded_code for a decent write-up
 *  in threaded code, inclduing performance.
**/

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
/**
 * Here are the opcodes. Note the numeric gap between the final
 * user-mode instruction and the first system-mode (privileged)
 * instruction. Comments refer to the incoming and outgoing arguments
 * that appear on the dataStack (mostly) or other state-bearing fields
 * in struct stepvmInC. Comments are copied from
 * http://acad.kutztown.edu/~parson/javadoc/stepvm/
 * The data values in this VM are all :L, which are long (64-bit) signed
 * ints; the Java-based VM has other types.
**/
/** USER MODE INSTRUCTIONS **/
#define STEP_LADD (0) /* v1:L v2:L TO (v1+v2):L (with TOS to the right). */
#define STEP_LSUB (1) /* v1:L v2:L TO (v1-v2):L (with TOS to the right). */
#define STEP_LMULT (2) /* v1:L v2:L TO (v1*v2):L (with TOS to the right). */
#define STEP_LDIV (3) /* v1:L v2:L TO (v1/v2):L (with TOS to the right). */
#define STEP_LMOD (4) /* v1:L v2:L TO (v1%v2):L (with TOS to the right). */
#define STEP_LSHL (5) /* v1:L v2:L TO (v1<<v2):L (with TOS to the right). */
#define STEP_LSHR (6) /* v1:L v2:L TO (v1>>v2):L (with TOS to the right). */
#define STEP_LBITAND (7) /* v1:L v2:L TO (v1&v2):L (with TOS to the right). */
#define STEP_LBITOR (8) /* v1:L v2:L TO (v1|v2):L (with TOS to the right). */
#define STEP_LBITXOR (9) /* v1:L v2:L TO (v1^v2):L (with TOS to the right). */
#define STEP_LCOMPLEMENT (10) /* v1:L TO (~v1):L (with TOS to the right). */
#define STEP_LLOGAND (11) /* v1:L v2:L TO (v1&&v2):L (with TOS to the right). */
#define STEP_LLOGOR (12) /* v1:L v2:L TO (v1||v2):L (with TOS to the right). */
#define STEP_LLOGNOT (13) /* v1:L TO (!v1):L (with TOS to the right). */
#define STEP_DUP (14) /* v1:L TO v1 v1 (with TOS to the right). */
#define STEP_DUP2 (15) /* v1:L TO v1 v1 v1 (with TOS to the right). */
#define STEP_OVER (16) /* (x1 x2 -> x1 x2 x1) with TOS to the right */
#define STEP_OVER2 (17) /* v1 v2 v3 TO v1 v2 v3 v1 (with TOS to the right). */
#define STEP_SWAP (18) /* x y TO y x (with top-of-dataStack to the right). */
#define STEP_SWAP2 (19) /* x y z TO z y x (with TOS to the right). */

#define STEP_LFETCH (20) /* address-on-stack TO data (with TOS to the right).
        address is a Long index into static memory in staticMemory */
#define STEP_LSTORE (21) /* v1 address-on-stack TO (none) (TOS to the right).
        address is a Long index into static memory in staticMemory */
#define STEP_GOTO (22) /* in-line address is a long offset in codeMemory */
#define STEP_GOTO0 (23) /* v1 -> (empty), goto in-line addr. if v1 is 0 */
#define STEP_CALL (24) /* in-line address, pushes return ip to controlStack */
#define STEP_RETURN (25) /* pops return ip from controlStack & goes there. */
#define STEP_SYSCALL (26) /* v1 TO (none), v1 is index in syscallTable,
        pushes return ip to controlStack, sets privileged mode */
#define STEP_CONST (27) /* push an in-line data constant to TOS */
#define STEP_DROP (28) /* drops v1 from data stack */
#define STEP_DROP2 (29) /* drops v1,v2 from data stack */
/* PRIVILEGED (SYSTEM MODE) INSTRUCTIONS */
#define STEP_SYSRETURN (32) /* pops return ip from controlStack & goes there,
        resets privileged mode */
#define STEP_LINPUT (33) /* Reads a long word from stdin onto TOS */
#define STEP_LOUTPUT (34) /* Pops & writes TOS to stdout. */
#define STEP_LDATAMEM (35) /* bottom, top -> (none),
        sets user staticMemory range to [bottom,top] inclusive. */
#define STEP_LCODEMEM (36) /* bottom, top -> (none),
        sets user codeMemory range to [bottom,top] inclusive. */
#define STEP_STARTUSER (37) /* Jump to low end of STEP_LCODEMEM in user mode */
#define STEP_TERMINATE_VM (38) /* Terminate execution of this VM with a dump */

/* THE VM DEFINITION STARTS HERE. **/
#define PROGRAM_MEMORY_SIZE 1024
#define STATIC_MEMORY_SIZE 1024
#define DATA_STACK_SIZE 65536
#define CALL_STACK_SIZE 1024
typedef int64_t stepdata_t ;  /* This is the data type on dataStack. */
typedef uint16_t stepaddr_t ;  /* This is the data type on callStack. */
typedef uint32_t stepcode_t ; /* Only up to 256 opcodes, in-line data is big */
struct stepvmInC { /** C++ "class" predecessor, all public, no methods. **/
    /* C language does not check array references for out of bounds!!! */
    stepdata_t dataStack[DATA_STACK_SIZE] ; /* arguments & results */
    stepdata_t staticMemory[STATIC_MEMORY_SIZE]; /* static data memory */
    stepaddr_t callStack[CALL_STACK_SIZE];  /* return addresses for ip */
    stepcode_t codeMemory[PROGRAM_MEMORY_SIZE]; /* 8 bits for compactness,
            256 opcodes max */
    int32_t ip ;
    /* The next 4 registers correspond to registers in a Memory Management
       Unit (MMU) that constrain the range of memory access in user mode. */
    int32_t lower_user_ip ; /* bottom of of user mode mem, STEP_LCODEMEM */
    int32_t upper_user_ip ; /* top of of user mode mem, STEP_LCODEMEM */
    int32_t lower_user_static ; /* bottom of of user mode mem, STEP_LDATAMEM */
    int32_t upper_user_static ; /* top of of user mode mem, STEP_LDATAMEM */
    int32_t topds ; /* Current top entry in dataStack+1, i.e., entry count. */
    int32_t topcs ; /* Current top entry in callStack+1, i.e., entry count. */
    int8_t isSupervisorMode ;
} ;
/* C non-encapsulated alternatives to C++ member functions: */
/**
 *  Initialize the data fields and arrays to zeroes in addressOfVM.
 *  This function can be called to reinitialize a struct stepvmInC.
 *  It loads a program into the VM, but does not execute it.
 *  @param addressOfVM is the VM to initialize.
 *  @param dataStackParam may be NULL, when non-NULL then this function
 *  copies topdsParam elements (not bytes) from dataStackParam into the
 *  dataStack array in the VM.
 *  @param topdsParam sets top of data stack, which is the count of
 *  elements in the data stack; it is 1 above the top element;
 *  normally we start with an empty data stack, i.e., topdsParam == 0.
 *  @param staticMemoryParam may be NULL, when non-NULL then this function
 *  copies staticMemoryParamElems elements (not bytes) from staticMemoryParam
 *  into the staticMemory array of the VM.
 *  @param staticMemoryParamElems see previous comment.
 *  @param callStackParam may be NULL, when non-NULL then this function
 *  copies topcsParam elements (not bytes) from callStackParam into the
 *  callStack array in the VM.
 *  @param topcsParam sets top of call stack, which is the count of
 *  elements in the call stack; it is 1 above the top element;
 *  normally we start with an empty data stack, i.e., topcsParam == 0.
 *  @param codeMemoryParam may be NULL, when non-NULL then this function
 *  copies codeMemoryParamElems elements (not bytes) from codeMemoryParam
 *  into the codeMemory array of the VM.
 *  @param codeMemoryParamElems see previous comment.
 *  @param isSupervisorModeParam is a boolean, usually 1 for true.
 *  Other state-bearing fields in the VM should be set by running
 *  the program in codeMemory via execute.
**/
extern void stepvmInC_constructor(struct stepvmInC *addressOfVM,
    stepdata_t *dataStackParam, int32_t topdsParam,
    stepdata_t *staticMemoryParam, int32_t staticMemoryParamElems,
    stepaddr_t *callStackParam, int32_t topcsParam,
    stepcode_t *codeMemoryParam, int32_t codeMemoryParamSize,
    int8_t isSupervisorModeParam);

/**
 *  run_stepvmInC() initializes the ip to 0 and runs the virtual machine.
 *  Compile with DEBUGVM to get range checks and status dumps.
 *  run() terminates on the syscall(2) instruction or most errors.
 *  @param addressOfVM is the VM to run, after initialization or
 *  reinitialization by a call to stepvmInC_constructor.
 *  @param dumpOnTermination set to true (non-0) if the run should
 *  dump the state of the VM to stderr at termination time, else false (0).
 *  dumpOnTermination should be avoided when profiling, particularly
 *  if run_stepvmInC is called many times, since each call generates a
 *  lot of I/O when dumpOnTermination is true, messing up the profiling
 *  and blowing SYStem time through the roof.
**/
extern void run_stepvmInC(struct stepvmInC *addressOfVM, int dumpOnTermination) ;

/**
 *  Dump the state of the VM to stderr.
 *  @param addressOfVM is the VM to dump.
**/
extern void dump_stepvmInC(struct stepvmInC *addressOfVM);

#endif
