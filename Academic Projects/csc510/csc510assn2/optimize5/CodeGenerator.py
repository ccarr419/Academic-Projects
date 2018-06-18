# CodeGenerator.py, initial code by D. Parson, January 2012,
# for use in CSC 526, Compiler II, Spring 2012.
# STUDENT add support for vectors in Spring 2012 assignment 1.

from optimize5.TypeChecks import tcompat, tIsArray, tBaseType
from sys import maxint

class CodeGenerator(object):
    '''
    This class provides the code generator for the compiler of progcalc.py.
    '''
    def __init__(self):
        '''
        The constructor does not do anything right now.
        All code is generated from the generate method.
        '''
        pass
    def generate(self, parsetree, outerSymtab, outerCodeArray, vmStaticData):
        '''
        Generate all the code of this program by calling other helper
        methods to traverse the parse tree, using helper methods as
        subtree visitors. The parameters are as follows:
        0. self is this object;
        1. parsetree is the top-level parse tree, consisting of
        a sequence of target program statements;
        2. outerSymtab is the symbol table of the outermost scope;
        3. outerCodeArray is the Python list into which to compile
        code for the outermost scope, outside of any function definition.
        '''
        for statement in parsetree:
            CodeGenerator.visitor[statement[0]](
                self, statement, outerSymtab, outerCodeArray, vmStaticData)

    def printexpression(self, subtree, mysymtab, myvmCode, vmStaticData):
        '''
        postorder code generator to print the result of expression
        evaluation residing atop the data stack.
        '''
        # Evaluating an expression without assigning its result (on top of the
        # data_stack) to a variable or parameter means: Print it, followed by
        # a carriage return - line feed.
        # subtree[1][0] gives the category of expression.
        CodeGenerator.visitor[subtree[1][0]](
            self, subtree[1], mysymtab, myvmCode, vmStaticData)
        myvmCode.append("StepOpCode STEP_PRINT")
        myvmCode.append("StepOpCode STEP_CRLF")
    def varassign(self, subtree, mysymtab, myvmCode, vmStaticData):
        '''
        postorder code generator to assign the result of expression
        evaluation residing atop the data stack into a new variable at
        the current scope, with possible type conversion necessary,
        e.g. storing a float into an int variable.
        '''
        # If no preceding code leaves any spare values sitting on the
        # data stack (and preceding code should NOT leave unused results of
        # expressions sitting on the data stack), then the result of the above
        # expression is sitting at just the correct offset from FP, i.e.,
        # 'numlocals' offset. In that case no code need be generated here.
        # HOWEVER, if the ID's type is a float and the expression's is an int,
        # or vice versa, we still need to generate STEP_CAST_DOUBLE or
        # STEP_CAST_LONG.
        CodeGenerator.visitor[subtree[3][0]](
            self, subtree[3], mysymtab, myvmCode, vmStaticData)
        vartype = subtree[2][1]
        valuetype = subtree[3][1]
        # TODO: Deal with array[] type implicit casting on variable assignment.
        # In the case where array types match,
        # it is not necessary to adjust reference counts because,
        # when the expression on the data stack loses the array
        # reference, the variable gains it, for a net change of 0.
        if (vartype != valuetype):
            if tIsArray(vartype):
                # Generate code to duplicate the array whose address is
                # on top of the data stack with an array of the correct type
                # via op codes including STEP_ARRAYCPY. *After* this is done,
                # it is necessary to decrement the reference count of the
                # original array via STEP_REFCNT, because popping it off of
                # the data stack is a lost reference. In the end the 
                # address of the new array replaces the original on the
                # data stack.
                # My advice is to create a private helper method that
                # generates code for an array "type-casting copy constructor"
                # that you can use here as well as in funcassign() and
                # funCall(). My solution makes a single-line call in each
                # of these three places to my helper method.
                self.__helpTypeCastArray__(myvmCode, vartype)
            elif (vartype == 'int'):
                myvmCode.append("StepOpCode STEP_CAST_LONG")
            elif (vartype == 'float'):
                myvmCode.append("StepOpCode STEP_CAST_DOUBLE")
            elif (vartype == 'string'):
                myvmCode.append("StepOpCode STEP_CAST_STRING")
    def __helpTypeCastArray__(self, myvmCode, desttype):
        basetype = tBaseType(desttype)
        if basetype == 'float':
            castarg = 1
        elif basetype == 'int':
            castarg = -1
        else:
            castarg = 0         # should not happen
        # STACK: FROMADDR
        myvmCode.append("StepOpCode STEP_DUP")
        # FROMADDR FROMADDR
        myvmCode.append("StepOpCode STEP_CONST")
        myvmCode.append("Long " + str(castarg))
        # FROMADDR FROMADDR castarg
        myvmCode.append("StepOpCode STEP_ARRAYCPY")
        # FROMADDR TOADDR
        myvmCode.append("StepOpCode STEP_SWAP")
        # TOADDR FROMADDR
        myvmCode.append("StepOpCode STEP_CONST")
        myvmCode.append("Long " + str(-1))
        # TOADDR FROMADDR -1
        myvmCode.append("StepOpCode STEP_REFCNT")
        # TOADDR
    def funcassign(self, subtree, outersymtab, myvmCode, vmStaticData,
            isHelpingTailcall=False):
        '''
        postorder code generator to compile a function body.
        This method compiles the statement list and the RETURN
        expression code via their subtrees, and then generates code
        for the postamble. Parameter isHelpingTailcall when True
        (NOT the default) generates only cleanup of the stack frame
        for tailcall.
        '''
        # outersymtab is this function's enclosing scope.
        funcname = subtree[1]
        funcentry = outersymtab[funcname]
        functype = funcentry[2]
        paramlist = funcentry[3]
        innersymtab = funcentry[4]
        innercode = funcentry[5]
        if not isHelpingTailcall:
            for statementSubtree in subtree[4]:
                CodeGenerator.visitor[statementSubtree[0]](self,
                    statementSubtree, innersymtab, innercode, vmStaticData)
            CodeGenerator.visitor[subtree[5][1][0]](    # RETURN expression
                self, subtree[5][1], innersymtab, innercode, vmStaticData)
            if (functype != subtree[5][1][1]):  # latter is expression type
                if tIsArray(functype):
                    # Deal with array[] type implicit casting on return
                    # expression.
                    # See comments regarding a helper method for
                    # "type-casting copy constructor" arrays of mismatched types
                    # in varassign().
                    self.__helpTypeCastArray__(innercode, functype)
                else:
                    if functype == 'int':
                        innercode.append("StepOpCode STEP_CAST_LONG")
                    elif functype == 'float':
                        innercode.append("StepOpCode STEP_CAST_DOUBLE")
                    elif functype == 'string':
                        innercode.append("StepOpCode STEP_CAST_STRING")
            # BUG innercode.append("StepOpCode STEP_CONST")
            # BUG innercode.append("Long 0")  # address 0 in the data dictionary
            # BUG innercode.append("StepOpCode STEP_STORE")
        mylocals = innersymtab['#locals']
        myparams = innersymtab['#params']
        # For every local variable and parameter that is an 
        # array, decrement its reference count in the process of
        # dropping it from the data stack. Integrate your code below.
        # Make sure to use innersymtab if you need to look up the local
        # variables, and paramlist (extracted from outersymtab) for params.
        # Note that local variables and arguements are popped in the
        # opposite order from which they were pushed. If there are three
        # local variables at offsets [2], [1] and 0 on the stack, [2] pops
        # first. If there were two arguments below [-1] (which holds the
        # static link), [-2] pops before [-3]. innersymtab holds type and
        # stack offset data for locals, and paramlist holds it for parameters.
        for entry in innersymtab.values():
            if (isinstance(entry, tuple) or isinstance(entry, list))    \
                    and entry[0] == 'var' and tIsArray(entry[2]):
                # Allowing entry[3] < 0 does the job for arguments.
                innercode.append("StepOpCode STEP_FETCH_REGISTER")
                innercode.append("Long " + str(entry[3]))
                innercode.append("StepOpCode STEP_CONST")
                innercode.append("Long -1")
                innercode.append("StepOpCode STEP_REFCNT")
        # Now nuke the activation frame.
        # Multithreading -- must NOT store result in dataMemory[0]!!!
        innercode.append("StepOpCode STEP_CONST")
        innercode.append("Long " + str(- (myparams + 1)))      # lowest param
        innercode.append("StepOpCode STEP_CONST")
        innercode.append("Long " + str(mylocals - 1)) # highest local var
        innercode.append("StepOpCode STEP_DROPFRAME")
        if not isHelpingTailcall:
            # BUG innercode.append("StepOpCode STEP_CONST")
            # BUG innercode.append("Long 0")    # address 0 in the data dictionary
            # BUG innercode.append("StepOpCode STEP_FETCH")
            innercode.append("StepOpCode STEP_RETURN")
    def binaryOperation(self, subtree, mysymtab, myvmCode, vmStaticData):
        '''
        postorder code generator to generate a binary operation
        combining two subexpressions. Enhanced February 2012 to implement
        '+' for two arrays by constructing their concatenation.
        Concatenating a 0-length any[] can actually just use the
        other array without growing a new one, because these arrays
        are immuable.
        '''
        CodeGenerator.visitor[subtree[2][0]](   # left subexpression
            self, subtree[2], mysymtab, myvmCode, vmStaticData)
        CodeGenerator.visitor[subtree[3][0]](   # right subexpression
            self, subtree[3], mysymtab, myvmCode, vmStaticData)
        if tIsArray(subtree[1]):        # Type of sum is an array
            # This should be concatenation of two arrays, make sure:
            if (subtree[0] != '+'):
                raise ValueError, (                                 \
                    "INTERNAL ERROR: Bad op for an array in parse tree: " \
                        + str(subtree[0]))
            # Generate code to set up the data stack for an invocation of
            # STEP_ARRAYCAT, setting its TYPEFLAG to a per-element typecast
            # only if one of the two input arrays has a type mismatch with
            # the destination array.
            # After STEP_ARRAYCAT has completed your generated code must
            # decrement the reference counts for the two original arrays
            # via STEP_REFCNT, and discard everything on the data stack
            # except the new, concatenated array. You do not need to
            # increment its reference count.
            # STACK: LARRAY RARRAY
            castflag = "Long 0"
            if (subtree[2][1] != subtree[1] or subtree[3][1] != subtree[1]):
                basetype = tBaseType(subtree[1])
                if (basetype == 'float'):
                    castflag = "Long 1"
                elif (basetype == 'int'):
                    castflag = "Long -1"
            myvmCode.append("StepOpCode STEP_OVER")
            myvmCode.append("StepOpCode STEP_OVER")
            # LARRAY RARRAY LARRAY RARRAY
            myvmCode.append("StepOpCode STEP_CONST")
            myvmCode.append(castflag)
            # LARRAY RARRAY LARRAY RARRAY castflag
            myvmCode.append("StepOpCode STEP_ARRAYCAT")
            # LARRAY RARRAY NEWARRAY
            myvmCode.append("StepOpCode STEP_SWAP2")
            # NEWARRAY RARRAY LARRAY
            myvmCode.append("StepOpCode STEP_CONST")
            myvmCode.append("Long -1")
            myvmCode.append("StepOpCode STEP_REFCNT")
            # NEWARRAY RARRAY
            myvmCode.append("StepOpCode STEP_CONST")
            myvmCode.append("Long -1")
            myvmCode.append("StepOpCode STEP_REFCNT")
            # NEWARRAY
        else:
            # The results of both expressions are sitting at the top of the data
            # stack, so just generate the appropriate op code.
            # With StepVM.java it is necessary to type cast mismatches.
            # The type of the arguments may be compatible
            # with each other but differ from the result of the binary
            # operation, for example (9.0 < 3) requires a STEP_DLT, which
            # evaluates to a Long. So, check the arg types against each other,
            # not against the result type.
            castflag = None
            argtype = None
            needCastLeft = False
            needCastRight = False
            if (subtree[2][1] == subtree[3][1]):
                argtype = subtree[2][1]
            elif (subtree[2][1] == 'float' or subtree[3][1] == 'float'):
                argtype = 'float'
                needCastLeft = (subtree[2][1] != 'float')
                needCastRight = (subtree[3][1] != 'float')
            else:
                msg = "INTERNAL ERROR: Illegal mix of types "           \
                    + str(subtree[2][1]) + " and " +                    \
                    + str(subtree[3][1]) + " for operator "             \
                    + str(subtree[0])
                raise ValueError, msg
            if (argtype == 'float'):
                castflag = "StepOpCode STEP_CAST_DOUBLE"
            elif (argtype == 'int'):
                castflag = "StepOpCode STEP_CAST_LONG"
            elif (argtype == 'string'):
                castflag = "StepOpCode STEP_CAST_STRING"
            if needCastLeft:
                myvmCode.append("StepOpCode STEP_SWAP")
                myvmCode.append(castflag)
                myvmCode.append("StepOpCode STEP_SWAP")
            if needCastRight:
                myvmCode.append(castflag)
            myvmCode.append(CodeGenerator.binops[subtree[0]][argtype])
    def logicalOperation(self, subtree, mysymtab, myvmCode, vmStaticData):
        '''
        inorder code generator to generate short-circuited logical and OR or.
        STUDENT LOGICAL NEEDS TO DEAL WITH > 2 ARGS IN subtree[2]
        STUDENTS: Modify this function accordingly.
        '''
        # PARSON'S SOLUTION
        jmpPoints = []
        finalexpr = len(subtree[2]) - 1
        for i in range(0, len(subtree[2])):
            CodeGenerator.visitor[subtree[2][i][0]](   # next subexpression
                self, subtree[2][i], mysymtab, myvmCode, vmStaticData)
            if (i < finalexpr):
                myvmCode.append("StepOpCode STEP_DUP")
                # Leave left expression result on stack if jump is taken.
                if subtree[0] == r'||':     # logical or
                    myvmCode.append("StepOpCode STEP_LZEQ")
                    # Invert before test.
                myvmCode.append("StepOpCode STEP_GOTO0")
                jumpoffset = len(myvmCode)    # offset of in-line jump address
                jmpPoints.append(jumpoffset)
                myvmCode.append(None)   # This will get backpatched.
                myvmCode.append("StepOpCode STEP_DROP")
                # Discard the DUP'd value.
        for jumpoffset in jmpPoints:
            myvmCode[jumpoffset] = ((len(myvmCode)-jumpoffset),)
            # Backpatch later
    def tildeOperation(self, subtree, mysymtab, myvmCode, vmStaticData):
        '''
        inorder code generator to print and discard left subexpression.
        STUDENT TILDE NEEDS TO DEAL WITH > 2 ARGS IN subtree[2]
        STUDENTS: Modify this function accordingly.
        '''
        # PARSON'S SOLUTION
        finalexpr = len(subtree[2]) - 1
        for i in range(0, len(subtree[2])):
            CodeGenerator.visitor[subtree[2][i][0]](   # next subexpression
                self, subtree[2][i], mysymtab, myvmCode, vmStaticData)
            if (i < finalexpr):
                myvmCode.append("StepOpCode STEP_PRINT")
                myvmCode.append("StepOpCode STEP_CRLF")
    def uminusOperation(self, subtree, mysymtab, myvmCode, vmStaticData):
        '''
        postorder code generator to invert a numeric value
        '''
        CodeGenerator.visitor[subtree[2][0]](   # single subexpression
            self, subtree[2], mysymtab, myvmCode, vmStaticData)
        if subtree[1] == 'int':
            myvmCode.append("StepOpCode STEP_LMINUS")
        else:
            myvmCode.append("StepOpCode STEP_DMINUS")
    def unotOperation(self, subtree, mysymtab, myvmCode, vmStaticData):
        '''
        postorder code generator to negate a logical (int) value
        '''
        CodeGenerator.visitor[subtree[2][0]](   # single subexpression
            self, subtree[2], mysymtab, myvmCode, vmStaticData)
        myvmCode.append("StepOpCode STEP_LZEQ")
    def conditionalOperation(self, subtree, mysymtab, myvmCode, vmStaticData):
        '''
        inorder code generator to generate short-circuited ?: operation
        '''
        CodeGenerator.visitor[subtree[2][0]](   # boolean expression 1
            self, subtree[2], mysymtab, myvmCode, vmStaticData)
        myvmCode.append("StepOpCode STEP_GOTO0")    # jump to else part
        jumpoffset1 = len(myvmCode)
        myvmCode.append(None)
        CodeGenerator.visitor[subtree[3][0]](   # the IF expression
            self, subtree[3], mysymtab, myvmCode, vmStaticData)
        myvmCode.append("StepOpCode STEP_GOTO") # Past the ELSE code
        jumpoffset2 = len(myvmCode)
        myvmCode.append(None)
        CodeGenerator.visitor[subtree[4][0]](   # the ELSE expression
            self, subtree[4], mysymtab, myvmCode, vmStaticData)
        # Backpatch with relative jump addresses that the linker will resolve.
        myvmCode[jumpoffset1] = ((jumpoffset2 - jumpoffset1 + 1),)
        myvmCode[jumpoffset2] = ((len(myvmCode) - jumpoffset2),)
    def idLookup(self, subtree, mysymtab, myvmCode, vmStaticData):
        '''
        postorder generator to walk out N static links and fetch this
        variable from its stack frame.
        '''
        symbolEntry = mysymtab[subtree[2]]
        # The parser guarantees that this is a variable lookup.
        outlinks = None
        location = None
        if symbolEntry[0] == 'var':
            outlinks = 0
            location = symbolEntry[3]
        else:           # symbolEntry[0] == 'symref':
            outlinks = symbolEntry[2]
            defsymtab = symbolEntry[3]
            originalEntry = defsymtab[subtree[2]]
            location = originalEntry[3]
        # Subscripting for array names added CSC 526 assn 1 Feb 2012
        subscriptSubtree = None if (len(subtree) == 3) else subtree[3]
        if (outlinks == 0):
            myvmCode.append("StepOpCode STEP_FETCH_REGISTER")
            myvmCode.append("Long " + str(location))
        else:
            myvmCode.append("StepOpCode STEP_PUSH_FP") # initial static link
            for i in range(0,outlinks):
                myvmCode.append("StepOpCode STEP_CONST")
                myvmCode.append("Long -1")
                myvmCode.append("StepOpCode STEP_LADD") # add -1 to current FP
                myvmCode.append("StepOpCode STEP_FETCH_STACK") # fetch outer FP
            myvmCode.append("StepOpCode STEP_CONST")
            myvmCode.append("Long " + str(location))
            myvmCode.append("StepOpCode STEP_LADD")  # variable's address
            myvmCode.append("StepOpCode STEP_FETCH_STACK") # variable's value
        # Increase the refcount if this value is
        # an array, UNLESS (subscriptSubtree != None).
        # After this code is done, the array address must still be
        # on the stack, with nothing else on the stack added by this code.
        # HOWEVER, if (subscriptSubtree != None), then instead of incrementing
        # the refcount, generate code to get the subscript value onto the
        # stack, then code to fetch the element indexed by subscriptSubtree,
        # replacing the array address with the fetched element.
        # subscriptSubtree entails recursive code generation via visitor[].
        if subscriptSubtree != None:
            CodeGenerator.visitor[subscriptSubtree[0]](
                self, subscriptSubtree, mysymtab, myvmCode, vmStaticData)
            myvmCode.append("StepOpCode STEP_PADD")
            myvmCode.append("StepOpCode STEP_FETCH")
        elif tIsArray(subtree[1]):
            myvmCode.append("StepOpCode STEP_DUP")
            # ARRAY ARRAY
            myvmCode.append("StepOpCode STEP_CONST")
            myvmCode.append("Long 1")
            myvmCode.append("StepOpCode STEP_REFCNT")
            # ARRAY
    def tailCall(self, subtree, mysymtab, myvmCode, vmStaticData):
        '''
        Generate a tail call to the current or other function when the
        call is the last step before returning, and the called function
        returns the value that is, in turn, returned by the calling
        function. A tail call does not generate a function call, it
        generates a STEP_GOTO_SECONDARY to the start of the called function,
        using the following general steps.
        1. It computes the outgoing arguments for the pseudo-function call.
           Computing arguments must be done before step 2, because
           if an incoming array parameter is also among the outgoing
           argument dependencies, its reference count must not drop to 0
           prematurely.
        2. Conceptually, it removes local variables and parameters,
           decrementing array reference counts as for a normal function
           return's postamble.
        3. It rerranges the data stack to reflect the dropping of all local
           variables, static link and arguments to the current function,
           then it pushes the argument values and static link to the called
           function, then generates a STEP_GOTO_SECONDARY to the "called"
           function.
        Turning tail calls into loops reduces the likelihood of a stack
        overflow at run time. However, with all of the stack manipulation
        overhead for the Step VM, a tail call may run slower than a
        regular function call. Consult the new STEP_DROP"FRAME op code as
        a possible time saver for the postamble.
        '''
        # STUDENTS -- delete the next line, then write your code.
        # NOTE that subtree[4] for a 'tailcall' holds the
        # (subtree, outersymboltable) pair for the context of the funcassign
        # for the definition of the function making the tail call.
        # You need that data so you can implement the postamble for
        # the correct parameters and local variables.
        # table entry for the function that is "making the tail call."
        location, numargs = self.funCall(subtree, mysymtab, myvmCode,
            vmStaticData, isRealFunction=False)
        # Arguments are pushed, now do the postamble call.
        self.funcassign(subtree[4][0],subtree[4][1], myvmCode, vmStaticData,
            isHelpingTailcall=True)
        myvmCode.append("StepOpCode STEP_GOTO_SECONDARY")
        myvmCode.append(location)
    def preduceCollect(self, subtree, mysymtab, myvmCode, vmStaticData):
        poptype = subtree[0]      # 'preduce' OR 'pcollect'
        exprtype = subtree[1]     # int, int[] etc of each function
        reducer = subtree[2]      # reduce operator '+' '-' etc.
        reducev = subtree[3]      # Initial reduce constant or None
        funclist = subtree[4]     # List of funcall records.
        numvals = len(funclist)
        for func in funclist:
            location, numargs = self.funCall(func, mysymtab, myvmCode,
                vmStaticData, isRealFunction=False)
            myvmCode.append("StepOpCode STEP_FORK")
            myvmCode.append(location)
            myvmCode.append("Long " + str(numargs))
        myvmCode.append("StepOpCode STEP_JOIN")
        # STACK: NVALUES N
        myvmCode.append("StepOpCode STEP_DROP")
        if poptype == 'preduce':
            if reducev != None:
                CodeGenerator.visitor[reducev[0]](
                    self, reducev, mysymtab, myvmCode, vmStaticData)
                numvals += 1
            if (tIsArray(exprtype) and reducer == '+'):
                # We have to take care of garbage collection.
                # There are at least 2 arrays sitting on the stack --
                # the grammar requires at least 2 parallel functions.
                # VALUES? RARRAY LARRAY
                myvmCode.append("StepOpCode STEP_OVER")
                myvmCode.append("StepOpCode STEP_OVER")
                myvmCode.append("StepOpCode STEP_SWAP")
                myvmCode.append("StepOpCode STEP_CONST")
                myvmCode.append("Long 0")
                # VALUES? RARRAY LARRAY LARRAY RARRAY 0
                myvmCode.append("StepOpCode STEP_ARRAYCAT")
                # VALUES? RARRAY LARRAY NEWARRAY
                myvmCode.append("StepOpCode STEP_SWAP2")
                # VALUES? NEWARRAY LARRAY RARRAY
                myvmCode.append("StepOpCode STEP_CONST")
                myvmCode.append("Long -1")
                myvmCode.append("StepOpCode STEP_REFCNT")
                # VALUES? NEWARRAY LARRAY
                myvmCode.append("StepOpCode STEP_CONST")
                myvmCode.append("Long -1")
                myvmCode.append("StepOpCode STEP_REFCNT")
                # VALUES? NEWARRAY
                # The total reduction is numvals-1, and we have just done one.
                for val in range(1, numvals-1):
                    myvmCode.append("StepOpCode STEP_OVER")
                    myvmCode.append("StepOpCode STEP_OVER")
                    myvmCode.append("StepOpCode STEP_SWAP")
                    # AREF NEWARRAY NEWARRAY AREF
                    myvmCode.append("StepOpCode STEP_CONST")
                    myvmCode.append("Long 0")
                    myvmCode.append("StepOpCode STEP_ARRAYCAT")
                    # AREF NEWARRAY NEWERARRAY
                    myvmCode.append("StepOpCode STEP_SWAP2")
                    # NEWERARRAY NEWARRAY AREF
                    myvmCode.append("StepOpCode STEP_CONST")
                    myvmCode.append("Long -1")
                    myvmCode.append("StepOpCode STEP_REFCNT")
                    # NEWERARRAY NEWARRAY
                    myvmCode.append("StepOpCode STEP_CONST")
                    myvmCode.append("Long -1")
                    myvmCode.append("StepOpCode STEP_REFCNT")
                    # NEWERARRAY
            else:   # scalar operation over numvals values
                # Optimization suggested by Jason Umbenhauer:
                # Avoid the SWAP on commutative operators.
                commutative  = ['+', '*']
                mustswap = True
                if reducer in commutative                           \
                        and (reducer != '+' or exprtype != 'string'):
                    mustswap = False
                opcodetxt = CodeGenerator.binops[reducer][exprtype]
                for val in range(0, numvals-1):
                    if mustswap:
                        myvmCode.append("StepOpCode STEP_SWAP")
                    myvmCode.append(opcodetxt)
        elif poptype == 'pcollect':
            # The following is close to the code in arrayvalues, but
            # the elements are backwards on the stack, and they are already
            # evaluated. This presents no run-time overhead, since we can index
            # from the back as easily as from the front, but the code is 
            # somewhat different from arrayValues().
            myvmCode.append("StepOpCode STEP_CONST")
            myvmCode.append("Long " + str(numvals))
            myvmCode.append("StepOpCode STEP_ALLOC")
            # STACK: NEWARRAY
            for ix in range(0, numvals):
                # ... ELEVALUE NEWARRAY
                myvmCode.append("StepOpCode STEP_DUP")
                if ix != 0:
                    myvmCode.append("StepOpCode STEP_CONST")
                    myvmCode.append("Long " + str(ix))
                    myvmCode.append("StepOpCode STEP_PADD")
                # ... ELEVALUE NEWARRAY NEWARRAY+IX
                myvmCode.append("StepOpCode STEP_OVER2")
                # ... ELEVALUE NEWARRAY NEWARRAY+IX ELEVALUE
                myvmCode.append("StepOpCode STEP_SWAP")
                # ... ELEVALUE NEWARRAY ELEVALUE NEWARRAY+IX
                myvmCode.append("StepOpCode STEP_STORE")
                # ... ELEVALUE NEWARRAY
                myvmCode.append("StepOpCode STEP_SWAP")
                myvmCode.append("StepOpCode STEP_DROP")
                # ... NEWARRAY
        else:
            raise ValueError, ("INTERNAL CODE GENERATOR ERROR: "    \
                + "Invalid parallel operator: " + str(poptype) + ".")
    def funCall(self, subtree, mysymtab, myvmCode, vmStaticData,
            isRealFunction=True):
        '''
        postorder generator to walk out N static links and invoke this
        function with its correct nesting run-time static scope.
        isRealFunction if False (NOT the default) generates parameters and the
        static link, but not a function call. That is used as a helper by
        tailCall. Returns (functionAddress, numArgsPushed) as required
        by tailcall, where functionAddress is the location of the function
        to call, and numArgsPushed includes the static link.
        '''
        symbolEntry = mysymtab[subtree[2]]
        # The parser guarantees that this is a variable lookup.
        outlinks = None
        location = None
        paramlist = None
        if symbolEntry[0] == 'func':
            outlinks = 0
            location = symbolEntry          # linker backpatches this
            paramlist = symbolEntry[3]
        else:           # symbolEntry[0] == 'symref':
            outlinks = symbolEntry[2]
            defsymtab = symbolEntry[3]
            originalEntry = defsymtab[subtree[2]]
            location = originalEntry
            paramlist = originalEntry[3]
        arglist = subtree[3]
        numArgsPushed = len(arglist) + 1
        offset = len(paramlist) - 1
        for i in range(0, len(paramlist)):
            paramtype = paramlist[i][1][1]
            argument = arglist[i]
            argtype = argument[1]
            CodeGenerator.visitor[argument[0]](
                self, argument, mysymtab, myvmCode, vmStaticData)
            # Enhancement from Fall 2011 assignment 5: Do the type check
            # immediately after expression evaluation.
            if (paramtype != argtype):
                if tIsArray(paramtype):
                    # See comments regarding a helper method for
                    # "type-casting copy constructor" arrays of mismatched
                    # types in varassign().
                    self.__helpTypeCastArray__(myvmCode, paramtype)
                elif paramtype == 'int':
                    myvmCode.append("StepOpCode STEP_CAST_LONG")
                elif paramtype == 'float':
                    myvmCode.append("StepOpCode STEP_CAST_DOUBLE")
                elif paramtype == 'string':
                    myvmCode.append("StepOpCode STEP_CAST_STRING")
                else:
                    msg = "INTERNAL ERROR: Illegal implicit type cast to "  \
                        + str(paramtype) + " at call to function "          \
                        + subtree[2] + ", parameter " + paramlist[i][0]
                    raise ValueError, msg
            offset -= 1
        myvmCode.append("StepOpCode STEP_PUSH_FP") # initial static link
        for i in range(0,outlinks):
            myvmCode.append("StepOpCode STEP_CONST")
            myvmCode.append("Long -1")
            myvmCode.append("StepOpCode STEP_LADD")  # add -1 to current FP
            myvmCode.append("StepOpCode STEP_FETCH_STACK") # fetch outer FP
        if (isRealFunction):
            myvmCode.append("StepOpCode STEP_CALL_SECONDARY")
            # ID's symbol table list for later linking:
            # print "DEBUG FUNCALL OFFSET", len(myvmCode), "OPERAND", location
            myvmCode.append(location)
        return ((location, numArgsPushed))
    def constantPush(self, subtree, mysymtab, myvmCode, vmStaticData):
        '''
        postorder code generator to push a typed constant to the data stack.
        '''
        ctype = subtree[1]
        lexeme = subtree[2]
        inlineData = None
        if ctype == 'string':
            inlineData = "String " + lexeme
        elif ctype == 'int':
            inlineData = "Long " + lexeme
        else:
            inlineData = "Double " + lexeme
        myvmCode.append("StepOpCode STEP_CONST")
        myvmCode.append(inlineData)
    def typeCast(self, subtree, mysymtab, myvmCode, vmStaticData):
        '''
        postorder code generator to convert the type of the value on
        the data stack to an int, float or string.
        '''
        CodeGenerator.visitor[subtree[2][0]](       # evaluate the expression
            self, subtree[2], mysymtab, myvmCode, vmStaticData)
        if subtree[1] == 'int':
             myvmCode.append("StepOpCode STEP_CAST_LONG")
        elif subtree[1] == 'float':
             myvmCode.append("StepOpCode STEP_CAST_DOUBLE")
        elif subtree[1] == 'string':
             myvmCode.append("StepOpCode STEP_CAST_STRING")
        else:
            raise ValueError, ("INTERNAL ERROR: Bad type cast in parse tree: " \
                + str(subtree[1]))
    def arrayValues(self, subtree, mysymtab, myvmCode, vmStaticData):
        '''
        inorder code generator to allocate and store an array value
        consisting of 0 or moretype-compatible elements, where a float
        array may contain some integer elements that require type
        conversion, and the base type may be 'any' for an empty array.
        The array value is a nonnegative offset into the data dictionary
        returned by op code STEP_ALLOC.
        '''
        # The parse tree has a list of expressions. You do not need to
        # generate a loop in VM code; you need to write a loop here that
        # iterates over all the expressions in that list. Roughly:
        # 1. Allocate an array with the correct element count via STEP_ALLOC.
        # 2. For each element in the parse tree's list of expressions:
        # 2a. Visit that subtree recursively, generating code to place its
        #     value onto the data stack.
        # 2b. If the type of the generated element does not match the type of
        #     the new array, generate a typecast op code. You can get this
        #     info from the parse tree.
        # 2c. Generate code to store the evaluated element in the new array.
        # 3. Leave only the address of the new array on the data stack. Its 
        #    reference count is already correctly set to 1 by STEP_ALLOC.
        # NOTE that STEP_ALLOC for a length of 0 works correctly -- the VM
        # creates a singleton, interned memory region for all 0-element
        # arrays when it starts up. These are intrinsically of type any[].
        # STUDENT #2 REPLACE DYNAMIC ALLOCATION OF ARRAY LITERALS ON THE STACK
        # WITH STATIC ALLOCATION in vmStaticData, which is the static
        # storage class data loaded into data_dictionary at VM load time.
        myvmCode.append("StepOpCode STEP_CONST")
        myvmCode.append("Long " + str(len(subtree[2])))
        myvmCode.append("StepOpCode STEP_ALLOC")
        # STACK: NEWARRAY
        typecast = None
        basetype = tBaseType(subtree[1])
        if basetype == 'float':
            typecast = "StepOpCode STEP_CAST_DOUBLE"
        elif basetype == 'int':
            typecast = "StepOpCode STEP_CAST_LONG"
        index = 0
        for subexpr in subtree[2]:
            CodeGenerator.visitor[subexpr[0]](  # evaluate the expression
                self, subexpr, mysymtab, myvmCode, vmStaticData)
            if subexpr[1] != basetype and typecast != None:
                myvmCode.append(typecast)
            # NEWARRAY ELEVALUE
            myvmCode.append("StepOpCode STEP_OVER")
            # NEWARRAY ELEVALUE NEWARRAY
            if index != 0:
                myvmCode.append("StepOpCode STEP_CONST")
                myvmCode.append("Long " + str(index))
                myvmCode.append("StepOpCode STEP_PADD")
            # NEWARRAY ELEVALUE NEWARRAY+IX
            myvmCode.append("StepOpCode STEP_STORE")
            # NEWARRAY
            index += 1
    def arrayLiterals(self, subtree, mysymtab, myvmCode, vmStaticData):
        '''
        inorder code generator to allocate and store an array value
        consisting of 0 or more type-compatible CONSTANT elements
        into static storage, with a reference count of maxint.
        '''
        typecast = None
        basetype = tBaseType(subtree[1])
        typestring = None
        if basetype == 'float':
            typecast = float
            typestring = "Double "
        elif basetype == 'int':
            typecast = int
            typestring = "Long "
        else:
            typestring = "String "
        elemcount = len(subtree[2])
        # Store count in front of the first element.
        region = ["Long " + str(elemcount)]
        for subexpr in subtree[2]:
            if (typecast):
                region.append(typestring + str(typecast(subexpr[2])))
            else:
                region.append(typestring + str(subexpr[2]))
        location = len(vmStaticData)
        vmStaticData.extend(region)
        myvmCode.append("StepOpCode STEP_CONST")
        myvmCode.append("Long " + str(location + 1))
    def arrayLength(self, subtree, mysymtab, myvmCode, vmStaticData):
        '''
        postorder code generator leave the length an an array ID
        on top of the data stack.
        '''
        # Parson used a called to idLookup() as a helper method here.
        # What we have in subtree is for example:
        # ('arraylen', 'int', 'iarray', 'int[]')
        self.idLookup(('id', subtree[3], subtree[2]), mysymtab, myvmCode,
            vmStaticData)
        # STACK: ARRAY
        myvmCode.append("StepOpCode STEP_DUP")
        # STACK: ARRAY ARRAY
        myvmCode.append("StepOpCode STEP_ARRAYCOUNT")
        # STACK: ARRAY LEN
        myvmCode.append("StepOpCode STEP_SWAP")
        # STACK: LEN ARRAY
        myvmCode.append("StepOpCode STEP_CONST")
        myvmCode.append("Long -1")
        # LEN ARRAY -1
        myvmCode.append("StepOpCode STEP_REFCNT")
        # LEN
    # mapping from parsetree symbols at all possible roots of a sub-parsetree
    # to the tree-visting method that generates its code.
    visitor = {
        r'printexpression'      :   printexpression,
        r'varassign'            :   varassign,
        r'funcassign'           :   funcassign,
        r'+'                    :   binaryOperation,
        r'-'                    :   binaryOperation,
        r'*'                    :   binaryOperation,
        r'/'                    :   binaryOperation,
        r'%'                    :   binaryOperation,
        r'=='                   :   binaryOperation,
        r'!='                   :   binaryOperation,
        r'>'                    :   binaryOperation,
        r'>='                   :   binaryOperation,
        r'<'                    :   binaryOperation,
        r'<='                   :   binaryOperation,
        r'&&'                   :   logicalOperation,
        r'||'                   :   logicalOperation,
        r'~'                    :   tildeOperation,
        r'uminus'               :   uminusOperation,
        r'unot'                 :   unotOperation,
        r'?:'                   :   conditionalOperation,
        r'id'                   :   idLookup,
        r'funcall'              :   funCall,
        r'tailcall'             :   tailCall,
        r'preduce'              :   preduceCollect,
        r'pcollect'             :   preduceCollect,
        r'constant'             :   constantPush,
        r'typecast'             :   typeCast,
        r'arrayvalues'          :   arrayValues,
        r'arrayliterals'        :   arrayLiterals,
        r'arraylen'             :   arrayLength
    }
    # VM op codes for the main binary operator tokens
    binops = {
        '+'  : {"int" : "StepOpCode STEP_LADD",
                "float" : "StepOpCode STEP_DADD",
                "string" : "StepOpCode STEP_SADD"},
        '-'  : {"int" : "StepOpCode STEP_LSUB",
                "float" : "StepOpCode STEP_DSUB"},
        '*'  : {"int" : "StepOpCode STEP_LMULT",
                "float" : "StepOpCode STEP_DMULT"},
        '/'  : {"int" : "StepOpCode STEP_LDIV",
                "float" : "StepOpCode STEP_DDIV"},
        '%'  : {"int" : "StepOpCode STEP_LMOD"},
        '==' : {"int" : "StepOpCode STEP_LEQ",
                "float" : "StepOpCode STEP_DEQ",
                "string" : "StepOpCode STEP_SEQ"},
        '!=' : {"int" : "StepOpCode STEP_LNEQ",
                "float" : "StepOpCode STEP_DNEQ",
                "string" : "StepOpCode STEP_SNEQ"},
        '>=' : {"int" : "StepOpCode STEP_LGE",
                "float" : "StepOpCode STEP_DGE",
                "string" : "StepOpCode STEP_SGE"},
        '<=' : {"int" : "StepOpCode STEP_LLE",
                "float" : "StepOpCode STEP_DLE",
                "string" : "StepOpCode STEP_SLE"},
        '>'  : {"int" : "StepOpCode STEP_LGT",
                "float" : "StepOpCode STEP_DGT",
                "string" : "StepOpCode STEP_SGT"},
        '<'  : {"int" : "StepOpCode STEP_LLT",
                "float" : "StepOpCode STEP_DLT",
                "string" : "StepOpCode STEP_SLT"}
    }
