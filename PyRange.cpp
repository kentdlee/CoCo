/* 
 * File:   PyRange.cpp
 * Author: Kent D. Lee
 * (c) 2013
 * Created on February 23, 2013, 8:25 PM
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

#include "PyRange.h"
#include "PyInt.h"
#include "PyType.h"
#include "PyRangeIterator.h"
#include "PyException.h"
#include <sstream>
using namespace std;

PyRange::PyRange(int start, int stop, int increment) : PyObject() {
    this->start = start;
    this->stop = stop;
    this->increment = increment;
    
    dict["__iter__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyRange::__iter__);
    dict["__len__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyRange::__len__);
    dict["__getitem__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyRange::__getitem__);
}

PyRange::~PyRange() {
}

PyType* PyRange::getType() {
    return PyTypes[PyRangeTypeId];
}

PyObject* PyRange::__iter__(vector<PyObject*>* args) {
    return new PyRangeIterator(this);
}

PyObject* PyRange::__len__(vector<PyObject*>* args) {
    return new PyInt((stop - start) / increment);
}

string PyRange::toString() {
    ostringstream s;
    s << "range(" << start << "," << stop << "," << increment << ")";
    
    return s.str();
}


PyObject* PyRange::__getitem__(vector<PyObject*>* args) {
    if (args->size() != 1) {
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,"TypeError: expected 1 arguments, got " + args->size());
    }
    
    PyInt* indexObj = (PyInt*) (*args)[0];
    int index = indexObj->getVal();
    
    return indexOf(index);
}

PyObject* PyRange::indexOf(int index) {
    int val = start + index * increment;
    
    if (increment > 0 && val >= stop) {
        throw new PyException(PYSTOPITERATIONEXCEPTION,"Stop Iteration");
    }
    
    if (increment < 0 && val <= stop) {
        throw new PyException(PYSTOPITERATIONEXCEPTION,"Stop Iteration");
    }
    
    return new PyInt(start + increment*index);
}