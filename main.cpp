/* 
 * File:   main.cpp
 * Author: Kent D. Lee
 * (c) 2013
 * Created on February 12, 2013, 10:58 PM
 * 
 * License:
 * Please read the LICENSE file in this distribution for details regarding
 * the licensing of this code. This code is freely available for educational
 * use. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * 
 * Description:
 * Descriptions of possible projects for students are given
 * below. The version to give students can be found at 
 * 
 * http://cs.luther.edu/~leekent/CoCo.tar.gz
 * 
 * The project is a Netbeans project but does not need to be. Netbeans provides 
 * a decent debug environment for C++ but still not great. Print statements are 
 * still useful. The stack class has a toString method to see the contents of a 
 * stack. Elements on the stack must override the ostream& << operator. 
 * 
 * The PyUtil.h source file contains a printMap template that will print the 
 * contents of a map to the screen for debugging.
 * 
 * This is an object-oriented implementation of the Python Virtual Machine. There 
 * are several things that are not supported in this machine. Positional arguments 
 * are implemented but none of the other parameter passing options like default 
 * parameters and keyword parameters are implemented.
 * 
 * Module imports are not supported. However, it is easy to add additional BuiltIn 
 * functions to the language. See PyBuiltInPrint and PyBuiltInInput for examples.
 * 
 * The magic methods are handled by dynamically binding the names of magic methods 
 * to virtual function pointers in the PyObject class. Through the use of virtual 
 * functions any subclass of PyObject may choose to implement any of the magic 
 * methods it desires. Calling magic methods is done through the call method for
 * the type of an object. All operations that are valid on an object are determined
 * by the type of that object.
 * 
 * The CoCo VM assumes that a main function will be defined because code execution
 * begins with the main function in this version of the CoCo VM. The subset of Python 
 * supported by this virtual machine is not unlike the Pascal language (albeit
 * without static type checking). Note that no module level code is supported at this 
 * time but probably could be without too much additional work. It would require 
 * that disassembler.py be extended to handle that and the grammar would have to 
 * be extended. Placing all functions within an implicitly defined function at
 * the module level would provide the appearance of module level variables 
 * with very little work. 
 * 
 * This project as given to students does not contain support for several interesting
 * aspects of Python. These project ideas are outlined below. Not all projects 
 * need or should be done in a semester class, but they are interesting nevertheless.
 * 
 * 1. Support can be added for various constructs in Python like while loops, for loops.
 * 
 * 2. The break statement in while loops and for loops must exit a loop. In that case
 * a Block Stack is needed to keep track of exit points when a loop is entered. This
 * is why the setup loop and pop block instructions exist. 
 * 
 * 3. Support for List objects could be added. In that case, for loops could also be 
 * added since they iterate over sequences (either strings or lists).
 * 
 * 4. The range function could be implemented. In this case a new range object should
 * be created to allow for lazy evaluation of the range. 
 * 
 * 5. Support for nested functions can be added. This entails identifying free variables
 * in a function and those variables that are accessed from an inner scope. Variables 
 * accessed from an inner scope must be pointed to by a new object called a PyCell object
 * because the inner function must be able to change the reference of the variable that 
 * points to the value because changes within the inner scope are still in effect when
 * the inner function returns. This is called a Closure. A closure is just a list of 
 * PyCell objects for the free variables of a called inner function. The PyFunction
 * object then is created and a closure is made (setting the closure field of the function)
 * so when the function is called the PyCells are accessible in the inner function.
 * 
 * This also means that the outer function must create the variables accessed in an inner
 * scope by creating PyCell objects too. This is necessary since both the inner and the outer
 * function code will dereference the cell objects in the same way. 
 * 
 * To implement this the grammar has to change slightly. The disassemple.py function handles
 * nested functions and shows the grammar format (see the sample program in disassembly.py). 
 * The scanner needs to change to recognize parens (I believe this is the only change to the
 * scanner). The grammar needs to allow nested functions. Items of code(x) can appear in the 
 * constants and can be handled by placing the code object in the constants list. 
 * 
 * 6. Garbage Collection can be implemented using reference counting. This is how Python
 * implements garbage collection. Each new object and new reference to an object increments
 * the reference count. When a function is not needed its reference count is deleted. When
 * the reference count reaches zero it is deleted. This can be handled with a new 
 * delete or unref function to do the reference counting. 
 * 
 * The only problem with this type of garbage collection is that circular references to objects
 * may exist in which case all objects in the cycle may be garbage collected while none
 * will be since all reference counts in the cycle would be non-zero. Does not happen 
 * often in practice though. 
 * 
 * 7. Through the use of additional built in functions support for Files could be added. In addition,
 * math functions could be implemented. There are many extensions to the language that 
 * could be implemented by adding additional built in functions. Some very interesting 
 * uses of the language are possible. For example, some form of turtle graphics might be possible. 
 * Some limited GUI programming using a C or C++ API might be possible. Computer Graphics programming
 * might be possible as well given the right set of primitive objects/functions. 
 */

