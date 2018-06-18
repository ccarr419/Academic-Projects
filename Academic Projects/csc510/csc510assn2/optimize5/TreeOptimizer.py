# TreeOptimizer.py, initial code by D. Parson, February 2012,
# for use in CSC 526, Compiler II, Spring 2012.
# Add support for O1 in Spring 2012 assignment 2.
# Add support for constant expression folding, constant subexpression
# elimination assignment 5.

import copy
from optimize5.TypeChecks import tcompat, tIsArray, tBaseType

class TreeOptimizer(object):
    '''
    This class rewrites parse trees and abstract syntax trees according
    to optimization levels.
    '''
    def __init__(self, optimizationLevel):
        '''
        Set the optimization level. Valid values are 0 through 2.
        Level 0 just returns the parse tree with no changes.
        Level 1 flattens the argument lists for &&, ||, ~  operators,
        and it minimizes array copy-casting by propagating the assigned
        array type downward as an inherited attribute. Level 1 also moves
        array values consisting solely of constants into static storage.
        Level 2 adds detection of tail calls, denoted in the output tree
        as a tailcall instead of a funcall.
        '''
        self.level = optimizationLevel
    def optimize(self, parsetree, outerSymtab):
        '''
        Write a new abstract syntax tree based on the parsetree parameter
        (which is not mutated) according to the optimizationLevel passed
        to the constructor. An optimizationLevel of 0 returns the input
        parsetree.
        Added assignment 5 spring 2012: Constant folding.
        '''
        # LEVEL O1:
        # STUDENT:  The visitor in the statement list may return None from
        # a varassign that converts its variable to an in-line constant,
        # so detect None as a return value from each visitor call, and just
        # drop that result. You don't need that statement. funcassign()
        # has a similar requirement for returns of None.
        if (self.level == 0):
            return parsetree
        result = ()
        for statement in parsetree:
            stmttree = TreeOptimizer.visitor[statement[0]](
                self, statement, outerSymtab, {})
            if (stmttree != None):
                result = result + (stmttree,)
        return result
    def printexpression(self, subtree, mysymtab, inherited):
        '''
        printexpression copies its subtree. It passes no inherited attributes.
        '''
        return (subtree[0], TreeOptimizer.visitor[subtree[1][0]](
            self, subtree[1], mysymtab, {}))
    def varassign(self, subtree, mysymtab, inherited):
        '''
        varassign copies its subtree. If it is assigning to an array
        variable, it propagates the receiving array type as an inherited
        attribute.
        Added assignment 5 spring 2012: Constant folding.
        '''
        # LEVEL O1:
        # STUDENT The symbol table for a variable from progcalc.py is:
        #   ID : ('var', ID, type, frameoffset)
        # If the right-hand-side expression is a constant, change above to:
        #   ID : ('var', ID, type, None, ('constant', TYPE, VALUE))
        #       when the 'var' is a compile-time constant.
        # Make sure the type of the constant in the above entry matches the
        # type of the ID, casting the value within this function if necessary.
        # You will use this added field in idLookup to replace a reference
        # to a constant 'var' ID with its ('constant', TYPE, VALUE).
        # In the case of a constant identifier, varassign() must return None,
        # and any calling method in TreeOptimizer must discard this subtree
        # when returned as None. The parser constrains such callers to 
        # TreeOptimizer.optimize() and TreeOptimizer.funcassign(), at the
        # loops over statements. Finally, before returning, this varassign
        # method must decrement the frameoffset of every local variable whose
        # frameoffset is greater than this variable's former frameoffset,
        # because after this LEVEL O1 change, this variable no longer lives
        # on the data stack. It has become a constant embedded in code.
        # Also decrement the '#locals' entry for this scope -- the activation
        # frame has one fewer entry.
        # See the postable generator code in CodeGenerator.funcassign around
        # "if (isinstance(entry, tuple) or isinstance(entry, list))" to see
        # how to find the 'var' symbol table entries in this scope's
        # mysymtab symbol table.
        attrs = {}
        if tIsArray(subtree[2][1]):
            attrs['arraytype'] = subtree[2][1]
        rhs = TreeOptimizer.visitor[subtree[3][0]](
            self, subtree[3], mysymtab, attrs)
        if (rhs[0] != 'constant'):
            return (subtree[0], subtree[1], subtree[2], rhs)
        if subtree[2][1] == rhs[1]:     # Types are the same.
            conval = rhs
        elif subtree[2][1] == 'float':
            conval = ('constant', 'float',
                str(float(int(rhs[2]))))
        elif subtree[2][1] == 'int':
            conval = ('constant', 'int',
                str(int(float(rhs[2]))))
        elif subtree[2][1] == 'string':
            conval = ('constant', 'string',
                str(rhs[2]))
        else:
            conval = rhs
        entry = mysymtab[subtree[1]]
        frmoffset = entry[3]
        mysymtab[subtree[1]] = (entry[0], entry[1], entry[2], None, conval)
        for entry in mysymtab.values():
            if (isinstance(entry, (tuple, list))                        \
                    and entry[0] == 'var' and entry[3] != None          \
                    and entry[3] > frmoffset):
                mysymtab[entry[1]] = (entry[0], entry[1], entry[2],
                    entry[3]-1) + entry[4:]
        mysymtab['#locals'] = mysymtab['#locals'] - 1
        return None
    def funcassign(self, subtree, outersymtab, inherited):
        '''
        funcassign copies its subtree. If it is returning an array value,
        it propagates the return array type as an inherited attribute.
        It also propagates a tailcall attribute for the return expression
        for optimization levels >= 2.
        Added assignment 5 spring 2012: Constant folding.
        '''
        # LEVEL O1:
        # STUDENT:  The visitor in the statement list may return None from
        # a varassign that converts its variable to an in-line constant,
        # so detect None as a return value from each visitor call, and just
        # drop that result. You don't need that statement. optimize()
        # has a similar requirement for returns of None.
        # outersymtab is this function's enclosing scope.
        funcname = subtree[1]
        funcentry = outersymtab[funcname]
        innersymtab = funcentry[4]
        statements = ()
        for statementSubtree in subtree[4]:
            stmttree = TreeOptimizer.visitor[statementSubtree[0]](
                self, statementSubtree, innersymtab, {})
            if stmttree != None:
                statements = statements + (stmttree,)
        attrs = {}
        if (self.level > 1):
            # Pass symbol table entry needed later for tail-call-postamble.
            attrs['tailcall'] = (subtree, outersymtab)
        if tIsArray(subtree[2][1]):
            attrs['arraytype'] = subtree[2][1]
        retexpr = ('return',
            TreeOptimizer.visitor[subtree[5][1][0]](
                self, subtree[5][1], innersymtab, attrs))
        return (subtree[0], subtree[1], subtree[2], subtree[3],
            statements, retexpr)
    def binaryOperation(self, subtree, mysymtab, inherited):
        '''
        binaryOperation copies its subtree. Array concatenation passes
        destination array type as an inherited attribute.
        Added assignment 5 spring 2012: Constant folding.
        '''
        # LEVEL O1
        # STUDENT COLLAPSE binaryOperations over constants into constants.
        # This means you must compute the constants in the compiler and
        # return a constant subtree in place of a binary operator if
        # possible. Watch out for divide by 0 and type-cast requirements.
        attrs = self.__purgeAttrs__(['tailcall'], inherited)
        lefttree = TreeOptimizer.visitor[subtree[2][0]]( # left subexpression
                self, subtree[2], mysymtab, attrs)
        righttree = TreeOptimizer.visitor[subtree[3][0]]( # right subexpression
                self, subtree[3], mysymtab, attrs)
        if not (lefttree[0] == 'constant' and righttree[0] == 'constant'):
            return (subtree[0], subtree[1], lefttree, righttree)
        try:
            ltypestr = lefttree[1] if (lefttree[1] != 'string') else 'str'
            rtypestr = righttree[1] if (righttree[1] != 'string') else 'str'
            mtypestr = subtree[1] if (subtree[1] != 'string') else 'str'
            levalstr = ltypestr + '(' + repr(lefttree[2]) + ')'
            # print "DEBUG BEFORE EVAL 1", levalstr
            lvalue = eval(levalstr, {}, {})
            revalstr = rtypestr + '(' + repr(righttree[2]) + ')'
            # print "DEBUG BEFORE EVAL 2", revalstr
            rvalue = eval(revalstr, {}, {})
            resevalstr = mtypestr + '(' + repr(lvalue) + ' '       \
                + subtree[0] + ' ' +  repr(rvalue) + ')'
            # print "DEBUG BEFORE EVAL 3", resevalstr
            resultval = eval(resevalstr, {}, {})
            # print "DEBUG BEFORE EVAL 4", resultval
            return ('constant', subtree[1], str(resultval))
        except Exception, msg:
            msg = 'ERROR during constant folding in binaryOperation: '  \
                + str(msg)
            raise ValueError, msg
    def logicalOperation1(self, subtree, mysymtab, inherited,
            isRootLogical=True):
        '''
        logicalOperation1 is an O1 tree flattener for && and || and ~.
        It collapses adjacent groups of && operations, or of || operations,
        or ~ (not differents ones at the same time), working left-to-right.
        Implicit left and explicit right association are discarded.
        The resulting flattened subtree evaluates left-to-right.
        It collects adjacent logicals with an inorder walk of the tree.
        It also propagates a tail call to its final boolean when the latter
        is a funcall.
        '''
        flatargs = []
        if subtree[2][0][0] == subtree[0]:
            flatargs += self.logicalOperation1(subtree[2][0], mysymtab, {},
                isRootLogical=False)
        else:
            flatargs.append(TreeOptimizer.visitor[subtree[2][0][0]](
                self, subtree[2][0], mysymtab, {}))
        if subtree[2][1][0] == subtree[0]:
            flatargs += self.logicalOperation1(subtree[2][1], mysymtab, {},
                isRootLogical=False)
        else:
            flatargs.append(TreeOptimizer.visitor[subtree[2][1][0]](
                self, subtree[2][1], mysymtab, {}))
        if isRootLogical:
            if inherited.has_key('tailcall') and flatargs[-1][0] == 'funcall':
                # Redo the tree rewrite now that we know that the rightmost
                # entry is a funcall. It still won't change to a tailcall
                # if the call is to an inner function.
                flatargs[-1] = self.funCall(flatargs[-1], mysymtab, inherited)
            return (subtree[0], subtree[1], tuple(flatargs))
        else:
            return flatargs

    def unaryOperation(self, subtree, mysymtab, inherited):
        '''
        unaryOperation copies its subtree. It passes no inherited attributes.
        Added assignment 5 spring 2012: Constant folding.
        '''
        # LEVEL O1
        # STUDENT COLLAPSE unaryOperation over constants into constants.
        # This means you must compute the constants in the compiler and
        # return a constant subtree in place of a binary operator if
        # possible. Watch out for type-cast requirements.
        righttree = TreeOptimizer.visitor[subtree[2][0]](
                self, subtree[2], mysymtab, {})
        if not (righttree[0] == 'constant'):
            return (subtree[0], subtree[1], righttree)
        xlate = {'unot' : 'not', 'uminus' : '-'}
        uop = xlate[subtree[0]]
        try:
            rtypestr = righttree[1] if (righttree[1] != 'string') else 'str'
            mtypestr = subtree[1] if (subtree[1] != 'string') else 'str'
            revalstr = rtypestr + '(' + repr(righttree[2]) + ')'
            # print "DEBUG BEFORE EVAL B", revalstr
            rvalue = eval(revalstr, {}, {})
            resevalstr = mtypestr + '(' + uop + ' ' +  repr(rvalue) + ')'
            # print "DEBUG BEFORE EVAL C", resevalstr
            resultval = eval(resevalstr, {}, {})
            # print "DEBUG BEFORE EVAL D", resultval
            return ('constant', subtree[1], str(resultval))
        except Exception, msg:
            msg = 'ERROR during constant folding in unaryOperation: '  \
                + str(msg)
            raise ValueError, msg
    def conditionalOperation(self, subtree, mysymtab, inherited):
        '''
        conditionalOperation copies its subtree.
        It passes tailcall inherited to its result expressions
        '''
        return (subtree[0], subtree[1],
            TreeOptimizer.visitor[subtree[2][0]](   # boolean expression 1
                self, subtree[2], mysymtab, {}),
            TreeOptimizer.visitor[subtree[3][0]](   # the IF expression
                self, subtree[3], mysymtab, inherited),
            TreeOptimizer.visitor[subtree[4][0]](   # the ELSE expression
                self, subtree[4], mysymtab, inherited))
    def idLookup(self, subtree, mysymtab, inherited):
        '''
        idLookup returns its subtree. It passes no inherited attributes.
        Added assignment 5 spring 2012: Constant folding.
        '''
        # LEVEL O1
        # STUDENT : Replace a reference to a constant 'var' ID with its
        # ('constant', TYPE, VALUE) using the extra field that your
        # TreeOptimizer.varassign method added to the 'var' symbol table
        # entry. Consult CodeGenerator.idLookup to see how to find the
        # symbol in the current or nested scope.
        symbolEntry = mysymtab[subtree[2]]
        # The parser guarantees that this is a variable lookup.
        outlinks = None
        location = None
        if symbolEntry[0] == 'var':
            originalEntry = symbolEntry
        else:           # symbolEntry[0] == 'symref':
            defsymtab = symbolEntry[3]
            originalEntry = defsymtab[subtree[2]]
        if len(originalEntry) > 4:
            return originalEntry[4]
        return subtree
    def funCall(self, subtree, mysymtab, inherited):
        '''
        funCall copies its subtree. It propogates an array parameter's
        type to its value expression via an inherited attribute.
        '''
        symbolEntry = mysymtab[subtree[2]]
        outlinks = None
        location = None
        paramlist = None
        if symbolEntry[0] == 'func':
            paramlist = symbolEntry[3]
            isInnerFunction = True
        else:           # symbolEntry[0] == 'symref':
            isInnerFunction = False
            defsymtab = symbolEntry[3]
            originalEntry = defsymtab[subtree[2]]
            paramlist = originalEntry[3]
        argtree = ()
        paramix = 0
        for arg in subtree[3]:
            attrs = {}
            if tIsArray(paramlist[paramix][1]):
                attrs['arraytype'] = paramlist[paramix][1]
            argtree = argtree + (TreeOptimizer.visitor[arg[0]](
                self, arg, mysymtab, attrs),)
            paramix += 1
        # We cannot do a tail call on an inner function because we need to
        # keep the static activation context intact.
        if inherited.has_key('tailcall') and not isInnerFunction:
            return ('tailcall', subtree[1], subtree[2], argtree,
                inherited['tailcall'])
        else:
            return (subtree[0], subtree[1], subtree[2], argtree)
    def preduce(self, subtree, mysymtab, inherited):
        '''
        preduce calls a series of parallel functions, then reduces their
        results using a mandatory operatorm and an optional,
        type-compatible initial value.
        '''
        return subtree
    def pcollect(self, subtree, mysymtab, inherited):
        '''
        pcollect calls a series of parallel functions, then collects their
        results into a new array.
        '''
        return subtree
    def constantCopy(self, subtree, mysymtab, inherited):
        '''
        constantCopy copies its subtree. It passes no inherited attributes.
        '''
        return subtree
    def typeCast(self, subtree, mysymtab, inherited):
        '''
        typeCast copies its subtree. It passes no inherited attributes.
        Added assignment 5 spring 2012: Constant folding.
        '''
        # LEVEL O1
        # STUDENT COLLAPSE typeCast over constants into constants.
        # This means you must compute the constants in the compiler and
        # return a constant subtree in place of a binary operator if
        # possible.
        righttree = TreeOptimizer.visitor[subtree[2][0]](
                self, subtree[2], mysymtab, {})
        if not (righttree[0] == 'constant'):
            return (subtree[0], subtree[1], righttree)
        try:
            rtypestr = righttree[1] if (righttree[1] != 'string') else 'str'
            mtypestr = subtree[1] if (subtree[1] != 'string') else 'str'
            revalstr = rtypestr + '(' + repr(righttree[2]) + ')'
            # print "DEBUG BEFORE EVAL X", revalstr
            rvalue = eval(revalstr, {}, {})
            resevalstr = mtypestr + '(' +  repr(rvalue) + ')'
            # print "DEBUG BEFORE EVAL Y", resevalstr
            resultval = eval(resevalstr, {}, {})
            # print "DEBUG BEFORE EVAL Z", resultval
            return ('constant', subtree[1], str(resultval))
        except Exception, msg:
            msg = 'ERROR during constant folding in typeCast: '  \
                + str(msg)
            raise ValueError, msg
    def arrayValues(self, subtree, mysymtab, inherited):
        '''
        arrayValues copies its subtree. If all initialization values are
        constants (a synthesized attribute), then it changes root tag
        'arrayvalues' to 'arrayliterals' to support allocation in static
        storage. Also it propagates inherited result type downward
        when assigning into variables, parameters and return values.
        '''
        scalars = ()
        if (inherited.has_key('arraytype')):
            arraytype = inherited['arraytype']
        else:
            arraytype = subtree[1]
        if len(subtree[2]) == 0:
            rootname = 'arrayvalues'
        elif self.level >= 1:
            rootname = 'arrayliterals'
        else:
            rootname = 'arrayvalues'
        basetype = tBaseType(arraytype)
        for subexpr in subtree[2]:
            # STUDENT: I made this change for assignment 5. You do not need
            # to do anything here.
            # PARSON CHANGE Look at result of visitor call, not subexpr[0],
            # to determine whether constants were folded.
            valtree = TreeOptimizer.visitor[subexpr[0]](
                self, subexpr, mysymtab, {})
            if valtree[0] == 'constant':
                if valtree[1] == 'int' and basetype == 'float':
                    # Propagate inherited array type down to the constant.
                    valtree = ('constant', basetype,
                        str(float(int(valtree[2]))))
                elif valtree[1] == 'float' and basetype == 'int':
                    valtree = ('constant', basetype,
                        str(int(float(valtree[2]))))
            else:
                rootname = 'arrayvalues'
            scalars = scalars + (valtree,)
        return (rootname, arraytype, scalars)
    def arrayLength(self, subtree, mysymtab, inherited):
        '''
        arrayLength copies its subtree. It passes no inherited attributes.
        '''
        return subtree
    # mapping from parse tree and abstract syntax tree symbols at all possible
    # roots of a sub-tree to the tree-visiting method that rewrites it.
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
            r'&&'                   :   logicalOperation1,
            r'||'                   :   logicalOperation1,
            r'~'                    :   logicalOperation1,
            r'uminus'               :   unaryOperation,
            r'unot'                 :   unaryOperation,
            r'?:'                   :   conditionalOperation,
            r'id'                   :   idLookup,
            r'funcall'              :   funCall,
            r'constant'             :   constantCopy,
            r'typecast'             :   typeCast,
            r'arrayvalues'          :   arrayValues,
            r'arraylen'             :   arrayLength,
            r'preduce'              :   preduce,
            r'pcollect'             :   pcollect
        }

    def __purgeAttrs__(self, attrNames, attrDict):
        newDict = copy.copy(attrDict);
        for aname in attrNames:
            if newDict.has_key(aname):
                del(newDict[aname])
        return newDict
