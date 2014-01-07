/* 
 * File:   PyStrIterator.cpp
 * Author: kent
 * (c) 2013
 * Created on February 28, 2013, 9:55 AM
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

#include "PyStrIterator.h"
#include "PyException.h"
#include "PyStr.h"
#include <sstream>
using namespace std;

PyStrIterator::PyStrIterator(PyStr* str) : PyObject() {
    this->str = str;
    this->index = 0;
    
    dict["__iter__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyStrIterator::__iter__);
    dict["__next__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyStrIterator::__next__);
}

PyStrIterator::~PyStrIterator() {
}

PyType* PyStrIterator::getType() {
    return PyTypes[PyStrIteratorType];
}

string PyStrIterator::toString() {
    ostringstream s;
    
    s << "<str_iterator object at " << this << ">";
    
    return s.str();  
}

PyObject* PyStrIterator::__iter__(vector<PyObject*>* args) {
    ostringstream msg;

    if (args->size() != 0) {
        msg << "TypeError: expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    
    return this;
}

PyObject* PyStrIterator::__next__(vector<PyObject*>* args) {
    ostringstream msg;

    if (args->size() != 0) {
        msg << "TypeError: expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    
    return str->charAt(index++);
}