#include "PyStack.h"
#include "PyScanner.h"
#include "PyParser.h"
#include "PyCode.h"
#include "PyObject.h"
#include "PyInt.h"
#include "PyType.h"
#include "PyFunction.h"
#include "PyBuiltInPrint.h"
#include "PyBuiltInFPrint.h"
#include "PyBuiltInTPrint.h"
#include "PyException.h"
#include "PyExceptionType.h"
#include "PyBuiltInInput.h"
#include "PyStr.h"
#include "PyFloat.h"
#include "PyBool.h"
#include "PyRange.h"
#include "PyRangeType.h"
#include "PyRangeIterator.h"
#include "PyBuiltInIter.h"
#include "PyBuiltInLen.h"
#include "PyBuiltInConcat.h"
#include "PyFrame.h"
#include "PyException.h"
#include <iostream>
#include <fstream>
#include <map>
#include <csignal>
#include <stdlib.h>
using namespace std;

vector<PyFrame*> callStack;

void pushFrame(PyFrame* frame) {
    callStack.push_back(frame);
    if (callStack.size() == 1000) {
        throw new PyException(PYILLEGALOPERATIONEXCEPTION, "Call Stack Overflow.");
    }
}

void popFrame() {
    callStack.pop_back();
}

void sigHandler(int signum) {
    cerr << "\n\n";
    cerr << "*********************************************************" << endl;
    cerr << "            An Uncaught Exception Occurred" << endl;
    cerr << "*********************************************************" << endl;
    cerr << "The exception was:\n";
    switch (signum) {
        case SIGABRT:
            cerr << "Program Execution Aborted" << endl;
            break;
        case SIGFPE:
            cerr << "Arithmetic or Overflow Error" << endl;
            break;
        case SIGILL:
            cerr << "Illegal Instruction in Virtual Machine" << endl;
            break;
        case SIGINT:
            cerr << "Execution Interrupted" << endl;
            break;
        case SIGSEGV:
            cerr << "Illegal Memory Access" << endl;
            break;
        case SIGTERM:
            cerr << "Termination Requested" << endl;
            break;
    }
    
    cerr << "---------------------------------------------------------" << endl;
    cerr << "              The Exception's Traceback" << endl;
    cerr << "---------------------------------------------------------" << endl;
    for (int k=callStack.size()-1;k>=0;k--) {
        cerr << "==========> At PC=" << (callStack[k]->getPC()-1) << " in this function. " << endl;
        cerr << callStack[k]->getCode().prettyString("",true);
    } 
    exit(0);
}

map<PyTypeId, PyType*> PyTypes;
bool verbose = false;

