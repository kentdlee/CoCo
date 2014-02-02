/* 
 * File:   PyFunction.cpp
 * Author: Kent D. Lee
 * (c) 2013
 * Created on February 15, 2013, 10:05 PM
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

#include "PyFunction.h"
#include "PyCode.h"
#include "PyException.h"
#include "PyFrame.h"
#include "PyType.h"
#include <iostream>
#include <sstream>
using namespace std;

PyFunction::PyFunction(PyCode& theCode, unordered_map<string,PyObject*>& theGlobals, PyObject* env) :
        PyCallable(), code(theCode), globals(theGlobals)
{
    PyTuple* tuple = (PyTuple*) env;
    
    for (int i = 0; i < theCode.getFreeVars().size(); i++) {
        cellvars[theCode.getFreeVars()[i]] = (PyCell*)tuple->getVal(i);
    }
}

PyFunction::~PyFunction() {
}


PyObject* PyFunction::__call__(vector<PyObject*>* args) {
    ostringstream msg;

    if (args->size() != code.getArgCount()) {
        msg << "TypeError: expected " << code.getArgCount() << " arguments, got " << args->size() << " for function " << code.getName();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }

    PyFrame* frame = new PyFrame(code,args,globals,code.getConsts(),cellvars);
    
    PyObject* result = frame->execute();
    
    try {
        delete frame;
    } catch (...) {
        cerr << "Frame deletion caused an exception for some reason.";
    }
    
    return result;
}

PyType* PyFunction::getType() {
    return PyTypes[PyFunctionType];
}

string PyFunction::callName() {
    return code.getName();
}

string PyFunction::toString() {
    return "Function("+callName()+")"; 
}