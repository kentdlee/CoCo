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
 * to virtual function pointers in a map called dict that is declared in the 
 * PyObject class. Through the use of virtual functions any subclass of PyObject 
 * may choose to implement any of the magic methods it desires. Calling magic 
 * methods is done through the callMethod method of the object. All operations 
 * that are valid on an object are determined by the object itself.
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
 * Garbage Collection can be implemented using reference counting. This is how Python
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
 * Through the use of additional built in functions support for Files could be added. In addition,
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
#include <unordered_map>
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
    cerr << "Signal: ";
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

unordered_map<PyTypeId, PyType*, std::hash<int> > PyTypes;
bool verbose = false;

unordered_map<PyTypeId, PyType*, std::hash<int> > initTypes() {

    unordered_map<PyTypeId, PyType*, std::hash<int> > types;

    PyType* typeType = new PyType("type", PyTypeType);
    types[PyTypeType] = typeType;

    PyType* noneType = new PyType("NoneType", PyNoneType);
    types[PyNoneType] = noneType;

    PyType* boolType = new PyType("bool", PyBoolType);
    types[PyBoolType] = boolType;

    PyType* intType = new PyType("int", PyIntType);
    types[PyIntType] = intType;

    PyType* floatType = new PyType("float", PyFloatType);
    types[PyFloatType] = floatType;

    PyType* strType = new PyType("str", PyStrType);
    types[PyStrType] = strType;

    PyType* functionType = new PyType("function", PyFunctionType);
    types[PyFunctionType] = functionType;

    PyType* builtinType = new PyType("builtin_function_or_method", PyBuiltInType);
    types[PyBuiltInType] = builtinType;

    PyType* rangeType = new PyRangeType("range", PyRangeTypeId);
    types[PyRangeTypeId] = rangeType;

    PyType* exceptionType = new PyExceptionType("Exception", PyExceptionTypeId);
    types[PyExceptionTypeId] = exceptionType;

    PyType* rangeIteratorType = new PyType("range_iterator", PyRangeIteratorType);
    types[PyRangeIteratorType] = rangeIteratorType;

    PyType* listType = new PyType("list", PyListType);
    types[PyListType] = listType;

    PyType* funListType = new PyType("funlist", PyFunListType);
    types[PyFunListType] = funListType;

    PyType* tupleType = new PyType("tuple", PyTupleType);
    types[PyTupleType] = tupleType;

    PyType* listIteratorType = new PyType("list_iterator", PyListIteratorType);
    types[PyListIteratorType] = listIteratorType;

    listIteratorType = new PyType("funlist_iterator", PyFunListIteratorType);
    types[PyFunListIteratorType] = listIteratorType;

    PyType* tupleIteratorType = new PyType("tuple_iterator", PyTupleIteratorType);
    types[PyTupleIteratorType] = tupleIteratorType;

    PyType* strIteratorType = new PyType("str_iterator", PyStrIteratorType);
    types[PyStrIteratorType] = strIteratorType;

    PyType* codeType = new PyType("code", PyCodeType);
    types[PyCodeType] = codeType;

    PyType* cellType = new PyType("cell", PyCellType);
    types[PyCellType] = cellType;

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

        PyParser* parser = new PyParser(filename);

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

        unordered_map<string, PyObject*> globals;

        globals["print"] = new PyBuiltInPrint();
        globals["fprint"] = new PyBuiltInFPrint();
        globals["tprint"] = new PyBuiltInTPrint();
        globals["input"] = new PyBuiltInInput();
        globals["iter"] = new PyBuiltInIter();
        globals["int"] = PyTypes[PyIntType];
        globals["float"] = PyTypes[PyFloatType];
        globals["str"] = PyTypes[PyStrType];
        globals["funlist"] = PyTypes[PyFunListType];
        globals["list"] = PyTypes[PyListType];
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
        PyObject* result = globals["main"]->callMethod("__call__", args);

    } catch (PyException* ex) {
        cerr << "\n\n";
        cerr << "*********************************************************" << endl;
        cerr << "            An Uncaught Exception Occurred" << endl;
        cerr << "*********************************************************" << endl;
        cerr << ex->toString() << endl;
        cerr << "---------------------------------------------------------" << endl;
        cerr << "              The Exception's Traceback" << endl;
        cerr << "---------------------------------------------------------" << endl;
        ex->printTraceBack();
        cerr << "*********************************************************" << endl;
        cerr << "            An Uncaught Exception Occurred (See Above) " << endl;
        cerr << "*********************************************************" << endl;
        cerr << ex->toString() << endl;        
        cerr << "*********************************************************" << endl;
    } 


    return 0;
}
