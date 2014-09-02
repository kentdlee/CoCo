/* 
 * File:   PyFrame.cpp
 * Author: Kent D. Lee
 * (c) 2013
 * Created on February 15, 2013, 5:35 PM
 * 
 * License:
 * Please read the LICENSE file in this distribution for details regarding
 * the licensing of this code. This code is freely available for educational
 * use. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * 
 * Description:
 * See the associated header file for a description of the purpose of this 
 * class. Implementation details are provided here. Read below for 
 * any specific details. 
 * 
 */

#include "PyFrame.h"
#include "PyCode.h"
#include "PyType.h"
#include "PyBool.h"
#include "PyFunction.h"
#include "PyCallable.h"
#include "PyAttr.h"
#include "PyTuple.h"
#include "PyList.h"
#include "PyFunList.h"
#include "PyInt.h"
#include "PyNone.h"
#include <iostream>
using namespace std;

const char* cmp_op[12] = {
    "__lt__",
    "__le__",
    "__eq__",
    "__ne__",
    "__gt__",
    "__ge__",
    "__contains__",
    "__notin__", // This is not an actual operator
    "is_",
    "is_not",
    "__excmatch__",
    "BAD"
};

PyFrame::PyFrame(const PyCode& theCode, vector<PyObject*>* args,
        unordered_map<string, PyObject*>& theGlobals, const vector<PyObject*>& theConstants,
        unordered_map<string, PyCell*>& theCellVars) :
        code(theCode), globals(theGlobals), 
        consts(theConstants), cellvars(theCellVars) {

    vector<string>& varnames = code.getLocals();

    this->opStack = new PyStack<PyObject*>();

    this->blockStack = new PyStack<int>();

    // bind the parameter names to the arguments. Invert
    // the order because the arguments come into the function
    // in reverse order. 
    int j = args->size()-1;

    for (int i = 0; i < args->size(); i++) {
        locals[varnames[i]] = (*args)[j--];
    }

    // bind the cellvars to their names
    for (int i = 0; i < code.getCellVars().size(); i++) {
        string name = code.getCellVars()[i];
        cellvars[name] = new PyCell(NULL);

        //Here we have a special case where the parameter 
        //is used in a nested function and so must be a cell
        //instead of the normal local value. 
        if (locals.find(name) != locals.end()) {
            cellvars[name]->set(locals[name]);
        }
    }
}

PyFrame::~PyFrame() {
    try {
        delete opStack;        
    } catch (...) {}
    try {
        delete blockStack;        
    } catch (...) {}
}

void terminate(int exceptionVal, int PC, string name) {
    throw new PyException(exceptionVal, "Terminating with exception in function " + name);
}

PyObject* PyFrame::safetyPop() {
    if (opStack->isEmpty()) {
        throw new PyException(PYILLEGALOPERATIONEXCEPTION, "Attempt to pop empty operand stack in " + code.getInstructions()[PC - 1]->getOpCodeName());
    }

    return opStack->pop();
}

string PyFrame::getCellName(int index) {
    string name;

    if (index < code.getCellVars().size()) {
        name = code.getCellVars()[index];
    } else {
        if (index - code.getCellVars().size() >= code.getFreeVars().size()) {
            throw new PyException(PYILLEGALOPERATIONEXCEPTION, "Index value out of range on instruction.");
        }
        name = code.getFreeVars()[index - code.getCellVars().size()];
    }


    return name;
}