map<PyTypeId, PyType*> initTypes() {

    map<PyTypeId, PyType*> types;

    PyType* typeType = new PyType("type", PyTypeType);
    types[PyTypeType] = typeType;

    typeType->addFun("__type__", &PyObject::__type__, 1);
    typeType->addFun("__call__", &PyObject::__call__, 0);
    typeType->addFun("__str__", &PyObject::__str__, 1);

    PyType* noneType = new PyType("NoneType", PyNoneType);
    types[PyNoneType] = noneType;

    noneType->addFun("__type__", &PyObject::__type__, 1);
    noneType->addFun("__str__", &PyObject::__str__, 1);

    PyType* boolType = new PyType("bool", PyBoolType);
    types[PyBoolType] = boolType;

    boolType->addFun("__type__", &PyObject::__type__, 1);
    boolType->addFun("__eq__", &PyObject::__eq__, 2);
    boolType->addFun("__str__", &PyObject::__str__, 1);
    boolType->addFun("__int__", &PyObject::__int__, 1);
    boolType->addFun("__float__", &PyObject::__float__, 1);
    boolType->addFun("__bool__", &PyObject::__bool__, 1);

    PyType* intType = new PyType("int", PyIntType);
    types[PyIntType] = intType;

    intType->addFun("__type__", &PyObject::__type__, 1);
    intType->addFun("__add__", &PyObject::__add__, 2);
    intType->addFun("__sub__", &PyObject::__sub__, 2);
    intType->addFun("__mul__", &PyObject::__mul__, 2);
    intType->addFun("__floordiv__", &PyObject::__floordiv__, 2);
    intType->addFun("__truediv__", &PyObject::__truediv__, 2);
    intType->addFun("__eq__", &PyObject::__eq__, 2);
    intType->addFun("__lt__", &PyObject::__lt__, 2);
    intType->addFun("__gt__", &PyObject::__gt__, 2);
    intType->addFun("__le__", &PyObject::__le__, 2);
    intType->addFun("__ge__", &PyObject::__ge__, 2);
    intType->addFun("__str__", &PyObject::__str__, 1);
    intType->addFun("__int__", &PyObject::__int__, 1);
    intType->addFun("__float__", &PyObject::__float__, 1);
    intType->addFun("__bool__", &PyObject::__bool__, 1);

    PyType* floatType = new PyType("float", PyFloatType);
    types[PyFloatType] = floatType;

    floatType->addFun("__type__", &PyObject::__type__, 1);
    floatType->addFun("__add__", &PyObject::__add__, 2);
    floatType->addFun("__str__", &PyObject::__str__, 1);
    floatType->addFun("__int__", &PyObject::__int__, 1);
    floatType->addFun("__float__", &PyObject::__float__, 1);
    floatType->addFun("__bool__", &PyObject::__bool__, 1);

    PyType* strType = new PyType("str", PyStrType);
    types[PyStrType] = strType;

    strType->addFun("__type__", &PyObject::__type__, 1);
    strType->addFun("__add__", &PyObject::__add__, 2);
    strType->addFun("__str__", &PyObject::__str__, 1);
    strType->addFun("__int__", &PyObject::__int__, 1);
    strType->addFun("__funlist__", &PyObject::__funlist__, 1);
    strType->addFun("__float__", &PyObject::__float__, 1);
    strType->addFun("__bool__", &PyObject::__bool__, 1);
    strType->addFun("__iter__", &PyObject::__iter__, 1);
    strType->addFun("__len__", &PyObject::__len__, 1);
    strType->addFun("__eq__", &PyObject::__eq__, 2);
    strType->addFun("__index__", &PyObject::__index__, 2);
    strType->addFun("split", &PyObject::split, 1);

    PyType* functionType = new PyType("function", PyFunctionType);
    types[PyFunctionType] = functionType;

    functionType->addFun("__type__", &PyObject::__type__, 1);
    functionType->addFun("__call__", &PyObject::__call__, 0);
    functionType->addFun("__str__", &PyObject::__str__, 1);

    PyType* builtinType = new PyType("builtin_function_or_method", PyBuiltInType);
    types[PyBuiltInType] = builtinType;

    builtinType->addFun("__type__", &PyObject::__type__, 1);
    builtinType->addFun("__call__", &PyObject::__call__, 0);
    builtinType->addFun("__str__", &PyObject::__str__, 1);

    PyType* rangeType = new PyRangeType("range", PyRangeTypeId);
    types[PyRangeTypeId] = rangeType;

    rangeType->addFun("__type__", &PyObject::__type__, 1);
    rangeType->addFun("__str__", &PyObject::__str__, 1);
    rangeType->addFun("__iter__", &PyObject::__iter__, 1);
    rangeType->addFun("__len__", &PyObject::__len__, 1);
    rangeType->addFun("__index__", &PyObject::__index__, 2);

    PyType* exceptionType = new PyExceptionType("Exception", PyExceptionTypeId);
    types[PyExceptionTypeId] = exceptionType;

    exceptionType->addFun("__type__", &PyObject::__type__, 1);
    exceptionType->addFun("__str__", &PyObject::__str__, 1);
    exceptionType->addFun("__excmatch__", &PyObject::__excmatch__, 2);

    PyType* rangeIteratorType = new PyType("range_iterator", PyRangeIteratorType);
    types[PyRangeIteratorType] = rangeIteratorType;

    rangeIteratorType->addFun("__type__", &PyObject::__type__, 1);
    rangeIteratorType->addFun("__str__", &PyObject::__str__, 1);
    rangeIteratorType->addFun("__iter__", &PyObject::__iter__, 1);
    rangeIteratorType->addFun("__next__", &PyObject::__next__, 1);

    PyType* listType = new PyType("list", PyListType);
    types[PyListType] = listType;

    listType->addFun("__type__", &PyObject::__type__, 1);
    listType->addFun("__str__", &PyObject::__str__, 1);
    listType->addFun("__iter__", &PyObject::__iter__, 1);
    listType->addFun("__len__", &PyObject::__len__, 1);
    listType->addFun("__index__", &PyObject::__index__, 2);
    listType->addFun("append", &PyObject::append, 2);

    PyType* funListType = new PyType("funlist", PyFunListType);
    types[PyFunListType] = funListType;

    funListType->addFun("__type__", &PyObject::__type__, 1);
    funListType->addFun("__str__", &PyObject::__str__, 1);
    funListType->addFun("__iter__", &PyObject::__iter__, 1);
    funListType->addFun("__len__", &PyObject::__len__, 1);
    funListType->addFun("__index__", &PyObject::__index__, 2);
    funListType->addFun("__add__", &PyObject::__add__, 2);
    funListType->addFun("head", &PyObject::head, 1);
    funListType->addFun("tail", &PyObject::tail, 1);
    funListType->addFun("concat", &PyObject::concat, 1);

    PyType* tupleType = new PyType("tuple", PyTupleType);
    types[PyTupleType] = tupleType;

    tupleType->addFun("__type__", &PyObject::__type__, 1);
    tupleType->addFun("__str__", &PyObject::__str__, 1);
    tupleType->addFun("__iter__", &PyObject::__iter__, 1);
    tupleType->addFun("__len__", &PyObject::__len__, 1);
    tupleType->addFun("__index__", &PyObject::__index__, 2);

    PyType* listIteratorType = new PyType("list_iterator", PyListIteratorType);
    types[PyListIteratorType] = listIteratorType;

    listIteratorType->addFun("__type__", &PyObject::__type__, 1);
    listIteratorType->addFun("__str__", &PyObject::__str__, 1);
    listIteratorType->addFun("__iter__", &PyObject::__iter__, 1);
    listIteratorType->addFun("__next__", &PyObject::__next__, 1);

    listIteratorType = new PyType("funlist_iterator", PyFunListIteratorType);
    types[PyFunListIteratorType] = listIteratorType;

    listIteratorType->addFun("__type__", &PyObject::__type__, 1);
    listIteratorType->addFun("__str__", &PyObject::__str__, 1);
    listIteratorType->addFun("__iter__", &PyObject::__iter__, 1);
    listIteratorType->addFun("__next__", &PyObject::__next__, 1);

    PyType* tupleIteratorType = new PyType("tuple_iterator", PyTupleIteratorType);
    types[PyTupleIteratorType] = tupleIteratorType;

    tupleIteratorType->addFun("__type__", &PyObject::__type__, 1);
    tupleIteratorType->addFun("__str__", &PyObject::__str__, 1);
    tupleIteratorType->addFun("__iter__", &PyObject::__iter__, 1);
    tupleIteratorType->addFun("__next__", &PyObject::__next__, 1);

    PyType* strIteratorType = new PyType("str_iterator", PyStrIteratorType);
    types[PyStrIteratorType] = strIteratorType;

    strIteratorType->addFun("__type__", &PyObject::__type__, 1);
    strIteratorType->addFun("__str__", &PyObject::__str__, 1);
    strIteratorType->addFun("__iter__", &PyObject::__iter__, 1);
    strIteratorType->addFun("__next__", &PyObject::__next__, 1);

    PyType* codeType = new PyType("code", PyCodeType);
    types[PyCodeType] = codeType;

    codeType->addFun("__type__", &PyObject::__type__, 1);
    codeType->addFun("__str__", &PyObject::__str__, 1);

    PyType* cellType = new PyType("cell", PyCellType);
    types[PyCellType] = cellType;

    cellType->addFun("__type__", &PyObject::__type__, 1);
    cellType->addFun("__str__", &PyObject::__str__, 1);

    return types;
}

