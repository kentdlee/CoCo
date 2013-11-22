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

PyException::PyException(int exception, PyObject* v) : exceptionType(exception), val(v) {
}

PyException::PyException(int exception, string msg) : exceptionType(exception), val(new PyStr(msg)) {
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
    //return excnames[exceptionType] + ": " + val->toString();
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
    PyObject* arg = (*args)[0];
    
    return new PyBool(this->getType() == arg);
}

PyObject* PyException::getTraceBack() {   
    return new PyList((vector<PyObject*>*)&traceback);
}