PyObject* PyFrame::execute() {

    PC = 0;
    PyByteCode* inst;
    PyOpCode opcode;
    int operand;
    int i;
    PyType* selfType;
    PyCell* cell;
    PyObject* u;
    PyObject* v;
    PyObject* w;
    PyFunList* funlist;
    PyTuple* tuple;
    PyObject* x;
    PyObject* y;
    PyObject* z;
    PyBool* bu;
    bool handled = false;
    PyCallable* fun;
    vector<PyObject*>* args;
    vector<PyObject*>::iterator it;
    string name;

    //This registers the frame for the signal handler in case a signal occurs.
    pushFrame(this);

    while (true) {
        inst = code.getInstructions()[PC];
        //cerr << "Executing " << inst->getOpCodeName() << " at location " << PC << " in function " << code.getName() << endl;
        //cerr << "Stack is here" << endl;
        //cerr << opStack->toString() << endl;
        PC++;
        opcode = inst->getOpCode();
        operand = inst->getOperand();
        try {
            switch (opcode) {
                case LOAD_FAST:
                    u = locals[code.getLocals()[operand]];
                    if (u == 0) {
                        throw new PyException(PYILLEGALOPERATIONEXCEPTION, "LOAD_FAST failed to find value " + code.getLocals()[operand]);
                    }
                    opStack->push(u);
                    break;

                case LOAD_CONST:
                    u = consts[operand];
                    opStack->push(u);
                    break;

                case LOAD_GLOBAL:
                    u = globals[code.getGlobals()[operand]];
                    if (u == 0) {
                        throw new PyException(PYILLEGALOPERATIONEXCEPTION, "LOAD_GLOBAL failed to find value " + code.getGlobals()[operand]);
                    }
                    opStack->push(u);
                    break;

                case STORE_FAST:
                    u = safetyPop();
                    locals[code.getLocals()[operand]] = u;
                    break;

                case POP_TOP:
                    u = safetyPop();
                    break;

                case COMPARE_OP:
                    v = safetyPop();
                    u = safetyPop();
                    args = new vector<PyObject*>();
                    args->push_back(v);
                    //Please note that the line below depends on the cmp_op 
                    //array and it should be initialized to all comparison operators. This list will 
                    //need to expand at some point. The cmp_op array is at the top of this module.
                    w = u->callMethod(cmp_op[operand], args);
                    try {
                        delete args;
                    } catch (...) {
                        cerr << "Delete of COMPARE_OP args caused an exception for some reason." << endl;
                    }
                    opStack->push(w);

                    //The following must be done for exceptions because the END_FINALLY
                    //needs to know whether the exception was handled or not.
                    if (operand == 10) {
                        handled = ((PyBool*) w)->getVal();
                    }
                    break;

                case SETUP_LOOP:
                    blockStack->push(operand);
                    break;

                case BREAK_LOOP:
                    PC = blockStack->pop();
                    break;

                case POP_BLOCK:
                    if (blockStack->isEmpty()) {
                        throw new PyException(PYILLEGALOPERATIONEXCEPTION, "Attempt to pop empty block stack.");
                    }

                    blockStack->pop();
                    break;

                case JUMP_FORWARD:
                    // This instruction is not relative in this virtual machine
                    // because the assembler calculates the target address.
                    PC = operand;
                    break;

                case JUMP_ABSOLUTE:
                    PC = operand;
                    break;

                case POP_JUMP_IF_TRUE:
                    if (opStack->isEmpty()) {
                        throw new PyException(PYILLEGALOPERATIONEXCEPTION, "Attempt to pop empty operand stack in POP_JUMP_IF_TRUE.");
                    }

                    u = safetyPop();
                    if (u->getType()->toString() != "bool") {
                        throw new PyException(PYILLEGALOPERATIONEXCEPTION, "Illegal TOS value for POP_JUMP_IF_TRUE. Boolean value required.");
                    }

                    bu = (PyBool*) u;

                    if (bu->getVal() == true) {
                        PC = operand;
                    }
                    break;

                case POP_JUMP_IF_FALSE:
                    if (opStack->isEmpty()) {
                        throw new PyException(PYILLEGALOPERATIONEXCEPTION, "Attempt to pop empty operand stack in POP_JUMP_IF_FALSE.");
                    }

                    u = safetyPop();
                    if (u->getType()->toString() != "bool") {
                        throw new PyException(PYILLEGALOPERATIONEXCEPTION, "Illegal TOS value for POP_JUMP_IF_FALSE. Boolean value required.");
                    }

                    bu = (PyBool*) u;

                    if (bu->getVal() == false) {
                        PC = operand;
                    }
                    break;

                case RETURN_VALUE:
                    // At one point I had a check here that after popping the stack was empty. This 
                    // turns out to be too restrictive since an exception may leave values on the 
                    // stack when returning. 
                    if (opStack->isEmpty()) {
                        throw new PyException(PYILLEGALOPERATIONEXCEPTION, "Attempt to pop empty operand stack in RETURN_VALUE.");
                    }

                    u = safetyPop();

                    //Now deregister the frame with the signal handler.
                    popFrame();

                    return u;
                    break;

                case BINARY_ADD:
                case INPLACE_ADD:
                    v = safetyPop();
                    u = safetyPop();
                    args = new vector<PyObject*>();
                    args->push_back(v);
                    w = u->callMethod("__add__", args);
                    opStack->push(w);
                    try {
                        delete args;
                    } catch (...) {
                        cerr << "Delete of BINARY_ADD args caused an exception for some reason." << endl;
                    }
                    break;

                case BINARY_SUBTRACT:
                    v = safetyPop();
                    u = safetyPop();
                    args = new vector<PyObject*>();
                    args->push_back(v);
                    w = u->callMethod("__sub__", args);
                    opStack->push(w);
                    try {
                        delete args;
                    } catch (...) {
                        cerr << "Delete of BINARY_SUBTRACT args caused an exception for some reason." << endl;
                    }
                    break;

                case BINARY_MULTIPLY:
                    v = safetyPop();
                    u = safetyPop();
                    args = new vector<PyObject*>();
                    args->push_back(v);
                    w = u->callMethod("__mul__", args);
                    opStack->push(w);
                    try {
                        delete args;
                    } catch (...) {
                        cerr << "Delete of BINARY_MULTIPLY args caused an exception for some reason." << endl;
                    }
                    break;

                case BINARY_TRUE_DIVIDE:
                    v = safetyPop();
                    u = safetyPop();
                    args = new vector<PyObject*>();
                    args->push_back(v);
                    w = u->callMethod("__truediv__", args);
                    opStack->push(w);
                    try {
                        delete args;
                    } catch (...) {
                        cerr << "Delete of BINARY_TRUE_DIVIDE args caused an exception for some reason." << endl;
                    }
                    break;

                case BINARY_FLOOR_DIVIDE:
                    v = safetyPop();
                    u = safetyPop();
                    args = new vector<PyObject*>();
                    args->push_back(v);
                    w = u->callMethod("__floordiv__", args);
                    opStack->push(w);
                    try {
                        delete args;
                    } catch (...) {
                        cerr << "Delete of BINARY_FLOOR_DIVIDE args caused an exception for some reason." << endl;
                    }

                    break;

                case GET_ITER:
                    u = safetyPop();
                    args = new vector<PyObject*>();
                    v = u->callMethod("__iter__", args);
                    opStack->push(v);
                    try {
                        delete args;
                    } catch (...) {
                        cerr << "Delete of GET_ITER args caused an exception for some reason." << endl;
                    }

                    break;

                case ROT_TWO:
                    u = safetyPop();
                    v = safetyPop();
                    opStack->push(u);
                    opStack->push(v);
                    break;

                case FOR_ITER:
                    u = safetyPop();
                    args = new vector<PyObject*>();
                    try {
                        v = u->callMethod("__next__", args);
                        opStack->push(u);
                        opStack->push(v);
                    } catch (PyException* ex) {
                        if (ex->getExceptionType() == PYSTOPITERATIONEXCEPTION) {
                            PC = operand;
                        } else
                            throw ex;
                    }
                    try {
                        delete args;
                    } catch (...) {
                        cerr << "Delete of FOR_ITER args caused an exception for some reason." << endl;
                    }

                    break;


                case CALL_FUNCTION:
                    args = new vector<PyObject*>();
                    //NOTE: Arguments are added backwards because they are popped
                    //off the stack in reverse order. So the called function gets
                    //the arguments backwards. 
                    for (i = 0; i < operand; i++) {
                        u = safetyPop();
                        args->push_back(u);
                    }
                    u = safetyPop();
                    v = u->callMethod("__call__", args);
                    opStack->push(v);
                    try {
                        delete args;
                    } catch (...) {
                        cerr << "Delete of CALL_FUNCTION args caused an exception for some reason." << endl;
                    }

                    break;

                case LOAD_ATTR:
                    u = safetyPop();
                    v = new PyAttr(u, code.getGlobals()[operand]);
                    opStack->push(v);
                    break;

                case BINARY_SUBSCR:
                    u = safetyPop();
                    v = safetyPop();
                    args = new vector<PyObject*>();
                    args->push_back(u);

                    w = v->callMethod("__getitem__", args);
                    opStack->push(w);
                    delete args;
                    break;
                    
                case STORE_SUBSCR:
                    u = safetyPop();
                    v = safetyPop();
                    w = safetyPop();
                    args = new vector<PyObject*>();
                    args->push_back(u); // the index
                    args->push_back(w); // the item
                    
                    w = v->callMethod("__setitem__", args); // None is returned
                    delete w;
                    delete args;
                    break;

                case LOAD_CLOSURE:
                    // The free or cell vars in the code object give us the name of the 
                    // value. 
                    name = getCellName(operand);

                    // Use the name to lookup the cell in the cellvar storage and push
                    // it on the stack. 
                    opStack->push(cellvars[name]);
                    break;

                case BUILD_TUPLE:
                    args = new vector<PyObject*>();
                    for (i = 0; i < operand; i++) {
                        u = safetyPop();
                        it = args->begin();
                        args->insert(it, u);
                    }

                    opStack->push(new PyTuple(args));
                    break;

                case SELECT_TUPLE:
                    u = safetyPop();
                    if (u->getType()->typeId() != PyTupleType) {
                        throw new PyException(PYILLEGALOPERATIONEXCEPTION, "Attempt to select elements of a tuple from non-tuple object.");
                    }

                    tuple = (PyTuple*) u;

                    if (operand != tuple->size()) {
                        throw new PyException(PYILLEGALOPERATIONEXCEPTION, "Attempt to select elements of a tuple with incorrect size.");
                    }
                    
                    for (i=tuple->size()-1;i>=0;i--) {
                        opStack->push(tuple->getVal(i));
                    }
                    
                    break;

                case BUILD_LIST:
                    args = new vector<PyObject*>();
                    for (int i = 0; i < operand; i++) {
                        u = safetyPop();
                        it = args->begin();
                        args->insert(it, u);
                    }

                    opStack->push(new PyList(args));
                    break;

                case BUILD_FUNLIST:
                    args = new vector<PyObject*>();
                    for (int i = 0; i < operand; i++) {
                        u = safetyPop();
                        it = args->begin();
                        args->insert(it, u);
                    }

                    opStack->push(new PyFunList(args));
                    break;

                case SELECT_FUNLIST:
                    u = safetyPop();
                    if (u->getType()->typeId() != PyFunListType) {
                        throw new PyException(PYILLEGALOPERATIONEXCEPTION, "Attempt to select elements of a funlist from non-funlist object.");
                    }
                    funlist = (PyFunList*) u;
                    opStack->push(funlist->getTail());
                    opStack->push(funlist->getHead());
                    break;

                case CONS_FUNLIST:
                    u = safetyPop();
                    v = safetyPop();
                    if (u->getType()->typeId() != PyFunListType) {
                        throw new PyException(PYILLEGALOPERATIONEXCEPTION, "Attempt to construct a funlist without a funlist tail.");
                    }
                    funlist = (PyFunList*) u;
                    opStack->push(new PyFunList(v, funlist));
                    break;

                case MAKE_CLOSURE:
                    u = safetyPop();
                    v = safetyPop();
                    w = new PyFunction(*((PyCode*) u), globals, v);
                    opStack->push(w);
                    break;

                case MAKE_FUNCTION:
                    u = safetyPop();
                    w = new PyFunction(*((PyCode*) u), globals, NULL);
                    opStack->push(w);
                    break;

                case STORE_DEREF:
                    u = safetyPop();
                    cell = cellvars[getCellName(operand)];
                    cell->set(u);
                    break;

                case LOAD_DEREF:
                    cell = cellvars[getCellName(operand)];
                    opStack->push(cell->deref());
                    break;

                case SETUP_EXCEPT:
                    // Multiplying by -1 is because any value less than 0
                    // is for a try except. 
                    blockStack->push(-1 * operand);
                    break;

                case RAISE_VARARGS:
                    // This is not currently implemented according to the 
                    // byte code documentation. The documentation says this:
                    // RAISE_VARARGS(argc)
                    //    Raises an exception. argc indicates the number of 
                    //    parameters to the raise statement, ranging from 0 to 3. 
                    //    The handler will find the traceback as TOS2, the 
                    //    parameter as TOS1, and the exception as TOS.
                    // In this interpreter, currently exceptions contain the traceback
                    // and there is always one argument to the RAISE_VARARGS 
                    // instruction, which is the value stored in the exception.
                    u = safetyPop();
                    throw ((PyException*) u);
                    break;

                case DUP_TOP:
                    if (opStack->isEmpty()) {
                        throw new PyException(PYEMPTYSTACKEXCEPTION, "Attempt to duplicate top entry of empty operand stack.");
                    }
                    opStack->push(opStack->top());
                    break;

                case SETUP_FINALLY:
                    blockStack->push(-1 * operand);
                    break;

                case END_FINALLY:
                    if (!handled) {
                        //The stack contains:
                        //TOS: Exception
                        //TOS1: Value (which is just our exception again)
                        //TOS2: Traceback - but this is in our exception
                        //And the block stack contains a block for the handler
                        //So we pop three values and throw our exception again.
                        u = safetyPop();
                        v = safetyPop();
                        w = safetyPop();
                        blockStack->pop();

                        throw ((PyException*) u);
                    }
                    break;

                case POP_EXCEPT:
                    operand = blockStack->pop();
                    if (operand > 0) {
                        throw new PyException(PYILLEGALOPERATIONEXCEPTION, "Pop of block stack was for non-exception handling block.");
                    }
                    break;

                case DELETE_FAST:
                    //The purpose of this instruction is not well understood.
                    //According to the definition it deletes the local 
                    //variable found at index operand.
                    delete locals[code.getLocals()[operand]];
                    break;

                default:
                    throw new PyException(PYILLEGALOPERATIONEXCEPTION, "Unimplemented instruction: " + inst->getOpCodeName());
            }
        } catch (PyException* ex) {
            int x;
            bool found = false;
            while (!found && !blockStack->isEmpty()) {
                x = blockStack->pop();
                if (x < 0) {
                    // A value less than or equal to zero on the block stack indicates a try except block
                    found = true;
                    if (verbose) {
                        cerr << "******************Handling Exception*********************" << endl;
                        cerr << "The exception was: " << ex->toString() << endl;
                        cerr << "---------------------------------------------------------" << endl;
                        cerr << "              The Exception's Traceback" << endl;
                        cerr << "---------------------------------------------------------" << endl;
                        ex->printTraceBack();
                        cerr << "******************End Handling Exception*****************" << endl;
                    }
                    //The Exception is pushed onto the operand stack for processing.
                    opStack->push(ex->getTraceBack()); //The traceback at TOS2
                    opStack->push(ex); //The parameter (in our case the exception) at TOS1
                    opStack->push(ex); //The Exception at TOS
                    //The location to resume execution was found on the block stack.
                    PC = -1 * x;

                    //An implicitly pushed exception handling block is pushed for the handler
                    blockStack->push(0);
                }
            }

            if (!found) {
                ex->tracebackAppend(this);
                throw ex;
            }
        } catch (...) {
            PyException* ex = new PyException(PYILLEGALOPERATIONEXCEPTION, "Unknown Error while executing instruction " + inst->getOpCodeName());
            ex->tracebackAppend(this);
            throw ex;
        }

    }
}

const PyCode& PyFrame::getCode() const {
    return code;
}

int PyFrame::getPC() const {
    return PC;
}