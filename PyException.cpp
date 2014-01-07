/*
 * PyException.cpp
 * Author: Kent D. Lee
 * (c) 2013
 * Created on: Feb 3, 2013
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

#include "PyException.h"
#include "PyStr.h"
#include "PyFrame.h"
#include "PyList.h"
#include "PyBool.h"
#include <map>
#include <sstream>
using namespace std;

struct names {

    static map<int, string> create_map() {
        map<int, string> m;
        m[PYEXCEPTION] = "Exception";
        m[PYEMPTYSTACKEXCEPTION] = "EmptyStackException";
        m[PYPARSEEXCEPTION] = "ParseException";
        m[PYILLEGALOPERATIONEXCEPTION] = "IllegalOperationException";
        m[PYWRONGARGCOUNTEXCEPTION] = "WrongArgCountExeption";
        m[PYSTOPITERATIONEXCEPTION] = "StopIterationException";
        m[PYMATCHEXCEPTION] = "MatchException";

        return m;
    }
};

static map<int, string> excnames = names::create_map();

PyException::PyException(int exception, PyObject* v) : PyObject(), exceptionType(exception), val(v) {
    dict["__excmatch__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyException::__excmatch__);
}

PyException::PyException(int exception, string msg) : PyObject(), exceptionType(exception), val(new PyStr(msg)) {
    dict["__excmatch__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyException::__excmatch__);
}


PyException::~PyException() {
    try {
        delete val;
    } catch (...) {}
}

int PyException::getExceptionType() {
    return exceptionType;
}

string PyException::toString() {
    return val->toString();
}

PyType* PyException::getType() {
    return PyTypes[PyExceptionTypeId];
}

void PyException::printTraceBack() {  
    for (int k=0; k<traceback.size();k++) {
        cerr << "==========> At PC=" << (traceback[k]->getPC()-1) << " in this function. " << endl;
        cerr << traceback[k]->getCode().prettyString("",true);
    }
}

void PyException::tracebackAppend(PyFrame* frame) {
    traceback.push_back(frame);
}

PyObject* PyException::__excmatch__(vector<PyObject*>* args) {
    ostringstream msg;
    
    if (args->size() != 1) {
        msg << "TypeError: expected 1 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());      }
    
    PyObject* arg = (*args)[0];
    
    return new PyBool(this->getType() == arg);
}

PyObject* PyException::getTraceBack() {   
    return new PyList((vector<PyObject*>*)&traceback);
}