int main(int argc, char* argv[]) {
    char* filename;
    
    signal(SIGABRT,sigHandler);
    signal(SIGFPE,sigHandler);
    signal(SIGILL,sigHandler);
    signal(SIGINT,sigHandler);
    signal(SIGSEGV,sigHandler);
    signal(SIGTERM,sigHandler);
    
    if (argc != 2 && argc != 3) {
        cerr << "Invoke as : coco [-v] filename" << endl;
        return 0;
    }

    PyTypes = initTypes();

    if (argc == 2)
        filename = argv[1];
    else {
        filename = argv[2];
        verbose = true;
    }

    try {
        istream* in = new ifstream(filename);

        PyScanner* scan = new PyScanner(in);

        PyParser* parser = new PyParser(scan);

        vector<PyCode*>* code = parser->parse();

        /* 
            This for loop prints the data read from the file back in nearly the same
            format. The only difference is the labels are removed and replaced with
            the actual address of the instructions. Instruction addresses start at 
            zero and each instruction takes exactly on location (i.e. index) in the
            code object. NOTE: The actual Python Virtual Machine is not implemented 
            this way. Instructions take one to several bytes in the actual machine. 
            This machine use index and address interchangeably to keep things simple.
            Once parsing is working the for loop below can be commented out or thrown
            away when work commences on the execution of the virtual machine.
         */
        string indent = "";

        for (int i = 0; i < code->size(); i++) {
            cerr << (*code)[i]->prettyString(indent, false) << endl;
            cerr << endl;
        }


        /*  This code will run the interpreter once the parser reads the data.
         */

        map<string, PyObject*> globals;

        globals["print"] = new PyBuiltInPrint();
        globals["fprint"] = new PyBuiltInFPrint();
        globals["tprint"] = new PyBuiltInTPrint();
        globals["input"] = new PyBuiltInInput();
        globals["iter"] = new PyBuiltInIter();
        globals["int"] = PyTypes[PyIntType];
        globals["float"] = PyTypes[PyFloatType];
        globals["str"] = PyTypes[PyStrType];
        globals["funlist"] = PyTypes[PyFunListType];
        globals["type"] = PyTypes[PyTypeType];
        globals["bool"] = PyTypes[PyBoolType];
        globals["range"] = PyTypes[PyRangeTypeId];
        globals["Exception"] = PyTypes[PyExceptionTypeId];
        globals["len"] = new PyBuiltInLen();
        globals["concat"] = new PyBuiltInConcat();


        //Now add the top-level functions
        bool foundMain = false;

        for (int i = 0; i < code->size(); i++) {
            if ((*code)[i]->getName() == "main")
                foundMain = true;

            globals[(*code)[i]->getName()] = new PyFunction(*((*code)[i]), globals, NULL);
        }

        if (!foundMain) {
            cerr << "Error: No main() function found. A main() is required in CoCo VM programs." << endl;
            return 0;
        }


        vector<PyObject*>* args = new vector<PyObject*>();

        PyType* selfType = globals["main"]->getType();
        PyObject* result = selfType->call("__call__", globals["main"], args);

    } catch (PyException* ex) {
        cerr << "\n\n";
        cerr << "*********************************************************" << endl;
        cerr << "            An Uncaught Exception Occurred" << endl;
        cerr << "*********************************************************" << endl;
        cerr << "The exception was: " << ex->toString() << endl;
        cerr << "---------------------------------------------------------" << endl;
        cerr << "              The Exception's Traceback" << endl;
        cerr << "---------------------------------------------------------" << endl;
        ex->printTraceBack();
        cerr << "*********************************************************" << endl;
        cerr << "            An Uncaught Exception Occurred (See Above) " << endl;
        cerr << "*********************************************************" << endl;
        cerr << "The exception was: " << ex->toString() << endl;        
        cerr << "*********************************************************" << endl;
    } 


    return 0;
}
