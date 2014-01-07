/* 
 * File:   PyRangeIterator.cpp
 * Author: Kent D. Lee
 * (c) 2013
 * Created on February 23, 2013, 10:51 PM
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

#include "PyRangeIterator.h"
#include "PyException.h"
#include <sstream>
using namespace std;

PyRangeIterator::PyRangeIterator(PyRange* obj) : PyObject() {
    rangeObj = obj;
    index = 0;
    
    dict["__iter__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyRangeIterator::__iter__);
    dict["__next__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyRangeIterator::__next__);
}

PyRangeIterator::~PyRangeIterator() {
}

PyType* PyRangeIterator::getType() {
    return PyTypes[PyRangeIteratorType];
}

PyObject* PyRangeIterator::__iter__(vector<PyObject*>* args) {
    ostringstream msg; 

    if (args->size() != 0) {
        msg << "TypeError: expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    
    return this;
}

string PyRangeIterator::toString() {
    ostringstream s;
    
    s << "<range_iterator object at " << this << ">";
    
    return s.str();
}

PyObject* PyRangeIterator::__next__(vector<PyObject*>* args) {
    ostringstream msg;

    if (args->size() != 0) {
        msg << "TypeError: expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }

    PyObject* result = this->rangeObj->indexOf(index);
    index++;

    return result;
}